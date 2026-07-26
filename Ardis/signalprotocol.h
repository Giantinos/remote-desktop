#ifndef SIGNALPROTOCOL_H
#define SIGNALPROTOCOL_H

#include <QObject>

class SignalProtocol : public QObject
{
    Q_OBJECT
public:
    explicit SignalProtocol(QObject *parent = nullptr);

signals:
};

#endif // SIGNALPROTOCOL_H
