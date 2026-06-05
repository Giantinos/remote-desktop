/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *textWidget;
    QLineEdit *lineEdit_messageToSend;
    QPushButton *pushButton_sendMessage;
    QGroupBox *groupBox;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_net_preferences;
    QLabel *label_ipv4;
    QLineEdit *lineEdit_ipv4;
    QLabel *label_port;
    QLineEdit *lineEdit_port;
    QPushButton *button_setParameters;
    QLabel *label;
    QLabel *label_clietnConnection;
    QLabel *label_2;
    QLabel *label_clientEvents;
    QPushButton *pushButton_connectToServer;
    QPushButton *pushButton_disconnectFromServer;
    QGroupBox *groupBox_2;
    QLabel *label_3;
    QLabel *label_serverStatus;
    QPushButton *pushButton_startServer;
    QPushButton *pushButton_stopServer;
    QPushButton *pushButton_disconnectClient;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(861, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        textWidget = new QTextEdit(centralwidget);
        textWidget->setObjectName("textWidget");
        textWidget->setGeometry(QRect(10, 10, 511, 451));
        textWidget->setReadOnly(true);
        lineEdit_messageToSend = new QLineEdit(centralwidget);
        lineEdit_messageToSend->setObjectName("lineEdit_messageToSend");
        lineEdit_messageToSend->setGeometry(QRect(10, 470, 511, 51));
        lineEdit_messageToSend->setMaxLength(256);
        lineEdit_messageToSend->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        pushButton_sendMessage = new QPushButton(centralwidget);
        pushButton_sendMessage->setObjectName("pushButton_sendMessage");
        pushButton_sendMessage->setGeometry(QRect(430, 530, 91, 24));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(530, 10, 321, 161));
        layoutWidget = new QWidget(groupBox);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(10, 20, 300, 26));
        horizontalLayout_net_preferences = new QHBoxLayout(layoutWidget);
        horizontalLayout_net_preferences->setObjectName("horizontalLayout_net_preferences");
        horizontalLayout_net_preferences->setContentsMargins(0, 0, 0, 0);
        label_ipv4 = new QLabel(layoutWidget);
        label_ipv4->setObjectName("label_ipv4");

        horizontalLayout_net_preferences->addWidget(label_ipv4);

        lineEdit_ipv4 = new QLineEdit(layoutWidget);
        lineEdit_ipv4->setObjectName("lineEdit_ipv4");
        lineEdit_ipv4->setMaxLength(23);

        horizontalLayout_net_preferences->addWidget(lineEdit_ipv4);

        label_port = new QLabel(layoutWidget);
        label_port->setObjectName("label_port");
        label_port->setLineWidth(1);

        horizontalLayout_net_preferences->addWidget(label_port);

        lineEdit_port = new QLineEdit(layoutWidget);
        lineEdit_port->setObjectName("lineEdit_port");
        lineEdit_port->setMaximumSize(QSize(40, 16777215));
        lineEdit_port->setMaxLength(5);
        lineEdit_port->setFrame(true);

        horizontalLayout_net_preferences->addWidget(lineEdit_port);

        button_setParameters = new QPushButton(layoutWidget);
        button_setParameters->setObjectName("button_setParameters");

        horizontalLayout_net_preferences->addWidget(button_setParameters);

        label = new QLabel(groupBox);
        label->setObjectName("label");
        label->setGeometry(QRect(10, 50, 136, 23));
        QFont font;
        font.setBold(true);
        font.setUnderline(false);
        label->setFont(font);
        label_clietnConnection = new QLabel(groupBox);
        label_clietnConnection->setObjectName("label_clietnConnection");
        label_clietnConnection->setGeometry(QRect(10, 70, 309, 16));
        label_clietnConnection->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(10, 90, 76, 28));
        label_2->setFont(font);
        label_clientEvents = new QLabel(groupBox);
        label_clientEvents->setObjectName("label_clientEvents");
        label_clientEvents->setGeometry(QRect(10, 110, 34, 28));
        label_clientEvents->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        pushButton_connectToServer = new QPushButton(groupBox);
        pushButton_connectToServer->setObjectName("pushButton_connectToServer");
        pushButton_connectToServer->setEnabled(true);
        pushButton_connectToServer->setGeometry(QRect(10, 130, 75, 24));
        pushButton_disconnectFromServer = new QPushButton(groupBox);
        pushButton_disconnectFromServer->setObjectName("pushButton_disconnectFromServer");
        pushButton_disconnectFromServer->setGeometry(QRect(90, 130, 75, 24));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(530, 170, 321, 101));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(10, 10, 77, 28));
        label_3->setFont(font);
        label_serverStatus = new QLabel(groupBox_2);
        label_serverStatus->setObjectName("label_serverStatus");
        label_serverStatus->setGeometry(QRect(10, 30, 65, 28));
        pushButton_startServer = new QPushButton(groupBox_2);
        pushButton_startServer->setObjectName("pushButton_startServer");
        pushButton_startServer->setGeometry(QRect(10, 70, 75, 24));
        QPalette palette;
        QBrush brush(QColor(0, 170, 127, 255));
        brush.setStyle(Qt::BrushStyle::SolidPattern);
        palette.setBrush(QPalette::ColorGroup::Active, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Inactive, QPalette::ColorRole::Button, brush);
        palette.setBrush(QPalette::ColorGroup::Disabled, QPalette::ColorRole::Button, brush);
        pushButton_startServer->setPalette(palette);
        pushButton_stopServer = new QPushButton(groupBox_2);
        pushButton_stopServer->setObjectName("pushButton_stopServer");
        pushButton_stopServer->setGeometry(QRect(90, 70, 75, 24));
        pushButton_disconnectClient = new QPushButton(groupBox_2);
        pushButton_disconnectClient->setObjectName("pushButton_disconnectClient");
        pushButton_disconnectClient->setGeometry(QRect(170, 70, 111, 24));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 861, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        lineEdit_messageToSend->setInputMask(QString());
        lineEdit_messageToSend->setText(QString());
        lineEdit_messageToSend->setPlaceholderText(QCoreApplication::translate("MainWindow", "Input your message...", nullptr));
        pushButton_sendMessage->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Client | Remote connect", nullptr));
        label_ipv4->setText(QCoreApplication::translate("MainWindow", "IP", nullptr));
        lineEdit_ipv4->setInputMask(QString());
        lineEdit_ipv4->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        lineEdit_ipv4->setPlaceholderText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        label_port->setText(QCoreApplication::translate("MainWindow", ":", nullptr));
        lineEdit_port->setText(QCoreApplication::translate("MainWindow", "8000", nullptr));
        lineEdit_port->setPlaceholderText(QCoreApplication::translate("MainWindow", "8000", nullptr));
        button_setParameters->setText(QCoreApplication::translate("MainWindow", "Set Parameters", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Client connection status:", nullptr));
        label_clietnConnection->setText(QCoreApplication::translate("MainWindow", "Connection status", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Client events:", nullptr));
        label_clientEvents->setText(QCoreApplication::translate("MainWindow", "Events", nullptr));
        pushButton_connectToServer->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        pushButton_disconnectFromServer->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Server", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Server status:", nullptr));
        label_serverStatus->setText(QCoreApplication::translate("MainWindow", "server status", nullptr));
        pushButton_startServer->setText(QCoreApplication::translate("MainWindow", "Start Server", nullptr));
        pushButton_stopServer->setText(QCoreApplication::translate("MainWindow", "Stop Server", nullptr));
        pushButton_disconnectClient->setText(QCoreApplication::translate("MainWindow", "Disconnect Client", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
