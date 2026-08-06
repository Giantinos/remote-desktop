#include "screenreceiver.h"
#include <QBuffer>
#include <QImageReader>
#include <QDebug>

ScreenReceiver::ScreenReceiver(QObject* parent)
    : ScreenBase(parent), m_stream(&m_receiveBuffer, QIODevice::ReadOnly)
{

}

// сам привязывается к сокету
void ScreenReceiver::startReceiving()
{
    DEBUG("[Video] Start receiving");

    if(m_isReceiving){
        emit errorOccurred("Already receiving");
        DEBUG("Already receiving");
        return;
    }

    // проверка сокета
    if (!m_socket){
        emit errorOccurred("Socket not set");
        return;
    }

    // проверка виджета отображения
    if(!m_displayWidget){
        emit errorOccurred("Display not set");
        return;
    } else { DEBUG("Display ready"); }

    // подготовка членов класса
    m_isReceiving = true;
    m_receiveBuffer.resize(CHUNK_SIZE);
    // m_stream.setDevice(&m_receiveBuffer);
    m_assembly.data.resize(CHUNK_SIZE * 4);
    // m_dchunk.data.resize(CHUNK_SIZE);
    m_expectedSize = 0;

    // соединение сокета с событием получения
    // ИСПРАВИТЬ МАГИЧЕСКОЕ ЧИСЛО
    // QHostAddress address("10.0.2.15");
    if(m_socket->bind(QHostAddress::AnyIPv4, 8001)){
        QString msg = "[Video] Bind usocket sucess "
                        + m_socket->localAddress().toString()
                        + ":" + QString::number(m_socket->localPort());
        qDebug() << msg;
        DEBUG(msg);

        connect(m_socket, &QUdpSocket::readyRead,
            this, &ScreenReceiver::onSocketReadyRead);
    }else {
        qDebug() << "Couldnt bind socket";
        DEBUG("[Video] Couldnt bind socket");

        emit errorOccurred("Error: couldnt start UDP listening");
    }
    emit receivingStarted();

    DEBUG("[Video] receiving started");
    qDebug() << "Screen receiving started";
}

void ScreenReceiver::stopReceiving(){
    if (!m_isReceiving) return;

    if (m_socket) {
        disconnect(m_socket, &QUdpSocket::readyRead,
                   this, &ScreenReceiver::onSocketReadyRead);
    }

    m_isReceiving = false;
    m_receiveBuffer.clear();
    emit receivingStopped();
    qDebug() << "Screen receiving stopped";
    DEBUG("[Video] Screen receiving stopped");
}

auto ScreenReceiver::findImageInAssemblyBuffer(){
    auto it = m_assemblies.find(m_dchunk.id);
    // при отсутствии записей условие сработает
    if (it == m_assemblies.end()) {

        // создание хранилища для создания изображения
        createNewImageAssembly();

        // таймаут на случай потери частей
        timeoutOnDataLost();

        // запись хранилища в словарь
        it = m_assemblies.insert(m_assembly.id, m_assembly);
    }
    return it;
}
// получение
void ScreenReceiver::onSocketReadyRead() {
    qDebug() << "[Video] onSocketReadyRead()";
    DEBUG("[Video] onSocketReadyRead()");

    // проверка сокета
    if (!m_socket) {
        qDebug() << "VideoStream:: socket is nullptr";
        DEBUG("VideoStream:: socket is nullptr");
        return;
    }

    while(m_socket->hasPendingDatagrams()){
        qDebug() << "[Video] hasPendingDatagrams()";
        DEBUG("[Video] hasPendingDatagrams()");
        // читаем данные из сокета
        getImageDataFromUdpSocket();

        // распаковка фрагмента
        if(!convertBytesToImageChunk()){
            qDebug() << "[Video] Error parsing datagrtam";
            DEBUG("[Video] Error parsing datagrtam");
            continue;
        }

        // создаем итератор и ищем запись в словаре c изображениями
        auto it = findImageInAssemblyBuffer();

        // it указывает на изображение в словаре
        ImageAssembly &assembly = it.value();

        // вставляем часть на место
        joinChunkToImage(assembly);

        // если все части собраны
        onAllChunksReceived(assembly);

        // m_assembly.data.clear();
        m_dchunk.data.clear();
        m_receiveBuffer.clear();
    }
}

