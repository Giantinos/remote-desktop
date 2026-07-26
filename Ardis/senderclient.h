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
#include "screenhandler.h"
#include "screenreceiver.h"
#include <QTcpSocket>
#include <QUdpSocket>
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
    void connectToHost();
    int getConnectionStatus();
    QString getErrorMessage();
    QString getWarningMessage();
    QString getStringConnectionStatus();
    void setDisplayWidget(QLabel* display);

public slots:
    void disconnectFromHost();
    void sendMessage(const QString& text);
    void startServerScreencast();
    void stopServerScreencast();
    void startScreencast();
    void stopScreencast();
    void setUdpAddress(QString address){
        QHostAddress a(address);
        if(!a.isNull() && a.protocol() == QAbstractSocket::IPv4Protocol)
            this->m_uaddress.setAddress(address);
        else emit warning("Invalid address");
    }
    void setUdpPort(int port){
        if(isCorrectPort(port))
            this->m_uport = port;
        else emit warning("Invalid port");
    }
    // для отладки
    void SHOWMES(QString s){
        textWidget->setText(s);
    }
    QHostAddress& getUdpAddress(){
        return m_uaddress;
    }

private:
    QTcpSocket *m_socket;
    QUdpSocket *m_usocket;
    QString hostAddress;
    QTextEdit *textWidget;
    int hostPort;
    int connectionStatus;
    int m_uport = 8001;
    QHostAddress m_uaddress;
    QString errorMessage;
    QString warningMessage;
    bool isCorrectIp();
    bool isCorrectPort();
    bool isCorrectIp(QString ip);
    bool isCorrectPort(int port);
    bool isServerAuthentificated;
    bool isIntentionalDisconnect;
    unsigned handshakeTime = 3000;
    void showMessage(QString m);
    void startSreencast();
    ScreenHandler* screen;
    ScreenReceiver* videoStream;
    void sendPacket(const QString& type, const QString &data = QString());
    void signalParse(const QString& message);
    void handleChatMessage(const QString& message);
    void handleCommand(const QString& cmd);
    void writeUdpDatagram();
    QByteArray ubuffer;

private slots:
    void onSocketError(QAbstractSocket::SocketError socketError);
    void onDisconnected();
    void onTcpConnected();
    void onReadyRead();
    // void startUdpListening();
    void stopUdpListening();
    // void onUdpDataReceived();

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
