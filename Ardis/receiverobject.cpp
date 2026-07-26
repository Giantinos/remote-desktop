#include "receiverobject.h"
#include "params.h"

ReceiverObject::ReceiverObject(QTextEdit *textWidget, QObject *parent)
    : QObject{parent}
{
    this->port = 8000;

    this->textWidget = textWidget;
    server = new QTcpServer(this);
    m_usocket = new QUdpSocket(this);

    serverStatus = ServerState::STOPPED;
    clientAuthenticated = false;

    screen = new ScreenHandler(this);
    screen->setSocket(m_usocket);

    videoStream = new ScreenReceiver(this);
    videoStream->setSocket(m_usocket);
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
    SHOWMES("== init server start");
    if(port == 0){
        emit warning("Port not initialized");
        return;
    }
    // Пытаемся прослушивать на указанном порту
    if(isCorrectPort()){
        SHOWMES("== port: ok");
        if (!server->listen(QHostAddress::Any, port)) { // QHostAddress::Any слушает на всех доступных сетевых интерфейсах
            emit serverStatusChanged("Error starting server");
            emit warning(QString("Can`t start server at port %1. Error: %2").arg(port).arg(server->errorString()));
            serverStatus = ServerState::S_ERROR;
            server->deleteLater();
        } else {
            QString listenAddress = server->serverAddress().toString();
            if (listenAddress.isEmpty() || listenAddress == "0.0.0.0") {
                SHOWMES("== listen all interfaces");
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

// ---- UDP ----

void ReceiverObject::startUdpListening(){
    qDebug() << ">> startUdpListening()";
    if(m_usocket->bind(m_uport)){

        connect(m_usocket, &QUdpSocket::readyRead,
                this, &ReceiverObject::onUdpDataReceived);
    }else {
        emit warning("Error: couldnt binding UDP port");
    }
}

void ReceiverObject::stopUdpListening(){
    m_usocket->close();

    // очистить буферы
    ubuffer.clear();
    // m_expectedSize = 0;
}
// рабочий
void ReceiverObject::writeUdpDatagram(QByteArray& data){
    qDebug() << "Writing datagram ip: " << m_uaddress << ":" << m_uport;
    qint64 sent =  m_usocket->writeDatagram(data,
                             m_uaddress,
                             m_uport);

    qDebug() << "Sent bytes:" << sent << "Expected:" << data.size();

    if (sent == -1) {
        qDebug() << "Send error:" << m_usocket->errorString();
    }
}
// не используется
void ReceiverObject::writeUdpTest(){
    QByteArray data;
    QString s = "TEST UDP DATA";
    data = s.toUtf8();
    m_usocket->writeDatagram(data,
                             m_uaddress,
                             m_uport);
}

void ReceiverObject::sendChunks(const QVector<DataChunk> &chunks) {
    for (const auto &chunk : chunks) {
        QByteArray packet;
        QDataStream stream(&packet, QIODevice::WriteOnly);
        stream << chunk.id << chunk.total << chunk.current << chunk.data;
        ReceiverObject::writeUdpDatagram(packet);
    }
}

void ReceiverObject::onUdpDataReceived(){
    qDebug() << ">> ReceiverObject::onUdpDataReceived()";

    while(m_usocket->hasPendingDatagrams()){
        QByteArray buffer;
        buffer.resize(m_usocket->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        m_usocket->readDatagram(buffer.data(), buffer.size(),
                                &sender, &senderPort);
    }
}
// ^^^^ UDP ^^^^



bool ReceiverObject::isCorrectPort(){
    return this->port >= 1 && this->port<= 65535 ? true : false;
}

bool ReceiverObject::isCorrectPort(int port){
    return port >= 1 && port <= 65535 ? true : false;
}

void ReceiverObject::onNewConnection() {
    SHOWMES("== on new conenction");
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
// TCP
void ReceiverObject::onReadyRead() {
    /*sender() - это встроенный метод библиотеки Qt,
    который используется внутри слотов (обработчиков сигналов).
    Он возвращает указатель на объект, который отправил (сгенерировал) сигнал,
    вызвавший этот слот.*/

    if (client) {
        QByteArray data = client->readAll();

        if(!clientAuthenticated){
            handshakeProcess(data);
        }

        // елсе разбор команд в сообщении
        QString message = QString::fromUtf8(data);
        signalParse(message);

    }
}

void ReceiverObject::handshakeProcess(QByteArray& data){
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

void ReceiverObject::signalParse(const QString& message){
    qDebug() << "[Server] handling message " << message;
    SHOWMES("[Server] handling message " + message);
    // .mid(i) возвращает строку с индекса i
    if (message.startsWith("MSG:")) {
        QString text = message.mid(4);
        handleChatMessage(text);
    } else if (message.startsWith("CMD:")) {
        QString command = message.mid(4);
        handleCommand(command);
    } else {
        emit warning("Unknown packet type:" + message);
        qWarning() << "Unknown packet type:" << message;
    }
}

void ReceiverObject::handleChatMessage(const QString& message){
    QString clientAddress = client->peerAddress().toString();
    int clientPort = client->peerPort();
    textWidget->append(QString("%1:%2> %3").arg(clientAddress).arg(clientPort).arg(message));
}

void ReceiverObject::handleCommand(const QString& cmd){
    qDebug() << "[Server] handling " + cmd;
    SHOWMES("[Server] handling " + cmd);
    if(cmd == "START_SSCREENCAST"){
        // отправка клиенту сообщение для инициализации udp соединения
        qDebug() << "[Server] sending signal message to client init udp";
        SHOWMES("[Server] sending signal message to client init udp");
        startServerScreencast();
        connect(screen, &ScreenHandler::frameCaptured,
                this, &ReceiverObject::sendChunks);
        textWidget->setText(">> CMD:" + cmd);
        screen->startCapture();


        // отправить по тсп CMD:INIT_UDP
        // sendInitUdpExchange();

        // чтобы начать механизм обмена по udp (клиент отправит инит-пакет)

        // сервер начинает слушать udp
        // начинает трансляцию

        // клиент начинает слушать юдп
    }else if(cmd == "STOP_SSCREENCAST"){
        //отправить клиенту команду о прекращении слушать юдп
        SHOWMES("[Server] stop screencast");
        qDebug() << "[Server] stop screencast";
        screen->stopCapture();
        stopScreencast();
        stopUdpListening();
        disconnect(screen, &ScreenHandler::frameCaptured,
                   this, &ReceiverObject::sendChunks);
        // прекратить трансу
    }else if(cmd == "START_CSCREENCAST"){
    // отправить клиенту подтверждение
        // начать слушать юдп
    // получить отклиента инициальный пакет юдп
    } else if(cmd == "STOP_CSCREENCAST"){
    // прекратить слушать юдп
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

    auto executeCloseServer= [this]() {
        if (server && server->isListening()) {
            server->close();
            serverStatus = ServerState::STOPPED;
            emit serverStatusChanged("Server stopped");
            if (textWidget) {
                textWidget->append("Server stopped.");
            }
        }
    };
    if(hasActiveClient()){
        if(client->state() == QAbstractSocket::ConnectedState){
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(nullptr,
                                          "Warning",           // Заголовок
                                          "The server has an active connection. Do you want to disconnect it?",             // Текст
                                          QMessageBox::Ok | QMessageBox::Cancel);  // Кнопки

            if (reply == QMessageBox::Ok) {
                disconnectClient();
                executeCloseServer();
            }
        }
    } else executeCloseServer();
}

bool ReceiverObject::hasActiveClient()  {
    return client && client->state() == QAbstractSocket::ConnectedState;
}

void ReceiverObject::disconnectClient(){
    qDebug() << ">> Disconnecting client";
    if(client->state() == QAbstractSocket::ConnectedState){
        qDebug() << ">> ClientsocketState : " << client->state();
        qDebug() << ">> Disconnecting client: client->disconnectFromHost()";
        client->disconnectFromHost();
        clientAuthenticated = false;
        qDebug() << ">> Changing server status";
        serverStatus = ServerState::STARTED;
        emit serverStatusChanged("Server started");

        // ---- Слушаем новые подключения снова ----
        // initServer();
    }else{
        qDebug() << ">> ClientsocketState : " << client->state();
        qDebug() << ">> Throwing Warning";
        emit warning("Client is not connected");
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

// ---- Сетевые методы ----
// TCP
void ReceiverObject::sendPacket(const QString& type, const QString &data){
    if (client->state() == QAbstractSocket::ConnectedState) {
        if (!data.isEmpty()) {
            QString packet = type;

            packet += ":" + data;

            client->write(packet.toUtf8());
            client->flush();
        }
    } else {
        emit warning("State is disconnected");
    }
}

void ReceiverObject::sendMessage(const QString& text){
    sendPacket("MSG", text);
}
void ReceiverObject::startServerScreencast() {
    sendPacket("CMD", "START_SSCREENCAST");
}
void ReceiverObject::stopServerScreencast(){
    sendPacket("CMD", "STOP_SSCREENCAST");
}
void ReceiverObject::startScreencast(){
    sendPacket("CMD", "START_CSCREENCAST");
}
void ReceiverObject::stopScreencast(){
    sendPacket("CMD", "STOP_CSCREENCAST");
}

void ReceiverObject::setUdpPort(int l_port){
    if(isCorrectPort(l_port))
        this->m_uport = l_port;
    else emit warning("Invalid port");
}
void ReceiverObject::setUdpAddress(QString addr){
    QHostAddress a(addr);
    if(!a.isNull() && a.protocol() == QAbstractSocket::IPv4Protocol)
        this->m_uaddress.setAddress(addr);
    else emit warning("Invalid address");
}

