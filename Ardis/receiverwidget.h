#ifndef RECEIVERWIDGET_H
#define RECEIVERWIDGET_H

#include <QWidget>
#include <QTextEdit>
// #include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QTcpSocket>
#include <QTcpServer>
#include <QMessageBox>
// #include <QTextBrowser>

class ReceiverWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ReceiverWidget(int port, QWidget *parent = nullptr);

private slots:
    void onNewConnection();
    void onReadyRead();
    void onClientDisconnected();

private:
    QTextEdit *receivedMessages;
    QLabel *statusLabel;
    QTcpServer *server;
};

#endif // RECEIVERWIDGET_H


