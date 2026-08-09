#ifndef NETWORKPEER_H
#define NETWORKPEER_H

#include <QObject>

class NetworkPeer : public QObject
{
    Q_OBJECT
public:
    explicit NetworkPeer(QObject *parent = nullptr);

signals:
};

#endif // NETWORKPEER_H
