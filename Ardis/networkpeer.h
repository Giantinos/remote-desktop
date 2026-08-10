#ifndef NETWORKPEER_H
#define NETWORKPEER_H
#include <QNetworkAccessManager>
#include <QTcpServer>

#include <QObject>

// класс который совмещает клиента и сервера в одном
// отвечает за сетевое взаимодействие приложения
class NetworkPeer : public QObject
{
    Q_OBJECT
public:
    explicit NetworkPeer(QObject *parent = nullptr);
    void setClient(QTcpSocket *socket = nullptr);
    void setServer(QTcpServer *server = nullptr);
    void sendMessage(const QString& text);
    void startServerScreencast();
    void stopServerScreencast();
    void startScreencast();
    void stopScreencast();
    void sendKeyboardControls(const QString& keys);

public slots:

private:
    QTcpSocket *client = nullptr;
    QTcpServer *server = nullptr;
    void sendPacket(const QString& type, const QString &data);



signals:
};

#endif // NETWORKPEER_H
