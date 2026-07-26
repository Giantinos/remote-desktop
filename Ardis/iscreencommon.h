#ifndef ISCREENCOMMON_H
#define ISCREENCOMMON_H

#include <QObject>
#include <Qpixmap>
#include <QImage>
#include <QByteArray>
#include <QTimer>

struct ScreenCaptureConfig{
    int fps = 15;
    int quality = 80;
    QSize resolution = QSize(1920, 1080);
    bool captureCursor = true;
};

class IScreenBase : public QObject{
    Q_OBJECT
    public:
        explicit IScreenBase(QObject* parent = nullptr);

    protected:
        QByteArray compressImage(const QPixmap& pixmap, int quality = 80);

        QPixmap scaleImage(const QPixmap& pixmap, const QSize& targetSize);

        ScreenCaptureConfig m_config;
};

#endif // ISCREENCOMMON_H
