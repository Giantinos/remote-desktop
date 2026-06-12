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
#include <QTcpSocket>
#include <QTcpServer>
#include <QMessageBox>
#include <QHostAddress>
#include <QTimer>

// --- Параметры сети ---
const int DEFAULT_PORT = 12345; // Порт, на котором будет работать сервер
const QString DEFAULT_HOST = "127.0.0.1"; // IP-адрес по умолчанию (localhost)
const int CONNECTION_TIMEOUT = 3000; // Таймаут на подключение

class SenderClient : public QObject
{
    Q_OBJECT
public:
    explicit SenderClient(QWidget *parent = nullptr);
    void setHostParameters(QString hostAddress, int hostPort);
    void setHostIp(QString hostAddress);
    void setHostPort(int hostPort);
    void sendMessage(QString message);
    void connectToHost();
    void disconnectFromHost();
    int getConnectionStatus();
    QString getErrorMessage();
    QString getWarningMessage();
    QString getStringConnectionStatus();
    // explicit SenderClient(const QString& hostAddress, int port, QWidget *parent = nullptr);

private:
    // QLineEdit *inputField;

    // QPushButton *sendButton;
    // QPushButton *connectButton;
    // QPushButton *applyNetworkSettingsButton;
    // QLabel *statusLabel;
    QTcpSocket *socket;
    QString hostAddress;
    int hostPort;
    int connectionStatus;
    QString errorMessage;
    QString warningMessage;
    bool isCorrectIp();
    bool isCorrectPort();
    bool isCorrectIp(QString ip);
    bool isCorrectPort(int port);
    void onConnected();

private slots:
    void onSocketError(QAbstractSocket::SocketError socketError);
    void onDisconnected();

signals:
    // сигнал для отображения статуса подключения
    void connectionStatusChanged(const int status);
    void warning(const QString message);
    void clientEvent(const QString message);
};

enum ClientState{
    DISCONNECTED,
    CONNECTING,
    CONNECTED,
    C_ERROR
};

#endif // SENDERCLIENT_H
