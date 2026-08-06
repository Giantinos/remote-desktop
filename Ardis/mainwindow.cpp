#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "senderclient.h"
#include <QImageReader>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // DEBUG
    QTimer *updateUAddressTimer = new QTimer(this);
    // Подключение док дебагера к кнопке из тулбара
    {
        ui->action_Debug_view->setChecked(false); // По умолчанию виден
        connect(ui->action_Debug_view, &QAction::toggled,
                ui->dockWidget_debug, &QDockWidget::setVisible);
        ui->dockWidget_debug->setVisible(false); // Возвращает QAction*
    }

    ui->pushButton_disconnectClient->setEnabled(false);
    // #### Main Objects ####
    senderClient = new SenderClient(ui->textWidget,this);
    receiverObject = new ReceiverObject(ui->textWidget,this);

    // connect debugs
    {
        connect(Common::instance(), &Common::debugSignal,
                this, [this](const QString m){
                    ui->plainTextEdit_debug->appendPlainText(m);
                });
    }
    // ///////////////////

    // ########
    // DEBUG
    // check udp address
    updateUAddressTimer->start(1000);
    connect(updateUAddressTimer, &QTimer::timeout, this, &MainWindow::checkUdpAddress);
    // RadioButtons UDP settings обозначение устройства для отладки (ВМ или хост)
    connect(ui->radioButton_virtualMachine, &QRadioButton::toggled,
            this, [&](){
        applyUdpSettings("192.168.0.30", 8001);
    });
    connect(ui->radioButton_host, &QRadioButton::toggled,
            this, [&](){
        applyUdpSettings("127.0.0.1", 8001);
    });
    // checkbox udp settings
    useManualSettings = false;
    manageUdpSettings(false);
    connect(ui->checkBox_useManualSettings, &QCheckBox::toggled,
            this, [this](bool checked){
        useManualSettings = checked;
        manageUdpSettings(checked);
    });
    //====Client====

    // ----Connect----
    connect(ui->pushButton_connectToServer, &QPushButton::clicked,
            this, &MainWindow::connectToHost);
    // ---- Set parameters ----
    connect(ui->button_setParameters, &QPushButton::clicked,
            this, &MainWindow::setUpHostParameters);
    // ---- Send ----
    connect(ui->pushButton_sendMessage, &QPushButton::clicked,
            this, &MainWindow::sendMessage);
    // ---- Set status | Update UI ----

    // ---- Disconnect from host ----
    connect(ui->pushButton_disconnectFromServer, &QPushButton::clicked,
            this, &MainWindow::disconnectFromServer);
    // ---- Warnings ----
    ui->label_clietnConnection->setText(senderClient->getStringConnectionStatus());
    connect(senderClient,  &SenderClient::warning,this, [this](QString message) {
        QMessageBox::warning(this, "", message);
    });
    // ---- Set Display ----
    senderClient->setDisplayWidget(ui->DisplayWidget_label);

    // ---- UI setup ----
    setMinimumSize(1330, 600);
    resize(1330, 600);

    // ---- Udp settings sector ----
    connect(ui->pushButton_applyUdpSettings, &QPushButton::clicked, this, [&](){
        qDebug() << "[Main window] button apply udp settings";
        MainWindow::applyUdpSettings();
    });

    // ====Server====

    // ---- Set status | Update UI ----
    connect(receiverObject, &ReceiverObject::serverSignalInfo, this ,[this](QString message){
        ui->label_serverStatus->setText(message);
    });
    // ---- Signal (Server Connection) ----
    connect(receiverObject, &ReceiverObject::connectionChanged,
            this, &MainWindow::serverStateListener);
    connect(senderClient, &SenderClient::connectionChanged,
            this, &MainWindow::clientStateListener);
    // ---- Warnings ----
    ui->label_serverStatus->setText(receiverObject->getStringServerStatus());
    connect(receiverObject, &ReceiverObject::warning, this, [this](QString message){
        QMessageBox::warning(this, "", message);
    });
    // ---- Start Server ----
    connect(ui->pushButton_startServer, &QPushButton::clicked, this,&MainWindow::startServer);
    // ---- Stop Server ----
    connect(ui->pushButton_stopServer, &QPushButton::clicked, this, &MainWindow::stopServer);
    // ---- Disconnect client ----
    connect(ui->pushButton_disconnectClient, &QPushButton::clicked, this,
            &MainWindow::disconnectClient);

    // ==== Screencast ====

    connect(ui->pushButton_startServerScreenCast, &QPushButton::clicked, this, &MainWindow::startServerScreencast);
    connect(ui->pushButton_stopScreencast, &QPushButton::clicked, this, &MainWindow::stopScreenCast);
    serverStateListener(ServerState::STOPPED);
    clientStateListener(ClientState::DISCONNECTED);
}

