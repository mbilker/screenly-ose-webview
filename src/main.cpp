#include <QCoreApplication>
#include <QApplication>
#include <QDebug>
#include <QWebView>
#include <QtDBus>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("Screenly");
    QCoreApplication::setApplicationName("ScreenlyWebview");

    QCursor cursor(Qt::BlankCursor);
    QApplication::setOverrideCursor(cursor);
    QApplication::changeOverrideCursor(cursor);

    MainWindow *window = new MainWindow();
    window->show();

    QDBusConnection connection = QDBusConnection::systemBus();

    if (!connection.registerObject("/Screenly", window, QDBusConnection::ExportAllSlots))
    {
        qWarning() << "Can't register object";
        return 1;
    }
    qDebug() << "WebView connected to D-bus";

    if (!connection.registerService("screenly.webview")) {
        qWarning() << qPrintable(connection.lastError().message());
        return 1;
    }
    qDebug() << "Screenly service start";

    return app.exec();
}
