#include "sessionmanager.h"
#include <qpushbutton.h>

SessionManager::SessionManager(SenderClient *senderClient,
                               ReceiverObject *receiverObject,
                               QObject *parent,
                               QTextEdit *textWidget,
                               QPushButton *sendMessageButton,
                               QPushButton *setParametersButton,
                               QPushButton *connectToServerButton,
                               QPushButton *disconnectFromServerButton,
                               QPushButton *disconnectClientButton,
                               QPushButton *startServerButton,
                               QPushButton *stopServerButton
                               )
    : QObject{parent}
{
    if(senderClient){
        this->senderClient = senderClient;
    }else{
        emit Error("Error assigning <SenderClient>");
    }
    if(receiverObject){
        this->receiverObject = receiverObject;
    }else{
        emit Error("Error assigning <RecieverObject>");
    }

    if(textWidget){
        this->textWidget = textWidget;
    } else emit Error("Error assigning <textWidget>");
    if(sendMessageButton){
        this->sendMessageButton = sendMessageButton;
    }else emit Error("Error assigning <sendMessageButton>");
    if(setParametersButton){
        this->setParametersButton = setParametersButton;
    }else emit Error("Error assigning <setParametersButton>");
    if(connectToServerButton){
        this->connectToServerButton = connectToServerButton;
    }else emit Error("Error assigning <connectToServerButton>");
    if(disconnectFromServerButton){
        this->disconnectFromServerButton = disconnectFromServerButton;
    }else emit Error("Error assigning <disconnectFromServerButton>");
    if(disconnectClientButton){
        this->disconnectClientButton = disconnectClientButton;
    }else emit Error("Error assigning <disconnectClientButton>");
    if(stopServerButton){
        this->stopServerButton = stopServerButton;
    }else emit Error("Error assigning <stopServerButton>");
}

void SessionManager::disableButton(QPushButton *button, QString buttonName){
    if(button){
        button->setEnabled(false);
    }
    else emit Error(QString("Error: nullptr <%1> %2")
                       .arg(buttonName).arg("buton"));
}

void SessionManager::enableButton(QPushButton *button, QString buttonName){
    if(button){
        button->setEnabled(true);
    }
    else emit Error(QString("Error: nullptr <%1> %2")
                       .arg(buttonName).arg("buton"));
}


void SessionManager::onClientConnected(){
    disableButton(connectToServerButton,connectToServerButton->objectName());
    disableButton(startServerButton,startServerButton->objectName());
}

void SessionManager::onClientDisconnected(){
    disableButton(sendMessageButton, sendMessageButton->objectName());
}

void SessionManager::onServerStarted(){
    disableButton(connectToServerButton, connectToServerButton->objectName());
    disableButton(startServerButton, startServerButton->objectName());
}

void SessionManager::onServerStopped(){
    enableButton(connectToServerButton, connectToServerButton->objectName());
    enableButton(startServerButton, startServerButton->objectName());
}

void SessionManager::onServerHaveAConnection(){
    enableButton(sendMessageButton, sendMessageButton->objectName());
}

void SessionManager::onValidClientSettings(){
    enableButton(connectToServerButton, connectToServerButton->objectName());
    enableButton(startServerButton, startServerButton->objectName());
}

void SessionManager::onInvalidClientSettings(){
    disableButton(connectToServerButton, connectToServerButton->objectName());
    disableButton(startServerButton, startServerButton->objectName());
}

void SessionManager::updateUiState(){
    switch(senderClient->getConnectionStatus()){
    case ClientConnectionStatus::CONNECTED:
        onClientConnected();
        break;
    case ClientConnectionStatus::DISCONNECTED:
        onClientDisconnected();
        break;
    default: break;
    }

    switch(receiverObject->getServerStatus()){

    }

}
