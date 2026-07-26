#ifndef SCREENHANDLER_H
#define SCREENHANDLER_H

#include "screenbase.h"
#include <QScreen>
#include <QGuiApplication>
#include <QUdpSocket>
#include <QVector>

// Захватывает экран. Отправляет данные.
class ScreenHandler : public ScreenBase
{
    Q_OBJECT

public:
    explicit ScreenHandler(QObject* parent = nullptr);

    void setConfig(const ScreenCaptureConfig& config);
    void setSocket(QUdpSocket* socket);

    void startCapture();
    void stopCapture();
    bool isCapturing() const { return m_isCapturing; }

    QPixmap captureFrame();

signals:
    void frameCaptured(const QVector<DataChunk>& chunks);
    void errorOccurred(const QString& error);
    void captureStarted();
    void captureStopped();

private slots:
    void onCaptureTimer();


private:
    QPixmap captureScreen();
    void sendFrame(const QPixmap& pixmap);
    QVector<DataChunk> splitData(const QByteArray &data);
    QTimer* m_captureTimer = nullptr;
    QUdpSocket* m_socket = nullptr;
    bool m_isCapturing = false;
};

#endif // SCREENHANDLER_H
