#ifndef SENDERCLIENT_H
#define SENDERCLIENT_H

// #include <QApplication>
// #include <QLocale>
// #include <QTranslator>
// #include <QLineEdit>
// #include <QTextEdit>
// #include <QPushButton>
// #include <QLabel>
// #include <QVBoxLayout>
#include "params.h"
#include <QTcpSocket>
#include <QTcpServer>
#include <QMessageBox>
#include <QHostAddress>
#include <QTimer>
#include <QTextEdit>



class SenderClient : public QObject
{
    Q_OBJECT
public:
    explicit SenderClient(QTextEdit *textWidget = nullptr,QWidget *parent = nullptr);
    void setHostParameters(QString hostAddress, int hostPort);
    void setHostIp(QString hostAddress);
    void setHostPort(int hostPort);
    void sendMessage(QString message);
    void connectToHost();
    int getConnectionStatus();
    QString getErrorMessage();
    QString getWarningMessage();
    QString getStringConnectionStatus();

public slots:
    void disconnectFromHost();

private:
    // QLineEdit *inputField;

    // QPushButton *sendButton;
    // QPushButton *connectButton;
    // QPushButton *applyNetworkSettingsButton;
    // QLabel *statusLabel;
    QTcpSocket *socket;
    QString hostAddress;
    QTextEdit *textWidget;
    int hostPort;
    int connectionStatus;
    QString errorMessage;
    QString warningMessage;
    bool isCorrectIp();
    bool isCorrectPort();
    bool isCorrectIp(QString ip);
    bool isCorrectPort(int port);
    bool isServerAuthentificated;
    bool isIntentionalDisconnect;
    unsigned handshakeTime = 3000;
    void printMessage(QString m);

private slots:
    void onSocketError(QAbstractSocket::SocketError socketError);
    void onDisconnected();
    void onTcpConnected();
    void onReadyRead();

signals:
    // сигнал для отображения статуса подключения
    void connectionStatusChanged(const int status);
    void warning(const QString message);
    void clientEvent(const QString message);
    void messageReceived(QByteArray data);
    // void sendingMessage(QString message);
};

enum ClientState{
    DISCONNECTED,
    CONNECTING,
    CONNECTED,
    C_ERROR
};

#endif // SENDERCLIENT_H
