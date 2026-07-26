#include "screenhandler.h"
#include <QBuffer>
#include <QImageWriter>
#include <QDebug>

ScreenHandler::ScreenHandler(QObject* parent)
    : ScreenBase(parent)
{
    m_captureTimer = new QTimer(this);
    connect(m_captureTimer, &QTimer::timeout,
            this, &ScreenHandler::onCaptureTimer);
}

void ScreenHandler::setSocket(QUdpSocket* socket){
    if(socket){
        m_socket = socket;
    } else qDebug() << ">> ScreenHandler:: *arg is nullptr";
}
void ScreenHandler::startCapture(){
    qDebug() << "ScreenHandler::startCapture()";
    if(m_isCapturing){
        qDebug() << "Capture already running";
        return;
    }

    if(!m_socket){
        qDebug() << "Socket not set";
        emit errorOccurred("Socket not set");
        return;
    }

    m_isCapturing = true;
    int interval = 1000 / m_config.fps;
    m_captureTimer->start(interval);

    emit captureStarted();
    qDebug() << ">> Screen Capture started, FPS:" << m_config.fps;
}

void ScreenHandler::stopCapture(){
    if(!m_isCapturing) return;

    m_captureTimer->stop();
    m_isCapturing = false;
    emit captureStopped();
    m_socket = nullptr;
    qDebug() << "Screen capture stopped";
}

void ScreenHandler::onCaptureTimer(){
    QPixmap frame = captureScreen();
    if(!frame.isNull()){
        qDebug() << "Frame captured!";
        sendFrame(frame);
    }
}

QPixmap ScreenHandler::captureScreen(){
    QScreen* screen = QGuiApplication::primaryScreen();
    if(!screen){
        qDebug() << "Error: No screen found";
        emit errorOccurred("No screen found");
        return QPixmap();
    }

    QPixmap screenshot = screen->grabWindow(0);

    if(screenshot.isNull()){
        emit errorOccurred("Failed to capture screen");
        return QPixmap();
    }

    // масштабирование
    if(m_config.resolution.isValid() &&
        screenshot.size() != m_config.resolution)
    {
        screenshot = scaleImage(screenshot, m_config.resolution);
    }

    qDebug() << ">> Screenshot scaled, sending.";
    return screenshot;
}

QVector<DataChunk> ScreenHandler::splitData(const QByteArray &data) {
    QVector<DataChunk> chunks;
    // сколько всего будет фрагментов
    // контекст data = imagе

    // вычисляется количество фрагментов
    int total = (data.size() + CHUNK_SIZE - 1) / CHUNK_SIZE;

    for (int i = 0; i < total; ++i) {
        DataChunk chunk;
        chunk.id = QDateTime::currentMSecsSinceEpoch();  // id
        chunk.total = total;
        chunk.current = i;
        //           с какого индекса-↓        ↓- размер отступа
        chunk.data = data.mid(i * CHUNK_SIZE, CHUNK_SIZE);
        chunks.append(chunk);
    }
    return chunks;
}

void ScreenHandler::sendFrame(const QPixmap& pixmap) {
    QByteArray compressedData = compressImage(pixmap, m_config.quality);
    if (compressedData.isEmpty()) {
        emit errorOccurred("Failed to compress image");
        return;
    }

    QVector<DataChunk> dataChunks = splitData(compressedData);


    // отправляем через сигнал
    qDebug() << "Frame compressed!";

    // ReceiverObject подхватывает
    emit frameCaptured(dataChunks);

    // напрямую через сокет (если есть)
    // if (m_socket) {
    //     // Протокол: [size (4 bytes)][data]
    //     QByteArray packet;
    //     QDataStream stream(&packet, QIODevice::WriteOnly);
    //     stream << quint32(compressedData.size());
    //     packet.append(compressedData);

    //     m_socket->write(packet);
    //     m_socket->flush();
    // }
}