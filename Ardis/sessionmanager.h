#ifndef SESSIONMANAGER_H
#define SESSIONMANAGER_H

#include <QObject>
#include "senderclient.h"
#include "receiverobject.h"

class SessionManager : public QObject
{
    Q_OBJECT
public:
    explicit SessionManager(SenderClient *senderClient,
                            ReceiverObject *receiverObject,
                            QObject *parent = nullptr,
                            QTextEdit *textWidget = nullptr,
                            QPushButton *sendMessageButton = nullptr,
                            QPushButton *setParametersButton = nullptr,
                            QPushButton *connectToServerButton = nullptr,
                            QPushButton *disconnectFromServerButton = nullptr,
                            QPushButton *disconnectClientButton = nullptr,
                            QPushButton *startServerButton = nullptr,
                            QPushButton *stopServerButton = nullptr
                            );
    void sendMessage(QString& message);
public slots:
    void onServerStarted();
    void onServerStopped();
    void onServerHaveAConnection();
    void onClientConnected();
    void onClientDisconnected();
    void onValidClientSettings();
    void onInvalidClientSettings();
    void updateUiState();

    // void onParametersChanged();

private:
    SenderClient *senderClient;
    ReceiverObject *receiverObject;
//  == Messaging
    QTextEdit *textWidget;
//  == Buttons ==
    QPushButton *sendMessageButton;
    QPushButton *setParametersButton;
    QPushButton *connectToServerButton;
    QPushButton *disconnectFromServerButton;
    QPushButton *disconnectClientButton;
    QPushButton *startServerButton;
    QPushButton *stopServerButton;
//  == Methods ==
    void disableButton(QPushButton *button);
    void enableButton(QPushButton *button);

private slots:
    bool isButtonOk(QPushButton *button);


signals:
    void Error(QString message);
};

#endif // SESSIONMANAGER_H
