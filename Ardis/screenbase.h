#ifndef SCREENBASE_H
#define SCREENBASE_H

#include <QObject>
#include <Qpixmap>
#include <QImage>
#include <QByteArray>
#include <QTimer>
#include <QNetworkInterface>
#include "common.h"//;

struct ScreenCaptureConfig{
    int fps = 10;
    int quality = 70;
    QSize resolution = QSize(1920, 1080);
    bool captureCursor = true;
};

const int CHUNK_SIZE = 60000;

struct DataChunk{
    int id; // id изображения
    int total; // всего фрагментов
    int current; // текущая часть (0-based)
    QByteArray data; // данные фрагмента
};

class ScreenBase : public QObject{
    Q_OBJECT
public:
    explicit ScreenBase(QObject* parent = nullptr);

protected:
    QByteArray compressImage(const QPixmap& pixmap, int quality = 70);

    QPixmap scaleImage(const QPixmap& pixmap, const QSize& targetSize);

    ScreenCaptureConfig m_config;
};

#endif // SCREENBASE_H
