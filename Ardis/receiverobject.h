#ifndef RECEIVEROBJECT_H
#define RECEIVEROBJECT_H

#include <QObject>
#include <QTextEdit>
// #include <QPushButton>
// #include <QLabel>
// #include <QVBoxLayout>
#include <QTcpSocket>
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
    void sendMessage(QString& message);
    QAbstractSocket::SocketState checkClientState();


private slots:
    void onNewConnection();
    void onReadyRead();
    void onClientDisconnected();
    bool hasActiveClient();

private:
    int port;
    QTextEdit *textWidget;
    bool isCorrectPort();
    bool isCorrectPort(int port);
    QTcpServer *server;
    int serverStatus;
    QTcpSocket *client;
    bool clientAuthenticated;

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
