#ifndef RECEIVEROBJECT_H
#define RECEIVEROBJECT_H

#include "screenreceiver.h"
#include "screenhandler.h"
#include <QObject>
#include <QTextEdit>
// #include <QPushButton>
// #include <QLabel>
// #include <QVBoxLayout>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QHostAddress>
#include <QTcpServer>
#include <QTimer>
#include <QMessageBox>
// #include <QTextBrowser>


class ReceiverObject : public QObject
{
    Q_OBJECT
public:
    explicit ReceiverObject(QTextEdit *textWidget,QObject *parent = nullptr);
    void initServer();
    void setPort(int port);
    void stopServer();
    void disconnectClient();
    int getServerStatus();
    QString getStringServerStatus();
    QAbstractSocket::SocketState checkClientState();
    void setUdpAddress(QString addr);
    void setUdpPort(int port);
// для отладки
    void SHOWMES(QString s){
        textWidget->setText(s);
    }

public slots:
    void sendMessage(const QString& text);
    void startServerScreencast();
    void stopServerScreencast();
    void startScreencast();
    void stopScreencast();
    // для разработки
    QHostAddress& getUdpAddress(){
        return m_uaddress;
    }


private slots:
    void onNewConnection();
    void onReadyRead();
    void onUdpDataReceived();
    void onClientDisconnected();
    bool hasActiveClient();
    void sendPacket(const QString& type, const QString &data = QString());
    void writeUdpDatagram(QByteArray& data);
    void sendChunks(const QVector<DataChunk> &chunks);
    void writeUdpTest();

private:
    int port;
    int m_uport = 8001;
    QHostAddress m_uaddress;
    QTextEdit *textWidget;
    bool isCorrectPort();
    bool isCorrectPort(int port);
    QTcpServer *server;
    int serverStatus;
    QTcpSocket *client;
    QUdpSocket* m_usocket;
    QByteArray ubuffer;
    bool clientAuthenticated;
    void handshakeProcess(QByteArray& data);
    // Парсит сигнал и выполняет команду
    void signalParse(const QString& message = QString());
    void handleChatMessage(const QString& message = QString());
    void handleCommand(const QString& message = QString());
    void startUdpListening();
    void stopUdpListening();
    ScreenHandler* screen;
    ScreenReceiver* videoStream;


signals:
    void serverStatusChanged(QString message);
    void warning(QString message);
};

enum ServerState{
    STOPPED,
    STARTED,
    CLIENT_CONNECTED,
    S_ERROR
};

#endif // RECEIVEROBJECT_H
