#include "networkpeer.h"
using np = NetworkPeer;
NetworkPeer::NetworkPeer(QObject *parent)
    : QObject{parent}
{

}

void np::setClient(QTcpSocket *socket){
    // не информативный выход, исправить
    if(socket == nullptr)
        return;
    this->client = socket;
}

void np::setServer(QTcpServer *server){
    if(server == nullptr){
        return;
    }
    this->server = server;
}

void np::sendMessage(const QString& text){
    sendPacket("MSG", text);
}
void np::startServerScreencast() {
    sendPacket("CMD", "START_SSCREENCAST");
}
void np::stopServerScreencast(){
    sendPacket("CMD", "STOP_SSCREENCAST");
}
void np::startScreencast(){
    sendPacket("CMD", "START_CSCREENCAST");
}
void np::stopScreencast(){
    sendPacket("CMD", "STOP_CSCREENCAST");
}
void np::sendKeyboardControls(const QString& keys){
    sendPacket("KBC", keys);
}

void np::sendPacket(const QString& type, const QString &data){
    if (client->state() == QAbstractSocket::ConnectedState) {
        if (!data.isEmpty()) {
            QString packet = type;

            packet += ":" + data;

            client->write(packet.toUtf8());
            client->flush();
        }
        return;
    }
    // emit warning("State is disconnected");
}
