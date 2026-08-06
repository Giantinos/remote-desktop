#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QFile>

// #include <QLineEdit>
// #include <QTextEdit>
// #include <QPushButton>
// #include <QLabel>
// #include <QVBoxLayout>
// #include <QTcpSocket>
// #include <QTcpServer>
// #include <QMessageBox>
void applyStylesheet(QApplication &app) {
    QFile file(":/styles/styles.qss");

    if (file.open(QFile::ReadOnly)) {
        QString styleSheet = QLatin1String(file.readAll());
        app.setStyleSheet(styleSheet);
        file.close();
    } else {
        qDebug() << "Не удалось загрузить стили";
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Ardis_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    // applyStylesheet(a);
    w.show();
    return QCoreApplication::exec();
}

