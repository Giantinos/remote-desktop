#include "screenbase.h"

#include <QBuffer>
#include <QImageWriter>

ScreenBase::ScreenBase(QObject* parent) : QObject(parent) {
    // Настройки по умолчанию
    m_config.fps = 10;
    m_config.quality = 80;
    m_config.resolution = QSize(1920, 1080);
    m_config.captureCursor = true;
}

QByteArray ScreenBase::compressImage(const QPixmap& pixmap, int quality) {
    if (pixmap.isNull()) {
        return QByteArray();
    }

    // Конвертируем в QImage
    QImage image = pixmap.toImage();

    // Настраиваем сжатие
    QByteArray bytes;
    QBuffer buffer(&bytes);
    buffer.open(QIODevice::WriteOnly);

    QImageWriter writer(&buffer, "JPEG");
    writer.setQuality(quality);

    if (!writer.write(image)) {
        qDebug() << "Failed to compress image:" << writer.errorString();
        return QByteArray();
    }

    return bytes;
}

// изменение размера с сохранением пропорций
// нужна проверка на isNull()
QPixmap ScreenBase::scaleImage(const QPixmap& screenshot, const QSize& targetSize){
    if (screenshot.isNull() || !targetSize.isValid() || targetSize.isEmpty()) {
        qWarning() << "Invalid input for scaling: " << (screenshot.isNull() ? "Screenshot is null; " : "")
        << (!targetSize.isValid() ? "TargetSize is not valid; " : "")
        << (targetSize.isEmpty() ? "TargetSize id empty" : "") ;
        return screenshot;
    }

    // масштабируем с сохранением пропрций
    return screenshot.scaled(targetSize,
                             Qt::KeepAspectRatio,      // сохраняем пропорции
                             Qt::SmoothTransformation); // сглаживание для качества
}
