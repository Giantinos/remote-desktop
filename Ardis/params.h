#ifndef PARAMS_H
#define PARAMS_H

#include <QString>

// --- Параметры сети ---
const int DEFAULT_PORT = 12345; // Порт, на котором будет работать сервер
const QString DEFAULT_HOST = "127.0.0.1"; // IP-адрес по умолчанию (localhost)
const int CONNECTION_TIMEOUT = 30000; // Таймаут на подключение
const QString CLIENT_HANDSHAKE = "HELLO_ARDIS";
const QString SERVER_HANDSHAKE = "HELLO_ARDIS_ACK";

#endif // PARAMS_H
