#include "keyboardcapture.h"
#include "common.h"
#include <qdatetime.h>

KeyboardCapture::KeyboardCapture(QObject* parent) : QObject(parent)
{
    // таймер для длительных нажатий
    /*m_holdTimer = new QTimer(this);
    m_holdTimer->setSingleShot(false);
    m_holdTimer->setInterval(100); */ // Проверка каждые 100 мс
    // connect(m_holdTimer, &QTimer::timeout, this, &KeyboardCapture::onKeyHoldTimer);

    // фильтр событий для приложения
    qApp->installEventFilter(this);
}

KeyboardCapture::~KeyboardCapture() {
    // stopCapture();
    qApp->removeEventFilter(this);
}

void KeyboardCapture::startCapture() {
    if (m_isCapturing) return;

    m_isCapturing = true;
    m_pressedKeys.clear();
    // m_keyPressTime.clear();

    emit captureStarted();
    DEBUG("[Keyboard] Keyboard capture started");
}

void KeyboardCapture::stopCapture() {
    if (!m_isCapturing) return;

    m_isCapturing = false;
    m_pressedKeys.clear();
    // m_keyPressTime.clear();
    // m_holdTimer->stop();

    emit captureStopped();
    DEBUG("[Keyboard] Keyboard capture stopped");
}

bool KeyboardCapture::eventFilter(QObject* obj, QEvent* event) {
    if (!m_isCapturing) {
        return QObject::eventFilter(obj, event);
    }

    // перехватываем события клавиатуры
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        processKeyPress(keyEvent);
        return false;  // не блокируем событие
    }

    if (event->type() == QEvent::KeyRelease) {
        QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
        processKeyRelease(keyEvent);
        return false;
    }

    return QObject::eventFilter(obj, event);
}

void KeyboardCapture::processKeyPress(QKeyEvent* event) {
    int keyCode = event->key();
    Qt::KeyboardModifiers modifiers = event->modifiers();

    // не дублируется ли событие (повторные нажатия)
    // if (m_pressedKeys.contains(keyCode)) {
    //     // обновляем время нажатия для повтора
    //     m_keyPressTime[keyCode] = QDateTime::currentMSecsSinceEpoch();
    //     return;
    // }

    // сохраняем нажатую клавишу
    m_pressedKeys.insert(keyCode);
    // m_keyPressTime[keyCode] = QDateTime::currentMSecsSinceEpoch();

    // отправляем сигнал о нажатии
    sendKeyPress(keyCode, modifiers);

    // проверяем комбинации
    checkCombination();

    // запускаем таймер длительного нажатия (если это не модификатор)
    // if (!(keyCode == Qt::Key_Control ||
    //       keyCode == Qt::Key_Shift ||
    //       keyCode == Qt::Key_Alt ||
    //       keyCode == Qt::Key_Meta)) {
    //     startHoldTimer(keyCode);
    // }
}

void KeyboardCapture::processKeyRelease(QKeyEvent* event) {
    int keyCode = event->key();

    if (!m_pressedKeys.contains(keyCode)) {
        return;  // клавиша не была нажата ранее
    }

    // удаляем из нажатых
    m_pressedKeys.remove(keyCode);
    // m_keyPressTime.remove(keyCode);

    // останавливаем таймер длительного нажатия
    // if (m_holdKeyCode == keyCode) {
    //     stopHoldTimer();
    // }

    // отправляем сигнал об отжатии
    if (m_sendKeyRelease) {
        sendKeyRelease(keyCode);
    }
}

void KeyboardCapture::sendKeyPress(int keyCode, Qt::KeyboardModifiers mods){
    int ctrl = mods & Qt::ControlModifier;
    int shift = mods & Qt::ControlModifier;
    int alt = mods & Qt::ControlModifier;
    QString keys = "";
    keyPressToString(keyCode, ctrl, shift, alt, keys);
    emit keyPressed(keys);
}
// подготовка к отправке по сети
void KeyboardCapture::keyPressToString(int keyCode, int ctrl,int shift,int alt,QString& out){
    out = "p:" + QString::number(keyCode) + ":"
          + QString::number(ctrl) + ":"
          + QString::number(shift) + ":"
          + QString::number(alt);
}
// подготовка к отправке по сети
QString KeyboardCapture::keyReleaseToString(int keyCode){
    return "r:" + QString::number(keyCode);
}
void KeyboardCapture::sendKeyRelease(int keyCode){
    qDebug() << "[Keyboard] release string to send " << keyReleaseToString(keyCode);
    emit keyReleased(keyReleaseToString(keyCode));
}
// подготовка к отправке по сети
QString keyCombinationToString(const QSet<int>& keys){
    QString combination = "c:";
    for(int key : keys){
        combination += QString::number(key);
        if(keys.find(key) != keys.end())
            combination += ":";
    }
    qDebug() << "[Keyboard] combination to send " << combination;
    return combination;
}
void KeyboardCapture::checkCombination(){
    if(m_pressedKeys.size() >= 2){
        // QSet<int> combination = m_pressedKeys;
        QString combination = keyCombinationToString(m_pressedKeys);
        emit keyCombination(combination);
    }
}

// void KeyboardCapture::startHoldTimer(int keyCode){
//     m_holdKeyCode = keyCode;
//     m_holdStartTime = QDateTime::currentMSecsSinceEpoch();
//     m_holdTimer->start();
// }

// void KeyboardCapture::stopHoldTimer(){
//     m_holdTimer->stop();
//     m_holdKeyCode = 0;
//     m_holdStartTime = 0;
// }

// void KeyboardCapture::onKeyHoldTimer(){
//     if(m_holdKeyCode == 0 || !m_pressedKeys.contains(m_holdKeyCode)){
//         stopHoldTimer();
//         return;
//     }

//     qint64 currentTime = QDateTime::currentMSecsSinceEpoch();
//     int durationMs = currentTime - m_holdStartTime;
//     // отправка сигнала длительного нажатия каждые 100мс
//     if(durationMs % 100 < 20){ // делает отправку не слишком частой
//         QString holdData = QString::number(m_holdKeyCode) + ":" +QString::number(durationMs);
//         emit keyHold(holdData);
//     }
// }
