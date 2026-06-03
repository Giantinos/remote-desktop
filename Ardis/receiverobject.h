#ifndef RECEIVEROBJECT_H
#define RECEIVEROBJECT_H

#include <QObject>
#include <QTextEdit>
// #include <QPushButton>
// #include <QLabel>
// #include <QVBoxLayout>
#include <QTcpSocket>
#include <QTcpServer>
// #include <QMessageBox>
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
    QString getServerStatus();

private slots:
    void onNewConnection();
    void onReadyRead();
    void onClientDisconnected();

private:
    int port;
    QTextEdit *textWidget;
    bool isCorrectPort();
    bool isCorrectPort(int port);
    QTcpServer *server;
    QString serverStatus;
    QTcpSocket *client;

signals:
    void serverStatusChanged(QString message);
    void warning(QString message);
};

enum StatusConnectionStatus{
    SERVER_STOPPED,
    SERVER_STARTED,
    ON_CONNECTED_CLIENT,
    ON_ERROR
};

#endif // RECEIVEROBJECT_H
