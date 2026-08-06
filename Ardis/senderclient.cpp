#include "senderclient.h"

SenderClient::SenderClient(QTextEdit *textWidget,QWidget *parent) : QObject(parent)
{
    m_socket = new QTcpSocket(this);
    m_usocket = new QUdpSocket(this);
    connectionStatus = ClientState::DISCONNECTED;

    // написать приём udp
    //     сделать кнопки управления udp соединением
    //         выводить udp на виджет

    screen = new ScreenHandler(parent);
    videoStream = new ScreenReceiver(parent);
    videoStream->setSocket(m_usocket);
    // videoStream->setDisplayWidget()

    if(textWidget){
        this->textWidget = textWidget;
    }

    isServerAuthentificated = false;

    isIntentionalDisconnect = false;
}

void SenderClient::setDisplayWidget(QLabel* display){
    if(display){
        videoStream->setDisplayWidget(display);
    } else {
        qDebug() << "Cant set display widget";
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
    DEBUG("[Client] Trying connect to host");
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
        emit warning("Already connecting");
        return;
    }

    if(connectionStatus == ClientState::CONNECTED){
        emit warning("Already connected");
        return;
    }
    if (!m_socket) {
        qDebug() << "trying to make new QTcpm_socket";
        DEBUG("[Client] trying to make new QTcp m_socket");
        m_socket = new QTcpSocket(this);
        qDebug() << "Created new m_socket";
        DEBUG("[Client] socket created");
    }
    qDebug() << "Checking m_socket for (m_socket && m_socket->state() != QTcpm_socket::UnconnectedState)";
    qDebug() << "m_socket > " << m_socket;
    qDebug() << "m_socket->state() > " << m_socket->state();
    if (m_socket && m_socket->state() != QTcpSocket::UnconnectedState) {
        m_socket->disconnectFromHost();
        m_socket->abort();
        qDebug() << "aborting m_socket";
        DEBUG("[Client] aborting socket");
        m_socket->deleteLater();
        m_socket = nullptr;
        isServerAuthentificated = false;
    }
    qDebug() << "checked";
    qDebug() << "disconnecting old m_socket signals";

    // отключение старого соединения
    disconnect(m_socket, nullptr, this, nullptr);

    connect(m_socket, &QTcpSocket::connected,
            this, &SenderClient::onTcpConnected);
    connect(m_socket, &QTcpSocket::readyRead,
            this, &SenderClient::onReadyRead);
    connect(m_socket, &QTcpSocket::disconnected,
            this, &SenderClient::onDisconnected);
    connect(m_socket, &QTcpSocket::errorOccurred,
            this, &SenderClient::onSocketError);
    // connect(m_socket, &QTcpm_socket::stateChanged, this, &SenderClient::onm_socketStateChanged);

    connectionStatus = ClientState::CONNECTING;
    emit connectionChanged(connectionStatus);
    qDebug() << "Connecting to " << hostAddress << " : " << hostPort;
    DEBUG("[Client] Connecting to " + hostAddress + " : " + QString::number(hostPort));
    isServerAuthentificated = false;
    m_socket->connectToHost(hostAddress, hostPort);

    QTimer::singleShot(CONNECTION_TIMEOUT, this, [this](){
        if(connectionStatus != ClientState::CONNECTED){
            connectionStatus = ClientState::DISCONNECTED;

            emit connectionChanged(connectionStatus);
            emit warning("Connection timeout");

            if(m_socket){
                m_socket->abort();
            }
        }
    });
}

void SenderClient::onTcpConnected(){
    qDebug(">> tcp connected");
    m_socket->write(CLIENT_HANDSHAKE.toUtf8());
    m_socket->flush();
    qDebug(">> handshake sended");

    QTimer::singleShot(handshakeTime, this, [this](){
        if(!isServerAuthentificated){
            m_socket->abort();
            connectionStatus = ClientState::DISCONNECTED;
            emit connectionChanged(connectionStatus);
            emit warning("Server did not respond to handshake");
        }
    });
}

