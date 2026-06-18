#include "receiverobject.h"
#include "params.h"

ReceiverObject::ReceiverObject(QTextEdit *textWidget, QObject *parent)
    : QObject{parent}
{

    this->port = 8000;

    this->textWidget = textWidget;
    server = new QTcpServer(this);

    serverStatus = ServerState::STOPPED;
    clientAuthenticated = false;
}

int ReceiverObject::getServerStatus(){
    return this->serverStatus;
}

void ReceiverObject::setPort(int port){
    if(isCorrectPort(port)){
        this->port = port;
    }else{
        emit warning("Port is not correct");
    }
};

void ReceiverObject::initServer(){
    if(port == 0){
        emit warning("Port not initialized");
        return;
    }
    // Пытаемся прослушивать на указанном порту
    if(isCorrectPort()){
        if (!server->listen(QHostAddress::Any, port)) { // QHostAddress::Any слушает на всех доступных сетевых интерфейсах
            emit serverStatusChanged("Error starting server");
            emit warning(QString("Cant start server at port %1. Error: %2").arg(port).arg(server->errorString()));
            serverStatus = ServerState::S_ERROR;
            server->deleteLater();
        } else {
            QString listenAddress = server->serverAddress().toString();
            if (listenAddress.isEmpty() || listenAddress == "0.0.0.0") {
                // Если слушает на всех, показываем, на чем реально
                listenAddress = "All interfaces";
            }
            serverStatus = ServerState::STARTED;
            emit serverStatusChanged(QString("Server started. Listening %1:%2").arg(listenAddress).arg(port));
            connect(server, &QTcpServer::newConnection, this, &ReceiverObject::onNewConnection);

            textWidget->append("Server started. Waiting for connections");
        }
    }
    else emit warning("Invalid port. Allowed port 1 <= port <= 65535");
}

bool ReceiverObject::isCorrectPort(){
    return this->port >= 1 && this->port<= 65535 ? true : false;
}

bool ReceiverObject::isCorrectPort(int port){
    return port >= 1 && port <= 65535 ? true : false;
}

void ReceiverObject::onNewConnection() {
    QTcpSocket *clientSocket = server->nextPendingConnection();
    textWidget->setText("Incoming connection...");
    if (clientSocket) {
        QString clientAddress = clientSocket->peerAddress().toString();
        int clientPort = clientSocket->peerPort();
        textWidget->append(QString("New Client Connected:%1:%2")
                               .arg(clientAddress,QString::number(clientPort)));
        emit serverStatusChanged(QString("Client connected (%1:%2)")
                                     .arg(clientAddress,QString::number(clientPort)));
        serverStatus = ServerState::CLIENT_CONNECTED;

        client = clientSocket;
        connect(client, &QTcpSocket::readyRead,
                this, &ReceiverObject::onReadyRead);
        connect(client, &QTcpSocket::disconnected,
                this, &ReceiverObject::onClientDisconnected);
        //############## подключения бльше не принимаются
        server->close();
        //##############

        QTimer::singleShot(3000, this, [this]() {
            if (!clientAuthenticated && client && client->state() == QTcpSocket::ConnectedState) {
                emit warning("Handshake timeout - client didn't identify itself");
                client->write("TIMEOUT\n");
                client->disconnectFromHost();
            }
        });
    }
}

void ReceiverObject::onReadyRead() {
    /*sender() - это встроенный метод библиотеки Qt,
    который используется внутри слотов (обработчиков сигналов).
    Он возвращает указатель на объект, который отправил (сгенерировал) сигнал,
    вызвавший этот слот.*/

    if (client) {
        QByteArray data = client->readAll();
        if(!clientAuthenticated){
            if(data.contains(CLIENT_HANDSHAKE.toUtf8())){
                client->write(SERVER_HANDSHAKE.toUtf8());
                client->flush();
                clientAuthenticated = true;
                textWidget->append("Клиент авторизован");
                serverStatus = ServerState::CLIENT_CONNECTED;
                // ================ разве это нужно в стринге?
                emit serverStatusChanged(getStringServerStatus());
            } else {
                client->write("UNKNOWN");
                client->disconnectFromHost();
            }
        }

        QString message = QString::fromUtf8(data);
        QString clientAddress = client->peerAddress().toString();
        int clientPort = client->peerPort();
        textWidget->append(QString("%1:%2> %3").arg(clientAddress).arg(clientPort).arg(message));
    }
}

void ReceiverObject::onClientDisconnected() {
    if (client) {
        textWidget->append(QString("Client disconnected: %1:%2").arg(client->peerAddress().toString()).arg(client->peerPort()));
        serverStatus = ServerState::STARTED;
        emit serverStatusChanged("Server is active. Waiting for connections...");
        client->deleteLater(); // Освободить память
        clientAuthenticated = false;

        // ---- Слушаем новые подключения снова ----
        initServer();
        serverStatus = ServerState::STARTED;
    }else {
        emit warning("Client disconnected but not correctly.");
    }
}

QString ReceiverObject::getStringServerStatus(){
    QString status;
    switch(serverStatus){
    case ServerState::STOPPED: status = "Server stopped"; break;
    case ServerState::STARTED: status = "Server started"; break;
    case ServerState::CLIENT_CONNECTED: status = "Client connected"; break;
    case ServerState::S_ERROR: status = "Error"; break;
    }

    return status;
}

void ReceiverObject::stopServer(){
    if (server->isListening()){
        server->close();
        serverStatus = ServerState::STOPPED;
        emit serverStatusChanged("Server stopped");
        textWidget->append("Server stopped.");
    }
}

void ReceiverObject::disconnectClient(){
    if(client->state() == QAbstractSocket::ConnectedState){
        client->disconnectFromHost();
        clientAuthenticated = false;
        serverStatus = ServerState::STARTED;
        emit serverStatusChanged("Server started");

        // ---- Слушаем новые подключения снова ----
        initServer();
    }else{
        emit warning("Client is not connected");
    }
}

void ReceiverObject::sendMessage(QString& message){
    if(client){
        if(client->state() == QTcpSocket::ConnectedState){
            client->write(message.toUtf8());
            client->flush();
        }else
            emit warning("Error sending message - client disconnected");
    }else{
        emit warning("Pointer error: client is null");
    }
}

QAbstractSocket::SocketState
ReceiverObject::checkClientState(){
    if(client){
        return client->state();
    }
    emit warning("Checking socket state: client is nullptr");
    return QAbstractSocket::SocketState::UnconnectedState;
}
