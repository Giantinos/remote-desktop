#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "senderclient.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_disconnectClient->setEnabled(false);
    // #### Main Objects ####
    senderClient = new SenderClient(this);
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

    //====Client====

    // ----Connect----
    connect(ui->pushButton_connectToServer, &QPushButton::clicked, this, &MainWindow::connectToHost);
    // ---- Set parameters ----
    connect(ui->button_setParameters, &QPushButton::clicked, this, &MainWindow::setUpHostParameters);
    // ---- Send ----
    connect(ui->pushButton_sendMessage, &QPushButton::clicked, this, &MainWindow::sendMessage);
    // ---- Set status | Update UI ----
    connect(senderClient,  &SenderClient::connectionStatusChanged,this, [this]() {
        ui->label_clietnConnection->setText(senderClient->getStringConnectionStatus());
        sessionManager->updateUiState();
    });
    // ---- Warnings ----
    ui->label_clietnConnection->setText(senderClient->getStringConnectionStatus());
    connect(senderClient,  &SenderClient::warning,this, [this](QString message) {
        QMessageBox::warning(this, "", message);
    });
    // ---- UI setup ----


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
    // ---- Start ----
    connect(ui->pushButton_startServer, &QPushButton::clicked, this,&MainWindow::startServer);
    // ---- Stop ----
    connect(ui->pushButton_stopServer, &QPushButton::clicked, this, &MainWindow::stopServer);
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
}

void MainWindow::startServer(){
    receiverObject->initServer();
}

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
