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
#include <QtWidgets/QFormLayout>
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
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QHBoxLayout *horizontalLayout_net_preferences;
    QLabel *label_ipv4;
    QLineEdit *lineEdit_ipv4;
    QLabel *label_port;
    QLineEdit *lineEdit_port;
    QPushButton *button_setPreferences;
    QLabel *label;
    QLabel *label_clietnConnection;
    QLabel *label_2;
    QLabel *label_clientEvents;
    QLabel *label_3;
    QLabel *label_serverStatus;
    QPushButton *connectButton;
    QPushButton *pushButton_startServer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(850, 600);
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
        formLayoutWidget = new QWidget(centralwidget);
        formLayoutWidget->setObjectName("formLayoutWidget");
        formLayoutWidget->setGeometry(QRect(530, 10, 311, 217));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName("formLayout");
        formLayout->setVerticalSpacing(5);
        formLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_net_preferences = new QHBoxLayout();
        horizontalLayout_net_preferences->setObjectName("horizontalLayout_net_preferences");
        label_ipv4 = new QLabel(formLayoutWidget);
        label_ipv4->setObjectName("label_ipv4");

        horizontalLayout_net_preferences->addWidget(label_ipv4);

        lineEdit_ipv4 = new QLineEdit(formLayoutWidget);
        lineEdit_ipv4->setObjectName("lineEdit_ipv4");
        lineEdit_ipv4->setMaxLength(23);

        horizontalLayout_net_preferences->addWidget(lineEdit_ipv4);

        label_port = new QLabel(formLayoutWidget);
        label_port->setObjectName("label_port");
        label_port->setLineWidth(1);

        horizontalLayout_net_preferences->addWidget(label_port);

        lineEdit_port = new QLineEdit(formLayoutWidget);
        lineEdit_port->setObjectName("lineEdit_port");
        lineEdit_port->setMaximumSize(QSize(40, 16777215));
        lineEdit_port->setMaxLength(5);
        lineEdit_port->setFrame(true);

        horizontalLayout_net_preferences->addWidget(lineEdit_port);

        button_setPreferences = new QPushButton(formLayoutWidget);
        button_setPreferences->setObjectName("button_setPreferences");

        horizontalLayout_net_preferences->addWidget(button_setPreferences);


        formLayout->setLayout(0, QFormLayout::ItemRole::LabelRole, horizontalLayout_net_preferences);

        label = new QLabel(formLayoutWidget);
        label->setObjectName("label");
        QFont font;
        font.setBold(true);
        font.setUnderline(false);
        label->setFont(font);

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label);

        label_clietnConnection = new QLabel(formLayoutWidget);
        label_clietnConnection->setObjectName("label_clietnConnection");
        label_clietnConnection->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        formLayout->setWidget(2, QFormLayout::ItemRole::SpanningRole, label_clietnConnection);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName("label_2");
        label_2->setFont(font);

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_2);

        label_clientEvents = new QLabel(formLayoutWidget);
        label_clientEvents->setObjectName("label_clientEvents");
        label_clientEvents->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);

        formLayout->setWidget(4, QFormLayout::ItemRole::LabelRole, label_clientEvents);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName("label_3");
        label_3->setFont(font);

        formLayout->setWidget(5, QFormLayout::ItemRole::LabelRole, label_3);

        label_serverStatus = new QLabel(formLayoutWidget);
        label_serverStatus->setObjectName("label_serverStatus");

        formLayout->setWidget(6, QFormLayout::ItemRole::LabelRole, label_serverStatus);

        connectButton = new QPushButton(formLayoutWidget);
        connectButton->setObjectName("connectButton");
        connectButton->setEnabled(true);

        formLayout->setWidget(8, QFormLayout::ItemRole::LabelRole, connectButton);

        pushButton_startServer = new QPushButton(formLayoutWidget);
        pushButton_startServer->setObjectName("pushButton_startServer");

        formLayout->setWidget(7, QFormLayout::ItemRole::LabelRole, pushButton_startServer);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 850, 22));
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
        label_ipv4->setText(QCoreApplication::translate("MainWindow", "IP", nullptr));
        lineEdit_ipv4->setInputMask(QString());
        lineEdit_ipv4->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        lineEdit_ipv4->setPlaceholderText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        label_port->setText(QCoreApplication::translate("MainWindow", ":", nullptr));
        lineEdit_port->setText(QCoreApplication::translate("MainWindow", "8000", nullptr));
        lineEdit_port->setPlaceholderText(QCoreApplication::translate("MainWindow", "8000", nullptr));
        button_setPreferences->setText(QCoreApplication::translate("MainWindow", "Set preferences", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Client connection status:", nullptr));
        label_clietnConnection->setText(QCoreApplication::translate("MainWindow", "Connection status", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Client events:", nullptr));
        label_clientEvents->setText(QCoreApplication::translate("MainWindow", "Events", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Server status:", nullptr));
        label_serverStatus->setText(QCoreApplication::translate("MainWindow", "server status", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        pushButton_startServer->setText(QCoreApplication::translate("MainWindow", "Start Server", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