void SenderClient::onReadyRead(){
    QByteArray data = m_socket->readAll();
    qDebug() << "cheking auth server";
    if(!isServerAuthentificated){
        qDebug() << "Not server isnt auth";
        if(data.contains(SERVER_HANDSHAKE.toUtf8())){
            qDebug() << "Auth done. HANDSHAKING";
            showMessage("Server is authentificated");
            showMessage(QString("Server: %1").arg(SERVER_HANDSHAKE));
            isServerAuthentificated = true;
            connectionStatus = ClientState::CONNECTED;
            emit connectionChanged(connectionStatus);
            showMessage("Server authorized.");
        }else{
            qDebug() << "Auth failed. m_socket Aborting";
            m_socket->abort();
            emit warning("Invalid server response");
        }
    } else {
        signalParse(data);
        showMessage(QString("Server: %1").arg(data));
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

// void SenderClient::sendMessage(QString message) {
//     if (m_socket->state() == QAbstractSocket::ConnectedState) {
//         if (!message.isEmpty()) {
//             m_socket->write(message.toUtf8());
//             m_socket->flush();
//             // emit clientEvent("Message sended");
//         }
//     } else {
//         emit warning("Connection lost");
//         connectionStatus = ClientState::DISCONNECTED;
//         emit connectionChanged(connectionStatus);
//     }
// }


void SenderClient::onSocketError(QAbstractSocket::SocketError socketError) {
    Q_UNUSED(socketError);
    qDebug() << QString("m_socket Error: %1").arg(m_socket->errorString());
    // errorMessage = QString("Ошибка сокета: %1").arg(m_socket->errorString());
    connectionStatus = ClientState::C_ERROR;
    emit connectionChanged(connectionStatus);
    emit warning(QString("Socker error %1").arg(m_socket->errorString()));
}

void SenderClient::disconnectFromHost(){
    if(!m_socket) return;
    if(m_socket->state() == QAbstractSocket::ConnectedState){
        isIntentionalDisconnect = true;
        m_socket->disconnect();
        m_socket->disconnectFromHost();
        if(m_socket && m_socket->state() != QTcpSocket::UnconnectedState){
            m_socket->waitForDisconnected(2000);
        }
        if (m_socket && m_socket->state() != QTcpSocket::UnconnectedState) {
            m_socket->abort();
        }
    } else {
        emit warning("Connection is not exist");
    }
    connectionStatus = ClientState::DISCONNECTED;
    emit connectionChanged(connectionStatus);
}

void SenderClient::onDisconnected() {
    qDebug() << ">> onDisconnected()";
    if(!isIntentionalDisconnect){
        qDebug() << ">> NOT Intentional disconnect";
        connectionStatus = ClientState::DISCONNECTED;
        emit connectionChanged(connectionStatus);
        emit warning("Host connection lost");
    }else qDebug() << ">> Intentional disconnect!";
    qDebug() << ">> Deleting m_socket memory";
    m_socket->deleteLater(); // Освободить память
    m_socket = nullptr;
    qDebug() << ">> m_socket = nulltpr";
    isIntentionalDisconnect = false;
}

void SenderClient::showMessage(QString message){
    textWidget->append(message);
}

// трансляция клиента
// void SenderClient::startScreencast(){
//     screen->startCapture();
// }

// ---- Сетевые методы ----
// TCP common
void SenderClient::sendPacket(const QString& type, const QString &data){
    if (m_socket->state() == QAbstractSocket::ConnectedState) {
        if (!data.isEmpty()) {
            QString packet = type;

            packet += ":" + data;

            // emit clientEvent("Message sended");

            m_socket->write(packet.toUtf8());
            m_socket->flush();
        }
    } else {
        emit warning("Client disconnected");
        connectionStatus = ClientState::DISCONNECTED;
        emit connectionChanged(connectionStatus);
    }
}

void SenderClient::sendMessage(const QString& text){
    sendPacket("MSG", text);
}
void SenderClient::startServerScreencast() {
    sendPacket("CMD", "START_SSCREENCAST");
    videoStream->startReceiving();
}
void SenderClient::stopServerScreencast(){
    sendPacket("CMD", "STOP_SSCREENCAST");
    videoStream->stopReceiving();
}
void SenderClient::startScreencast(){
    sendPacket("CMD", "START_CSCREENCAST");
}
void SenderClient::stopScreencast(){
    sendPacket("CMD", "STOP_CSCREENCAST");
}

void SenderClient::signalParse(const QString& message){
    qDebug() << "== [Client] received message: " + message;
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

void SenderClient::handleChatMessage(const QString& message){
    QString clientAddress = m_socket->peerAddress().toString();
    // для отображения
    int clientPort = m_socket->peerPort();
    textWidget->append(QString("%1:%2> %3").arg(clientAddress).arg(clientPort).arg(message));
}

void SenderClient::handleCommand(const QString& cmd){
    showMessage("[Client] handling " + cmd);
    qDebug() << "[Client] handling " + cmd;
    if(cmd == "START_SSCREENCAST"){
        showMessage("[Client] processing...");
        qDebug() << "[Client] try to send init udp";
        // отправить по тсп CMD:INIT_UDP

        writeUdpDatagram();

        // чтобы начать механизм обмена по udp (клиент отправит инит-пакет)

        // сервер начинает слушать udp
        // начинает трансляцию

        // клиент начинает слушать юдп
    }else if(cmd == "STOP_SSCREENCAST"){
        //отправить клиенту команду о прекращении слушать юдп
        // прекратить трансу
        // stopUdpListening();
    }else if(cmd == "START_CSCREENCAST"){
        // отправить клиенту подтверждение
        // начать слушать юдп
        // получить отклиента инициальный пакет юдп
    } else if(cmd == "STOP_CSCREENCAST"){
        // прекратить слушать юдп
    }
}

// ---- UDP ----

// void SenderClient::startUdpListening(){
//     if(m_usocket->bind(hostPort)){
//         connect(m_usocket, &QUdpSocket::readyRead,
//                 this, &ScreenReceiver::startReceiving);
//     }else {
//         emit warning("Error: couldnt start UDP listening");
//     }
// }

void SenderClient::stopUdpListening(){
    m_usocket->close();

    // очистить буферы
    ubuffer.clear();
    // m_expectedSize = 0;
}

// void SenderClient::onUdpDataReceived(){
//     // while(m_usocket->hasPendingDatagrams()){
//     //     // QByteArray buffer;
//     //     ubuffer.resize(m_usocket->pendingDatagramSize());

//     //     QHostAddress sender;
//     //     quint16 senderPort;

//     //     m_usocket->readDatagram(ubuffer.data(), ubuffer.size(),
//     //                             &sender, &senderPort);
//     // }
//     videoStream->onSocketReadyRead());
// }

// UNSAFE check socket
void SenderClient::writeUdpDatagram(){
    showMessage("[Client] writing initial udp packet " + m_uaddress.toString() + ":" + QString::number(m_uport));
    qDebug() << "[Client] writing initial udp packet " << m_uaddress << ":" << m_uport ;
    m_usocket->writeDatagram("VIDEO_INIT",
                               m_uaddress,
                               m_uport);
}
// ^^^^ UDP ^^^^