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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextBrowser *textBrowser;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_receiver;
    QPushButton *button_setPreferences;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_net_preferences;
    QLabel *label_ipv4;
    QLineEdit *lineEdit_ipv4;
    QLabel *label_port;
    QLineEdit *lineEdit_port;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QPushButton *connectButton;
    QLabel *label_2;
    QLineEdit *lineEdit_messageToSend;
    QPushButton *pushButton_sendMessage;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        textBrowser = new QTextBrowser(centralwidget);
        textBrowser->setObjectName("textBrowser");
        textBrowser->setGeometry(QRect(10, 10, 381, 311));
        horizontalLayoutWidget_2 = new QWidget(centralwidget);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(400, 330, 381, 171));
        horizontalLayout_receiver = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_receiver->setObjectName("horizontalLayout_receiver");
        horizontalLayout_receiver->setContentsMargins(0, 0, 0, 0);
        button_setPreferences = new QPushButton(centralwidget);
        button_setPreferences->setObjectName("button_setPreferences");
        button_setPreferences->setGeometry(QRect(270, 330, 91, 24));
        horizontalLayoutWidget_3 = new QWidget(centralwidget);
        horizontalLayoutWidget_3->setObjectName("horizontalLayoutWidget_3");
        horizontalLayoutWidget_3->setGeometry(QRect(10, 330, 251, 24));
        horizontalLayout_net_preferences = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_net_preferences->setObjectName("horizontalLayout_net_preferences");
        horizontalLayout_net_preferences->setContentsMargins(0, 0, 0, 0);
        label_ipv4 = new QLabel(horizontalLayoutWidget_3);
        label_ipv4->setObjectName("label_ipv4");

        horizontalLayout_net_preferences->addWidget(label_ipv4);

        lineEdit_ipv4 = new QLineEdit(horizontalLayoutWidget_3);
        lineEdit_ipv4->setObjectName("lineEdit_ipv4");
        lineEdit_ipv4->setMaxLength(20);

        horizontalLayout_net_preferences->addWidget(lineEdit_ipv4);

        label_port = new QLabel(horizontalLayoutWidget_3);
        label_port->setObjectName("label_port");
        label_port->setLineWidth(1);

        horizontalLayout_net_preferences->addWidget(label_port);

        lineEdit_port = new QLineEdit(horizontalLayoutWidget_3);
        lineEdit_port->setObjectName("lineEdit_port");
        lineEdit_port->setMaximumSize(QSize(60, 16777215));
        lineEdit_port->setMaxLength(6);
        lineEdit_port->setFrame(true);

        horizontalLayout_net_preferences->addWidget(lineEdit_port);

        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(10, 360, 251, 128));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        connectButton = new QPushButton(verticalLayoutWidget);
        connectButton->setObjectName("connectButton");
        connectButton->setEnabled(true);

        verticalLayout->addWidget(connectButton);

        label_2 = new QLabel(verticalLayoutWidget);
        label_2->setObjectName("label_2");

        verticalLayout->addWidget(label_2);

        lineEdit_messageToSend = new QLineEdit(verticalLayoutWidget);
        lineEdit_messageToSend->setObjectName("lineEdit_messageToSend");
        lineEdit_messageToSend->setMaxLength(256);

        verticalLayout->addWidget(lineEdit_messageToSend);

        pushButton_sendMessage = new QPushButton(verticalLayoutWidget);
        pushButton_sendMessage->setObjectName("pushButton_sendMessage");

        verticalLayout->addWidget(pushButton_sendMessage);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 22));
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
        button_setPreferences->setText(QCoreApplication::translate("MainWindow", "Set preferences", nullptr));
        label_ipv4->setText(QCoreApplication::translate("MainWindow", "IP", nullptr));
        lineEdit_ipv4->setInputMask(QString());
        lineEdit_ipv4->setText(QCoreApplication::translate("MainWindow", "127.0.0.1", nullptr));
        label_port->setText(QCoreApplication::translate("MainWindow", ":", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Connection status:", nullptr));
        connectButton->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Events:", nullptr));
        lineEdit_messageToSend->setInputMask(QString());
        lineEdit_messageToSend->setText(QCoreApplication::translate("MainWindow", "Send message", nullptr));
        pushButton_sendMessage->setText(QCoreApplication::translate("MainWindow", "Send", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
