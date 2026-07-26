#ifndef SCREENRECEIVER_H
#define SCREENRECEIVER_H

#include "screenbase.h"
#include <QLabel>
#include <QPixmap>
#include <QUdpSocket>


struct ImageAssembly{
    int id;
    int total;
    int received;
    QByteArray data;
    QTimer* timeout;
};

class ScreenReceiver : public ScreenBase
{
    Q_OBJECT
public:
    explicit ScreenReceiver(QObject* parent = nullptr);

    // настройка
    void setDisplayWidget(QLabel* widget);
    void setSocket(QUdpSocket* socket);

    // yправление
    void startReceiving();
    void stopReceiving();
    bool isReceiving() const { return m_isReceiving; }

    // обработка входящих данных
    void processData(const QByteArray& data);

signals:
    void frameReceived(const QPixmap& frame);
    void errorOccurred(const QString& error);
    void receivingStarted();
    void receivingStopped();

private slots:
    void onSocketReadyRead();
    // void updateDisplay(const QPixmap& frame);

private:
    QPixmap decodeImage(const QByteArray& data);
    void showFrame(const QPixmap& pixmap);

    QLabel* m_displayWidget = nullptr;
    QUdpSocket* m_socket = nullptr;
    bool m_isReceiving = false;

    // буфер для приема датаграммы
    QByteArray m_receiveBuffer;
    // распакованный фрагмент
    DataChunk m_dchunk;
    // хранит изображения собранные из фрагментов
    QMap <int, ImageAssembly> m_assemblies;
    // фрагмент для создания изображения
    ImageAssembly m_assembly;
    quint32 m_expectedSize = 0;
    // член для распаковки потоков байтов
    QDataStream m_stream;
    // чтение фрагмента байтов с изображением
    void getImageDataFromUdpSocket();
    bool convertBytesToImageChunk();
    auto findImageInAssemblyBuffer();
    void createNewImageAssembly();
    void timeoutOnDataLost();
    void joinChunkToImage(ImageAssembly &assembly);
    void onAllChunksReceived(ImageAssembly &assembly);
};

#endif // SCREENRECEIVER_H
