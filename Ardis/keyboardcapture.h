#ifndef KEYBOARDCAPTURE_H
#define KEYBOARDCAPTURE_H

#include <QObject>
#include <QKeyEvent>
#include <QTimer>
#include <QSet>

class KeyboardCapture : public QObject
{
    Q_OBJECT
public:
    explicit KeyboardCapture(QObject* parent = nullptr);
    ~KeyboardCapture();
    // управление захватом
    void startCapture();
    void stopCapture();
    // bool isCapturing() const { return m_isCapturing; }

    // настройки
    void setCaptureGlobal(bool global); // захват вне приложения
    void setSendKeyRelease(bool send); // отправлять сжатие или нет

signals:
    // сигналы для отправки по сети
    void keyPressed(int keyCode, bool ctrl,bool shift,bool alt);
    void keyReleased(int keyCode);
    void keyCombination(const QSet<int>& keys);
    void keyHold(int keyCode, int durationMS);

    // сигналы для UI
    void captureStarted();
    void captureStopped();
    void error(const QString& er);

protected:
    // для
    bool eventFilter(QObject* obj, QEvent* event) override;

private slots:
    void onKeyHoldTimer();
    void onKeyReleaseTimer();

private:
    // методы обработки
    void processKeyPress(QKeyEvent* vent);
    void processKeyRelease(QKeyEvent* vent);
    void checkCombination();
    void startHoldTimer(int keyCode);
    void stopHoldTimer();

    // отправка данных
    void sendKeyPress(int keyCode, Qt::KeyboardModifiers mods);
    void sendKeyRelease(int keyCode);
    void sendCombination(const QSet<int>& keys);

private:
    // состояния захвата
    bool m_isCapturing = false;
    bool m_captureGlobal = false;
    bool m_sendKeyRelease = false;

    // хранение клавиш
    QSet<int> m_pressedKeys;
    QSet<int> m_combinationKeys;
    QMap<int, qint64> m_keyPressTime;

    // таймер для длительности нажатия
    QTimer* m_holdTimer = nullptr;
    int m_holdKeyCode = 0;
    qint64 m_holdStartTime = 0;

    // таймер для задержки отправки комбинаций
    QTimer* m_combinationDelayTimer = nullptr;
    QSet<int> m_pendingCombination;

    Qt::KeyboardModifiers m_currentModifiers = Qt::NoModifier;

};



#endif // KEYBOARDCAPTURE_H
















