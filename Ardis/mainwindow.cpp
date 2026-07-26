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
    // ///////////////////
    ui->pushButton_disconnectClient->setEnabled(false);
    // #### Main Objects ####
    senderClient = new SenderClient(ui->textWidget,this);
    receiverObject = new ReceiverObject(ui->textWidget,this);
    sessionManager = new SessionManager(senderClient, receiverObject, this,
                                        ui->textWidget,
                                        ui->pushButton_sendMessage,
                                        ui->button_setParameters,
                                        ui->pushButton_connectToServer,
                                        ui->pushButton_disconnectFromServer,
                                        ui->pushButton_disconnectClient,
                                        ui->pushButton_startServer,
                                        ui->pushButton_stopServer
                                        );
    // ########
    // DEBUG
    // check udp address
    updateUAddressTimer->start(1000);
    connect(updateUAddressTimer, &QTimer::timeout, this, &MainWindow::checkUdpAddress);
    // RadioButtons обозначение устройства для отладки (ВМ или хост)
    connect(ui->radioButton_virtualMachine, &QRadioButton::toggled,
            this, [&](){
        applyUdpSettings("192.168.0.30", 8001);
    });
    connect(ui->radioButton_host, &QRadioButton::toggled,
            this, [&](){
        applyUdpSettings("127.0.0.1", 8001);
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
    connect(senderClient,  &SenderClient::connectionStatusChanged,
            this, [this]() {
        ui->label_clietnConnection->setText(senderClient->getStringConnectionStatus());
        sessionManager->updateUiState();
    });
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
    connect(receiverObject, &ReceiverObject::serverStatusChanged, this ,[this](QString message){
        ui->label_serverStatus->setText(message);
        sessionManager->updateUiState();
    });
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
}

void MainWindow::connectToHost(){
    senderClient->connectToHost();
}

void MainWindow::disconnectFromServer(){
    senderClient->disconnectFromHost();
}

void MainWindow::setUpHostParameters(){
    senderClient->setHostParameters(ui->lineEdit_ipv4->text(),
                                    ui->lineEdit_port->text().toInt());
}

void MainWindow::sendMessage(){
    // sessionManager->sendMessage();
    sessionManager->sendMessage(ui->lineEdit_messageToSend->text());
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
