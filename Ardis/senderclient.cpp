#include "senderclient.h"

SenderClient::SenderClient(QWidget *parent) : QObject(parent)
{
    socket = new QTcpSocket(this);
    connectionStatus = ClientConnectionStatus::DISCONNECTED;
}

QString SenderClient::getStringConnectionStatus(){
    QString status;
    switch(connectionStatus){
    case 0: status = "Disconnected"; break;
    case 1: status = "Connected"; break;
    case 2: status = "Trying to connect"; break;
        // добавить отображение таймаута
    case 3: status = "Disconnecting"; break;
    case 4: status = "Connection failed"; break;
    case 5: status = "Socket error"; break;
    case 6: status = "Connection timeout"; break;
    }
    return status;
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

    socket->connectToHost(hostAddress, hostPort);

    connectionStatus = ClientConnectionStatus::TRYING_TO_CONNECT;
    connectionStatusChanged(connectionStatus);

    // Ожидаем подключения, но с таймаутом
    if (!socket->waitForConnected(CONNECTION_TIMEOUT)) {
        connectionStatus = ClientConnectionStatus::ON_CONNECTION_TIMEOUT;
        emit connectionStatusChanged(connectionStatus);
        emit warning(getStringConnectionStatus());
    } else {
        connectionStatus = ClientConnectionStatus::CONNECTED;
        emit connectionStatusChanged(connectionStatus);

        // соединяем события сокета: ерор дисконнект
        connect(socket, &QTcpSocket::errorOccurred, this, &SenderClient::onSocketError);
        connect(socket, &QTcpSocket::disconnected, this, &SenderClient::onDisconnected);
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
            emit clientEvent("Message sended");
        }
    } else {
        emit warning("Connection lost");
        connectionStatus = ClientConnectionStatus::DISCONNECTED;
        emit connectionStatusChanged(connectionStatus);
    }
}

QString SenderClient::getErrorMessage(){
    return errorMessage;
}

void SenderClient::onSocketError(QAbstractSocket::SocketError socketError) {
    Q_UNUSED(socketError);
    errorMessage = QString("Ошибка сокета: %1").arg(socket->errorString());
    connectionStatus = ClientConnectionStatus::SOCKET_ERROR;
    emit connectionStatusChanged(ClientConnectionStatus::SOCKET_ERROR);
    emit warning(QString("Socker error %1").arg(socket->errorString()));
}

void SenderClient::disconnectFromHost(){
    if(socket->state() == QAbstractSocket::ConnectedState){
        socket->disconnectFromHost();
        connectionStatus = ClientConnectionStatus::DISCONNECTED;
        emit connectionStatusChanged(connectionStatus);
        socket->deleteLater();
    }
}

void SenderClient::onDisconnected() {
    connectionStatus = ClientConnectionStatus::DISCONNECTED;
    emit connectionStatusChanged(ClientConnectionStatus::DISCONNECTED);
    emit warning("Host connection lost");
    // QMessageBox::warning(this, "Предупреждение", "Соединение с сервером было разорвано.");
    // Можно добавить логику переподключения здесь
    socket->deleteLater(); // Освободить память
}