void ScreenReceiver::getImageDataFromUdpSocket(){
// Debug
    {
        qDebug() << "[Video] pending data size: " << m_socket->pendingDatagramSize();
        qDebug() << "[Video] buffer capacity: " << m_receiveBuffer.capacity();
        DEBUG("[Video] pending data size: " + QString::number(m_socket->pendingDatagramSize()));
        DEBUG("[Video] buffer capacity: " + QString::number(m_receiveBuffer.capacity()));
    }

    if(m_receiveBuffer.size() != m_socket->pendingDatagramSize()){
        qDebug() << "[Video] Resizing buffer";
        DEBUG("[Video] Resizing buffer");
        m_receiveBuffer.resize(m_socket->pendingDatagramSize());
    }
    qDebug() << "[Video] buffer data bytes: " << m_receiveBuffer.size();
    DEBUG("[Video] buffer data bytes: " + QString::number(m_receiveBuffer.size()));
    int bytesRead = m_socket->readDatagram(m_receiveBuffer.data(), m_socket->pendingDatagramSize());
    qDebug() << "[Video] read bytes: " << bytesRead;
    DEBUG("[Video] read bytes: " + QString::number(bytesRead));
}

// return true если успешно
bool ScreenReceiver::convertBytesToImageChunk(){
    m_stream.device()->seek(0);
    m_stream >> m_dchunk.id
        >> m_dchunk.total
        >> m_dchunk.current
        >> m_dchunk.data;
    // Debug
    {
        qDebug() << "[Video] decoding chunk: id:" << m_dchunk.id
                 << " total:" << m_dchunk.total
                 <<  " current:" << m_dchunk.current
                 << " data.size:" << m_dchunk.data.size();
        qDebug() << "[Video] m_stream status: " << m_stream.status();
        DEBUG("[Video] decoding chunk: id:" + QString::number(m_dchunk.id)
                                          + " total:" + QString::number(m_dchunk.total)
                                          +  " current:" + QString::number(m_dchunk.current)
                                          + " data.size:" + QString::number(m_dchunk.data.size())
            );
        DEBUG("[Video] m_stream status: " + QString::number(m_stream.status()));
    }

    return m_stream.status() == QDataStream::Ok;
}

void ScreenReceiver::createNewImageAssembly(){
    // буфер для всего изображения
    m_assembly.id = m_dchunk.id;
    m_assembly.total = m_dchunk.total;
    m_assembly.received = 0;

    // выделяем буфер под ВСЕ части
    if(m_assembly.data.size() < m_assembly.total * CHUNK_SIZE)
        m_assembly.data.resize(m_assembly.total * CHUNK_SIZE);
}
void ScreenReceiver::timeoutOnDataLost(){
    QTimer::singleShot(3000, this, [this, id = m_dchunk.id]() {
        qDebug() << "Timeout for assembly " << id << " - removing";
        auto found = m_assemblies.find(id);
        if (found != m_assemblies.end()) {
            m_assemblies.remove(id);
        }
    });
}
void ScreenReceiver::joinChunkToImage(ImageAssembly &assembly){
    // верно ли что мы реплейсаем ту дату которую нужно?
    assembly.data.replace(m_dchunk.current * CHUNK_SIZE,
                          m_dchunk.data.size(),
                          m_dchunk.data);
    assembly.received++;
    DEBUG("[Video] Assembling image "
          + QString::number(m_dchunk.current)
          + "/" + QString::number(m_dchunk.total));
}
void ScreenReceiver::onAllChunksReceived(ImageAssembly &assembly){
    if (assembly.received == assembly.total) {
        DEBUG("[Video] Image done");
        // Полное изображение готово!
        QByteArray fullImage = assembly.data.left(assembly.received * CHUNK_SIZE);
        processData(fullImage);

        // Удаляем сборщик
        m_assemblies.remove(assembly.id);
    }
}

void ScreenReceiver::processData(const QByteArray& data) {
    QPixmap frame = decodeImage(data);
    DEBUG("[Video] Decoding image");
    if (frame.isNull()) {
        emit errorOccurred("Failed to decode image");
        DEBUG("[Video] Failed to decode image");
        return;
    }

    emit frameReceived(frame);
    qDebug() << "Frame processed";
    showFrame(frame);
}

QPixmap ScreenReceiver::decodeImage(const QByteArray& data) {
    QPixmap pixmap;
    pixmap.loadFromData(data, "JPEG");
    return pixmap;
}

void ScreenReceiver::showFrame(const QPixmap& pixmap) {
    if (m_displayWidget) {
        DEBUG("[Video] Scaling and outputing");
        // масштабируем под размер виджета с сохранением пропорций
        QPixmap scaled = pixmap.scaled(m_displayWidget->size(),
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation);
        qDebug() << "Show display";
        m_displayWidget->setPixmap(scaled);
    } else {
        qDebug() << "Display widget is not setted";
        DEBUG("[Video] Display widget is not setted");
    }
}

void ScreenReceiver::setDisplayWidget(QLabel* widget) {
    m_displayWidget = widget;
}

void ScreenReceiver::setSocket(QUdpSocket* socket) {
    m_socket = socket;
}

// идея: внедрить лейбл смотрящий на адрес внутри сервера m_uaddress
//        кажется на вм m_uaddress меняется на 127
//
// найти где меняется
