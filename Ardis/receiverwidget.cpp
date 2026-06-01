#include "receiverwidget.h"

ReceiverWidget::ReceiverWidget(int port, QWidget *parent) : QWidget(parent) {
    receivedMessages = new QTextEdit(this);
        receivedMessages->setReadOnly(true);
        statusLabel = new QLabel("Статус: Сервер не запущен.");

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(receivedMessages);
        layout->addWidget(statusLabel);

        server = new QTcpServer(this);
        // Пытаемся прослушивать на указанном порту
        if (!server->listen(QHostAddress::Any, port)) { // QHostAddress::Any слушает на всех доступных сетевых интерфейсах
            QString errorMsg = QString("Не удалось запустить сервер на порту %1: %2").arg(port).arg(server->errorString());
            statusLabel->setText("Статус: Ошибка запуска сервера.");
            QMessageBox::critical(this, "Ошибка", errorMsg);

            //++++++edited below+++++++

            server->deleteLater();
        } else {
            QString listenAddress = server->serverAddress().toString();
            if (listenAddress.isEmpty() || listenAddress == "0.0.0.0") {
                // Если слушает на всех, показываем, на чем реально
                listenAddress = "Все интерфейсы";
            }
            statusLabel->setText(QString("Статус: Сервер запущен. Слушает на %1:%2").arg(listenAddress).arg(port));
            connect(server, &QTcpServer::newConnection, this, &ReceiverWidget::onNewConnection);

            receivedMessages->append("Сервер запущен. Ожидание подключений...");
        }
    }

    void ReceiverWidget::onNewConnection() {
        QTcpSocket *clientSocket = server->nextPendingConnection();
        if (clientSocket) {
            QString clientAddress = clientSocket->peerAddress().toString();
            int clientPort = clientSocket->peerPort();
            receivedMessages->append(QString("Новый клиент подключился: %1:%2").arg(clientAddress).arg(clientPort));
            statusLabel->setText(QString("Статус: Клиент подключен (%1:%2)").arg(clientAddress).arg(clientPort));

            connect(clientSocket, &QTcpSocket::readyRead, this, &ReceiverWidget::onReadyRead);
            connect(clientSocket, &QTcpSocket::disconnected, this, &ReceiverWidget::onClientDisconnected);
            // Можно добавить map для хранения клиентских сокетов
        }
    }

    void ReceiverWidget::onReadyRead() {
        QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
        if (clientSocket) {
            QByteArray data = clientSocket->readAll();
            QString message = QString::fromUtf8(data);
            QString clientAddress = clientSocket->peerAddress().toString();
            int clientPort = clientSocket->peerPort();
            receivedMessages->append(QString("%1:%2> %3").arg(clientAddress).arg(clientPort).arg(message));
        }
    }

    void ReceiverWidget::onClientDisconnected() {
        QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
        if (clientSocket) {
            QString clientAddress = clientSocket->peerAddress().toString();
            int clientPort = clientSocket->peerPort();
            receivedMessages->append(QString("Клиент отключился: %1:%2").arg(clientAddress).arg(clientPort));
            statusLabel->setText("Статус: Сервер активен. Ожидание подключений...");
            clientSocket->deleteLater(); // Освободить память
        }
    }
