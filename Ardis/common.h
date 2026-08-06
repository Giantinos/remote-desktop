#ifndef COMMON_H
#define COMMON_H

#include <QObject>

#define DEBUG(msg) Common::instance()->debug(msg)

class Common : public QObject
{
    Q_OBJECT
public:
    explicit Common(QObject *parent = nullptr);
    static Common *instance();
    void debug(const QString& message);

private:
    static Common* m_instance;
    // QTime* timer;

signals:
    void debugSignal(const QString& message);
};

#endif // COMMON_H
