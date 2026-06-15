#include "senderclient.h"

SenderClient::SenderClient(QWidget *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    connectionStatus = ClientState::DISCONNECTED;
}

QString SenderClient::getStringConnectionStatus(){
    QString status;
    switch(connectionStatus){
    case ClientState::DISCONNECTED: status = "Disconnected"; break;
    case ClientState::CONNECTING: status = "Connecting"; break;
    case ClientState::CONNECTED: status = "Connected"; break;
    case ClientState::C_ERROR: status = "Error"; break;
    }
    return status;
}

int SenderClient::getConnectionStatus(){
    return this->connectionStatus;
}

void SenderClient::connectToHost(){

    if(this->hostAddress.isEmpty() || this->hostPort < 1){
        emit warning("Ip not set");
        return;
    }

    if(!isCorrectIp()){
        emit warning("Invalid IP");
        return;
    }
    if(!isCorrectPort()){
        emit warning(QString("Invalid Port : %1").arg(hostPort));
        return;
    }

    if(connectionStatus == ClientState::CONNECTING){
        emit warning("Already connecting");
        return;
    }

    if(connectionStatus == ClientState::CONNECTED){
        emit warning("Already connected");
        return;
    }

    if (socket && socket->state() != QTcpSocket::UnconnectedState) {
        socket->disconnectFromHost();
        socket->abort();
        socket->deleteLater();
        socket = nullptr;
    }
    if (!socket) {
        socket = new QTcpSocket(this);
    }

    // отключение старого соединения
    disconnect(socket, nullptr, this, nullptr);

    connect(socket, &QTcpSocket::connected,
            this, &SenderClient::onTcpConnected);
    connect(socket, &QTcpSocket::readyRead,
            this, &SenderClient::onReadyRead);
    connect(socket, &QTcpSocket::disconnected,
            this, &SenderClient::onDisconnected);
    connect(socket, &QTcpSocket::errorOccurred,
            this, &SenderClient::onSocketError);
    // connect(socket, &QTcpSocket::stateChanged, this, &SenderClient::onSocketStateChanged);

    connectionStatus = ClientState::CONNECTING;
    emit connectionStatusChanged(connectionStatus);

    socket->connectToHost(hostAddress, hostPort);

    QTimer::singleShot(CONNECTION_TIMEOUT, this, [this](){
        if(connectionStatus != ClientState::CONNECTED){
            connectionStatus = ClientState::DISCONNECTED;

            emit connectionStatusChanged(connectionStatus);
            emit warning("Connection timeout");

            if(socket){
                socket->abort();
            }
        }
    });
}

// в процессе написаниея рукопожатия для программы

void SenderClient::onTcpConnected(){
    socket->write(CLIENT_HANDSHAKE.toUtf8());
    socket->flush();

    QTimer::singleShot(handshakeTime, this, [this](){
        if(isServerAuthentificated){
            socket->abort();
            connectionStatus = ClientState::DISCONNECTED;
            emit connectionStatusChanged(connectionStatus);
            emit warning("Server did not respond to handshake");
        }
    });
}

void SenderClient::onReadyRead(){
    QByteArray data = socket->readAll();

    if(!isServerAuthentificated){
        if(data.contains(SERVER_HANDSHAKE.toUtf8())){
            isServerAuthentificated = true;
            connectionStatus = ClientState::CONNECTED;
            emit connectionStatusChanged(connectionStatus);
        }else{
            socket->abort();
            emit warning("Invalid server response");
        }
    } else {
        emit messageReceived(data);
    }
}

void SenderClient::setHostParameters(QString hostAddress, int hostPort){
    if(hostAddress.isEmpty())
        emit warning("IP is empty");
    else
        this->hostAddress = hostAddress;

    if(isCorrectPort(hostPort))
        this->hostPort = hostPort;
    else
        emit warning("Invalid port");
}

void SenderClient::setHostIp(QString hostAddress){
    if(hostAddress.isEmpty()){
        emit warning("IP is empty");
        return;
    }
    if(isCorrectIp(hostAddress))
        this->hostAddress = hostAddress;
    else
        emit warning("Invalid IP");

}

void SenderClient::setHostPort(int hostPort){
    if(isCorrectPort(hostPort)){
        emit warning("Invalid port");
        return;
    }
    this->hostPort = hostPort;
}

bool SenderClient::isCorrectIp(){
    QHostAddress addr(this->hostAddress);
    return !addr.isNull() && addr.protocol() == QAbstractSocket::IPv4Protocol;
}

bool SenderClient::isCorrectIp(QString ip){
    QHostAddress addr(ip);
    return !addr.isNull() && addr.protocol() == QAbstractSocket::IPv4Protocol;
}

bool SenderClient::isCorrectPort(){
    return this->hostPort >= 1 && this->hostPort <= 65535 ? true : false;
}

bool SenderClient::isCorrectPort(int port){
    return port >= 1 && port <= 65535 ? true : false;
}

void SenderClient::sendMessage(QString message) {
    if (socket->state() == QAbstractSocket::ConnectedState) {
        if (!message.isEmpty()) {
            socket->write(message.toUtf8());
            socket->flush();
            // emit clientEvent("Message sended");
        }
    } else {
        emit warning("Connection lost");
        connectionStatus = ClientState::DISCONNECTED;
        emit connectionStatusChanged(connectionStatus);
    }
}

QString SenderClient::getErrorMessage(){
    return errorMessage;
}

void SenderClient::onSocketError(QAbstractSocket::SocketError socketError) {
    Q_UNUSED(socketError);
    errorMessage = QString("Ошибка сокета: %1").arg(socket->errorString());
    connectionStatus = ClientState::C_ERROR;
    emit connectionStatusChanged(connectionStatus);
    emit warning(QString("Socker error %1").arg(socket->errorString()));
}

void SenderClient::disconnectFromHost(){
    if(!socket) return;

    if(socket->state() == QAbstractSocket::ConnectedState){
        socket->disconnectFromHost();
        if(socket->state() != QTcpSocket::UnconnectedState){
            socket->waitForDisconnected(2000);
        }

        if (socket->state() != QTcpSocket::UnconnectedState) {
            socket->abort();
        }

        socket->deleteLater();
        socket = nullptr;
    } else {
        emit warning("Connection is not exist");
    }
    connectionStatus = ClientState::DISCONNECTED;
    emit connectionStatusChanged(connectionStatus);
}

void SenderClient::onDisconnected() {
    connectionStatus = ClientState::DISCONNECTED;
    emit connectionStatusChanged(connectionStatus);
    emit warning("Host connection lost");
    // QMessageBox::warning(this, "Предупреждение", "Соединение с сервером было разорвано.");
    // Можно добавить логику переподключения здесь
    socket->deleteLater(); // Освободить память
}
