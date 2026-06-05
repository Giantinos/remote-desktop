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
    if(startServerButton)
        this->startServerButton = startServerButton;
    else emit Error("Error assigning <startServerButton>");
    if(stopServerButton){
        this->stopServerButton = stopServerButton;
    }else emit Error("Error assigning <stopServerButton>");
}

void SessionManager::disableButton(QPushButton *button, QString buttonName){
    if(button){
        button->setDisabled(true);
    }
    else emit Error(QString("Error: nullptr <%1> %2")
                       .arg(buttonName,"buton"));
}

void SessionManager::enableButton(QPushButton *button, QString buttonName){
    if(button){
        button->setEnabled(true);
    }
    else emit Error(QString("Error: nullptr <%1> %2")
                       .arg(buttonName, "button"));
}

bool SessionManager::isButtonOk(QPushButton *button){
    try{
        button->text();
    }catch(...){
        emit Error(QString("Somthing went wrong about button %1").arg(button->objectName()));
        return false;
    }
    return true;
}


void SessionManager::onClientConnected(){
    if(isButtonOk(connectToServerButton))
    disableButton(connectToServerButton,connectToServerButton->objectName());
    if(isButtonOk(startServerButton))
    disableButton(startServerButton,startServerButton->objectName());
}

void SessionManager::onClientDisconnected(){
    if(isButtonOk(sendMessageButton))
    disableButton(sendMessageButton, sendMessageButton->objectName());
}

void SessionManager::onServerStarted(){
    if(isButtonOk(connectToServerButton))
    disableButton(connectToServerButton, connectToServerButton->objectName());
    if(isButtonOk(startServerButton))
    disableButton(startServerButton, startServerButton->objectName());
}

void SessionManager::onServerStopped(){
    if(isButtonOk(connectToServerButton))
    enableButton(connectToServerButton, connectToServerButton->objectName());
    if(isButtonOk(startServerButton))
    enableButton(startServerButton, startServerButton->objectName());
}

void SessionManager::onServerHaveAConnection(){
    if(isButtonOk(sendMessageButton))
    enableButton(sendMessageButton, sendMessageButton->objectName());
}

void SessionManager::onValidClientSettings(){
    if(isButtonOk(connectToServerButton))
    enableButton(connectToServerButton, connectToServerButton->objectName());
    if(isButtonOk(startServerButton))
    enableButton(startServerButton, startServerButton->objectName());
}

void SessionManager::onInvalidClientSettings(){
    if(isButtonOk(connectToServerButton))
    disableButton(connectToServerButton, connectToServerButton->objectName());
    if(isButtonOk(startServerButton))
    disableButton(startServerButton, startServerButton->objectName());
}

void SessionManager::updateUiState(){
    switch(senderClient->getConnectionStatus()){
    case ClientState::CONNECTED:
        onClientConnected();
        break;
    case ClientState::DISCONNECTED:
        onClientDisconnected();
        break;
    case ClientState::C_ERROR:
        onClientDisconnected();
        break;
    default: break;
    }

    switch(receiverObject->getServerStatus()){
    case ServerState::STOPPED:
        onServerStopped();
        break;
    case ServerState::STARTED:
        onServerStarted();
        break;
    case ServerState::CLIENT_CONNECTED:
        onServerHaveAConnection();
        break;
    case ServerState::S_ERROR:
        onServerStopped();
        break;
    default: break;
    }
}
