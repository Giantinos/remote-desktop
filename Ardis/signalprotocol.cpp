#include "signalprotocol.h"

SignalProtocol::SignalProtocol(QObject *parent)
    : QObject{parent}
{
}

void SignalProtocol::sendPacket(const QTcpSocket* socket,const QString& type, const QString &data){
    if (socket->state() == QAbstractSocket::ConnectedState) {
        if (!data.isEmpty()) {
            QString packet = type;

            packet += ":" + data;

            // emit clientEvent("Message sended");

            socket->write(packet.toUtf8());
            socket->flush();
        }
    } else {
        emit warning("Client disconnected");
        connectionStatus = ClientState::DISCONNECTED;
        emit connectionStatusChanged(connectionStatus);
    }
}
