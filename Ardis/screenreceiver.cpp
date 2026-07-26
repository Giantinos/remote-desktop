
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
    // запущен ли процесс получения
    if(m_isReceiving){
        emit errorOccurred("Already receiving");
        qDebug() << "Already receiving";
        return;
    }

    // проверка сокета
    if (!m_socket) {
        emit errorOccurred("Socket not set");
        return;
    }

    // проверка виджета отображения
    if(!m_displayWidget){
        emit errorOccurred("Display not set");
        return;
    } else { qDebug() << "Display ready" ;}

    // подготовка членов класса
    m_isReceiving = true;
    m_receiveBuffer.resize(CHUNK_SIZE);
    // m_stream.setDevice(&m_receiveBuffer);
    m_assembly.data.resize(CHUNK_SIZE * 4);
    // m_dchunk.data.resize(CHUNK_SIZE);
    m_expectedSize = 0;

    // соединение сокета с событием получения

    // ИСПРАВИТЬ МАГИЧЕСКОЕ ЧИСЛО
    if(m_socket->bind(QHostAddress::Any, 8001)){
        qDebug() << "Bind usocket sucess";

        connect(m_socket, &QUdpSocket::readyRead,
            this, &ScreenReceiver::onSocketReadyRead);
    }else {
        qDebug() << "Couldnt bind socket";

        emit errorOccurred("Error: couldnt start UDP listening");
    }
    emit receivingStarted();
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

void ScreenReceiver::onSocketReadyRead() {
    qDebug() << "[Video] onSocketReadyRead()";

    // проверка сокета
    if (!m_socket) {
        qDebug() << "VideoStream:: socket is nullptr";
        return;
    }

    while(m_socket->hasPendingDatagrams()){
        qDebug() << "[Video] hasPendingDatagrams()";

        // читаем данные из сокета
        getImageDataFromUdpSocket();

        // распаковка фрагмента
        if(!convertBytesToImageChunk()){
            qDebug() << "[Video] Error parsing datagrtam";
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
    qDebug() << "[Video] pending data size: " << m_socket->pendingDatagramSize();
    qDebug() << "[Video] buffer capacity: " << m_receiveBuffer.capacity();
    if(m_receiveBuffer.size() != m_socket->pendingDatagramSize()){
        qDebug() << "[Video] Resizing buffer";
        m_receiveBuffer.resize(m_socket->pendingDatagramSize());
    }
    qDebug() << "[Video] buffer data bytes: " << m_receiveBuffer.size();
    int bytesRead = m_socket->readDatagram(m_receiveBuffer.data(), m_socket->pendingDatagramSize());
    qDebug() << "[Video] read bytes: " << bytesRead;
}

// return true если успешно
bool ScreenReceiver::convertBytesToImageChunk(){
    m_stream.device()->seek(0);
    m_stream >> m_dchunk.id
        >> m_dchunk.total
        >> m_dchunk.current
        >> m_dchunk.data;
    qDebug() << "[Video] decoding chunk: id:" << m_dchunk.id
             << " total:" << m_dchunk.total
             <<  " current:" << m_dchunk.current
             << " data.size:" << m_dchunk.data.size();
    qDebug() << "[Video] m_stream status: " << m_stream.status();
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
}
void ScreenReceiver::onAllChunksReceived(ImageAssembly &assembly){
    if (assembly.received == assembly.total) {
        // Полное изображение готово!
        QByteArray fullImage = assembly.data.left(assembly.received * CHUNK_SIZE);
        processData(fullImage);

        // Удаляем сборщик
        m_assemblies.remove(assembly.id);
    }
}

void ScreenReceiver::processData(const QByteArray& data) {
    QPixmap frame = decodeImage(data);

    if (frame.isNull()) {
        emit errorOccurred("Failed to decode image");
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
        // масштабируем под размер виджета с сохранением пропорций
        QPixmap scaled = pixmap.scaled(m_displayWidget->size(),
                                       Qt::KeepAspectRatio,
                                       Qt::SmoothTransformation);
        qDebug() << "Show display";
        m_displayWidget->setPixmap(scaled);
    } else {
        qDebug() << "Display widget is not setted";
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
//        найти где меняется
