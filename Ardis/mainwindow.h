#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "senderclient.h"
#include "receiverobject.h"
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
    SenderClient *senderClient;
    ReceiverObject *receiverObject ;
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
    void startMyScreenCast();
    void startServerScreencast();
    void stopScreenCast();
    void applyUdpSettings(QString address, int port);
    void applyUdpSettings();
    // для разработки
    void checkUdpAddress();
    void serverStateListener(int status);
    void clientStateListener(int status);


};
#endif // MAINWINDOW_H
