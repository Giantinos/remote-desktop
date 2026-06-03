#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "senderclient.h"
#include "receiverobject.h"
#include <QMainWindow>
#include "sessionmanager.h"

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
    SessionManager *sessionManager;
    // QPushButton *connectButton;

private slots:
    void connectToHost();
    void setUpHostParameters();
    void sendMessage();
    void startServer();
    void disconnectFromServer();
    void disconnectClient();
    void stopServer();

};
#endif // MAINWINDOW_H