void MainWindow::connectToHost(){
    senderClient->connectToHost();
}

void MainWindow::disconnectFromServer(){
    senderClient->disconnectFromHost();
}

void MainWindow::setUpHostParameters(){
    if(!useManualSettings)
    {
        applyUdpSettings(ui->lineEdit_ipv4->text(),
                         ui->lineEdit_udpPort->text().toInt());
    }
    senderClient->setHostParameters(ui->lineEdit_ipv4->text(),
                                    ui->lineEdit_port->text().toInt());
}

void MainWindow::sendMessage(){
    QString message = ui->lineEdit_messageToSend->text();
    if(receiverObject->getServerStatus() == ServerState::CLIENT_CONNECTED){
        receiverObject->sendMessage(message);
    }else if(senderClient->getConnectionStatus() == ClientState::CONNECTED){
        senderClient->sendMessage(message);
    }
    ui->lineEdit_messageToSend->clear();
}

void MainWindow::startServer(){
    receiverObject->initServer();
}

// Server disconnecting a client
void MainWindow::disconnectClient(){
    receiverObject->disconnectClient();
}

void MainWindow::stopServer(){
    receiverObject->stopServer();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// трансяция экрана

void MainWindow::startMyScreenCast(){
    /*
    если трансляция уже запущена
    то выход

    если трансляция у серверной части
    то выход
    */

    if(senderClient->getConnectionStatus() == ClientState::CONNECTED){
        senderClient->startScreencast();
    } else {
        QMessageBox::warning(this, "Cant start Screencast", "Client disconnected");
    }
}

void MainWindow::startServerScreencast(){
    senderClient->startServerScreencast();
}
// добавить получение статусов видеопотока у клиента и сервера
void MainWindow::stopScreenCast(){
    senderClient->stopServerScreencast();
}

void MainWindow::applyUdpSettings(QString address, int port){
    receiverObject->setUdpAddress(address) ;
    receiverObject->setUdpPort(port);
    senderClient->setUdpAddress(address);
    senderClient->setUdpPort(port);
}

void MainWindow::applyUdpSettings(){
    qDebug() << "[Main window] applyUDPSettings()";
    receiverObject->setUdpAddress(ui->lineEdit_udpAddress->text()) ;
    receiverObject->setUdpPort(ui->lineEdit_udpPort->text().toInt());
    senderClient->setUdpAddress(ui->lineEdit_udpAddress->text());
    senderClient->setUdpPort(ui->lineEdit_udpPort->text().toInt());
}

void MainWindow::checkUdpAddress(){
    if(senderClient->getConnectionStatus() != ClientState::DISCONNECTED){
        if(senderClient->getUdpAddress().toString()
            != ui->lineEdit_udpAddress->text()){
            ui->lineEdit_udpAddress->setText(senderClient->getUdpAddress().toString());
        }
    } else if(receiverObject->getServerStatus() != ServerState::STOPPED){
        if(receiverObject->getUdpAddress().toString()
            != ui->lineEdit_udpAddress->text()){
            ui->lineEdit_udpAddress->setText(receiverObject->getUdpAddress().toString());
        }
    }
}

void MainWindow::clientStateListener(int state){
    // исправить механизм -↓
    ui->label_clietnConnection->setText(senderClient->getStringConnectionStatus());
    //
    if(receiverObject->getServerStatus() == ServerState::CLIENT_CONNECTED
        || receiverObject->getServerStatus() == ServerState::STARTED
        || receiverObject->getServerStatus() == ServerState::INCOMING_CONNECTION)
    {
        QMessageBox::warning(this, "Desync application logic", "Server is running!");
    }
    if(state == ClientState::CONNECTED
        || state == ClientState::CONNECTING)
    {
        // общее управление с сервером кнопками
        manageUIButtons();
        // уникальные управления
        ui->pushButton_disconnectFromServer->setEnabled(true);
        ui->pushButton_stopServer->setDisabled(true);
        if(state == ClientState::CONNECTED){
            ui->pushButton_sendMessage->setEnabled(true);
            ui->pushButton_startServerScreenCast->setEnabled(true);
            ui->pushButton_startMyScreenCast->setEnabled(true);
            ui->pushButton_stopScreencast->setEnabled(true);
        }else{
            ui->pushButton_sendMessage->setDisabled(true);
            ui->pushButton_startServerScreenCast->setDisabled(true);
            ui->pushButton_startMyScreenCast->setDisabled(true);
            ui->pushButton_stopScreencast->setDisabled(true);
        }
        return;
    }
    onServer_N_ClientInactive();
}

void MainWindow::serverStateListener(int status){
    if(senderClient->getConnectionStatus() == ClientState::CONNECTED
        || senderClient->getConnectionStatus() == ClientState::CONNECTING)
    {
        QMessageBox::warning(this, "Desync application logic", "Client is active!");
    }
    if(status == ServerState::CLIENT_CONNECTED
        || status == ServerState::INCOMING_CONNECTION
        || status == ServerState::STARTED)
    {
        // общее управление с клиентом кнопками
        manageUIButtons();
        // разблокировка
        ui->pushButton_disconnectFromServer->setDisabled(true);
        ui->pushButton_stopServer->setEnabled(true);
        if(status == ServerState::CLIENT_CONNECTED){
            ui->pushButton_sendMessage->setEnabled(true);
            ui->pushButton_startServerScreenCast->setEnabled(true);
            ui->pushButton_startMyScreenCast->setEnabled(true);
            ui->pushButton_stopScreencast->setEnabled(true);
        }else{
            ui->pushButton_sendMessage->setDisabled(true);
            ui->pushButton_startServerScreenCast->setDisabled(true);
            ui->pushButton_startMyScreenCast->setDisabled(true);
            ui->pushButton_stopScreencast->setDisabled(true);
        }
        return;
    }
    onServer_N_ClientInactive();
}

void MainWindow::onServer_N_ClientInactive(){
    // разблокировка всех кнопок
    ui->pushButton_disconnectFromServer->setEnabled(true);
    ui->pushButton_startServer->setEnabled(true);
    ui->pushButton_connectToServer->setEnabled(true);
    ui->button_setParameters->setEnabled(true);
    ui->radioButton_virtualMachine->setEnabled(true);
    ui->radioButton_host->setEnabled(true);
    // блокировка кнопок
    ui->pushButton_sendMessage->setDisabled(true);
    ui->pushButton_disconnectFromServer->setDisabled(true);
    ui->pushButton_startServerScreenCast->setDisabled(true);
    ui->pushButton_startMyScreenCast->setDisabled(true);
    ui->pushButton_stopScreencast->setDisabled(true);
}

void MainWindow::manageUIButtons(){
    ui->pushButton_startServer->setDisabled(true);
    ui->pushButton_connectToServer->setDisabled(true);
    ui->button_setParameters->setDisabled(true);
    ui->radioButton_virtualMachine->setDisabled(true);
    ui->radioButton_host->setDisabled(true);
}

void MainWindow::manageUdpSettings(bool state){
    ui->radioButton_host->setEnabled(state);
    ui->radioButton_virtualMachine->setEnabled(state);
    ui->lineEdit_udpAddress->setEnabled(state);
    // ui->lineEdit_udpPort->setEnabled(state);
}