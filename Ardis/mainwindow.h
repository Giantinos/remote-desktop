#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "senderclient.h"
#include "receiverobject.h"
#include "keyboardcapture.h"
#include <QMainWindow>
#include "common.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
    Ui::MainWindow *ui;
    SenderClient *senderClient = nullptr;
    ReceiverObject *receiverObject = nullptr;
    KeyboardCapture *keyboard = nullptr;
    bool isKeyboardCapture = false;
    void onServer_N_ClientInactive();
    // Управляетсясигналами от клиента и сервера
    void manageUIButtons();
    bool useManualSettings;
    // [enable disable]
    void manageUdpSettings(bool state);


private slots:
    void connectToHost();
    void setUpHostParameters();
    void sendMessage();
    void startServer();
    void disconnectFromServer();
    void disconnectClient();
    void stopServer();
    // общий метод для остановки трансляции и инструментов
    void startMyScreencast();
    void startRemoteScreencast();
    void stopScreencast();
    void applyUdpSettings(QString address, int port);
    void applyUdpSettings();
    // для разработки
    void checkUdpAddress();
    void serverStateListener(int status);
    void clientStateListener(int status);


};
#endif // MAINWINDOW_H
