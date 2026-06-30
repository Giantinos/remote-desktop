#include "senderclient.h"

SenderClient::SenderClient(QTextEdit *textWidget,QWidget *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    connectionStatus = ClientState::DISCONNECTED;
    isServerAuthentificated = false;
    isIntentionalDisconnect = false;
    if(textWidget){
        this->textWidget = textWidget;
    }
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
    qDebug() << ">> Trying connect to host";
    if(this->hostAddress.isEmpty() || this->hostPort < 1){
        emit warning("Ip not set");
        return;
    }
    qDebug() << "> OK (this->hostAddress.isEmpty() || this->hostPort < 1)";
    if(!isCorrectIp()){
        emit warning("Invalid IP");
        return;
    }
    qDebug() << "> OK isCorrectIp()";
    if(!isCorrectPort()){
        emit warning(QString("Invalid Port : %1").arg(hostPort));
        return;
    }
    qDebug() << "> OK isCorrectPort()";
    qDebug() << ">> Connection Status : " << SenderClient::getStringConnectionStatus();
    if(connectionStatus == ClientState::CONNECTING){
        qDebug() << "> Invalid Status Error";
        emit warning("Already connecting");
        return;
    }

    if(connectionStatus == ClientState::CONNECTED){
        qDebug() << "> Invalid Status Error";
        emit warning("Already connected");
        return;
    }
    qDebug() << ">> if(!socket) making new one";
    if (!socket) {
        qDebug() << "trying to make new QTcpSocket";
        socket = new QTcpSocket(this);
        qDebug() << "Created new socket";
    }
    qDebug() << "Checking socket for (socket && socket->state() != QTcpSocket::UnconnectedState)";
    qDebug() << "socket > " << socket;
    qDebug() << "socket->state() > " << socket->state();
    if (socket && socket->state() != QTcpSocket::UnconnectedState) {
        socket->disconnectFromHost();
        socket->abort();
        qDebug() << "aborting socket";
        socket->deleteLater();
        socket = nullptr;
        isServerAuthentificated = false;
    }
    qDebug() << "checked";
    qDebug() << "disconnecting old socket signals";
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
    qDebug() << "Connecting...";
    isServerAuthentificated = false;
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
        if(!isServerAuthentificated){
            socket->abort();
            connectionStatus = ClientState::DISCONNECTED;
            emit connectionStatusChanged(connectionStatus);
            emit warning("Server did not respond to handshake");
        }
    });
}

void SenderClient::onReadyRead(){
    QByteArray data = socket->readAll();
    qDebug() << "cheking auth server";
    if(!isServerAuthentificated){
        qDebug() << "Not server isnt auth";
        if(data.contains(SERVER_HANDSHAKE.toUtf8())){
            qDebug() << "Auth done. HANDSHAKING";
            printMessage("Server is authentificated");
            printMessage(QString("Server: %1").arg(SERVER_HANDSHAKE));
            isServerAuthentificated = true;
            connectionStatus = ClientState::CONNECTED;
            emit connectionStatusChanged(connectionStatus);
        }else{
            qDebug() << "Auth failed. socket Aborting";
            socket->abort();
            emit warning("Invalid server response");
        }
    } else {
        printMessage("Server authorized.");
        printMessage(QString("Server: %1").arg(data));
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
    qDebug() << QString("Socket Error: %1").arg(socket->errorString());
    errorMessage = QString("Ошибка сокета: %1").arg(socket->errorString());
    connectionStatus = ClientState::C_ERROR;
    emit connectionStatusChanged(connectionStatus);
    emit warning(QString("Socker error %1").arg(socket->errorString()));
}

void SenderClient::disconnectFromHost(){
    if(!socket) return;
    if(socket->state() == QAbstractSocket::ConnectedState){
        isIntentionalDisconnect = true;
        socket->disconnect();
        socket->disconnectFromHost();
        if(socket && socket->state() != QTcpSocket::UnconnectedState){
            socket->waitForDisconnected(2000);
        }
        if (socket && socket->state() != QTcpSocket::UnconnectedState) {
            socket->abort();
        }
    } else {
        emit warning("Connection is not exist");
    }
    connectionStatus = ClientState::DISCONNECTED;
    emit connectionStatusChanged(connectionStatus);
}

void SenderClient::onDisconnected() {
    qDebug() << ">> onDisconnected()";
    if(!isIntentionalDisconnect){
        qDebug() << ">> NOT Intentional disconnect";
        connectionStatus = ClientState::DISCONNECTED;
        emit connectionStatusChanged(connectionStatus);
        emit warning("Host connection lost");
    }else qDebug() << ">> Intentional disconnect!";
    qDebug() << ">> Deleting socket memory";
    socket->deleteLater(); // Освободить память
    socket = nullptr;
    qDebug() << ">> socket = nulltpr";
    isIntentionalDisconnect = false;
}

void SenderClient::printMessage(QString message){
    textWidget->append(message);
}