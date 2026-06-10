#include "receiverobject.h"

ReceiverObject::ReceiverObject(QTextEdit *textWidget, QObject *parent)
    : QObject{parent}
{

    this->port = 8000;

    // QVBoxLayout *layout = new QVBoxLayout(this);
    // layout->addWidget(receivedMessages);
    // layout->addWidget(statusLabel);
    this->textWidget = textWidget;
    server = new QTcpServer(this);

    // emit serverStatusChanged("Server not started");
    serverStatus = ServerState::STOPPED;
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
        if(!server) qDebug() <<"pizdec";
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
    if (clientSocket) {
        QString clientAddress = clientSocket->peerAddress().toString();
        int clientPort = clientSocket->peerPort();
        textWidget->append(QString("New Client Connected: %1:%2").arg(clientAddress).arg(clientPort));
        emit serverStatusChanged(QString("Client connected (%1:%2)").arg(clientAddress).arg(clientPort));
        serverStatus = ServerState::CLIENT_CONNECTED;

        connect(clientSocket, &QTcpSocket::readyRead, this, &ReceiverObject::onReadyRead);
        connect(clientSocket, &QTcpSocket::disconnected, this, &ReceiverObject::onClientDisconnected);
        client = clientSocket;
        //############## подключения бльше не принимаются
        server->close();
        //##############
    }
}

void ReceiverObject::onReadyRead() {
    /*sender() - это встроенный метод библиотеки Qt,
    который используется внутри слотов (обработчиков сигналов).
    Он возвращает указатель на объект, который отправил (сгенерировал) сигнал,
    вызвавший этот слот.*/

    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    if (clientSocket) {
        QByteArray data = clientSocket->readAll();
        QString message = QString::fromUtf8(data);
        QString clientAddress = clientSocket->peerAddress().toString();
        int clientPort = clientSocket->peerPort();
        textWidget->append(QString("%1:%2> %3").arg(clientAddress).arg(clientPort).arg(message));
    }
}

void ReceiverObject::onClientDisconnected() {
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    serverStatus = ServerState::STARTED;
    if (clientSocket) {
        QString clientAddress = clientSocket->peerAddress().toString();
        int clientPort = clientSocket->peerPort();
        textWidget->append(QString("Client disconnected: %1:%2").arg(clientAddress).arg(clientPort));
        serverStatus = ServerState::STARTED;
        emit serverStatusChanged("Server is active. Waiting for connections...");
        clientSocket->deleteLater(); // Освободить память
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
        serverStatus = ServerState::STARTED;
        emit serverStatusChanged("Server started");
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
