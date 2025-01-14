#include <QNetworkDiskCache>
#include <QStandardPaths>
#include <QWebFrame>

#include "cookiejar.h"
#include "mainwindow.h"
#include "view.h"


MainWindow::MainWindow() : QMainWindow()
{
    QWebSettings::globalSettings()->setAttribute(QWebSettings::LocalStorageEnabled, true);

    QNetworkAccessManager* manager = new QNetworkAccessManager(this);
    QNetworkDiskCache* diskCache = new QNetworkDiskCache(this);
    CookieJar* cookieJar = new CookieJar(this);
    QString cacheLocation = QStandardPaths::writableLocation(QStandardPaths::CacheLocation);

    diskCache->setCacheDirectory(cacheLocation);
    manager->setCache(diskCache);
    manager->setCookieJar(cookieJar);

    view = new View(this);
    view->page()->setNetworkAccessManager(manager);
    view->page()->mainFrame()->setScrollBarPolicy(Qt::Vertical, Qt::ScrollBarAlwaysOff);
    view->page()->mainFrame()->setScrollBarPolicy(Qt::Horizontal, Qt::ScrollBarAlwaysOff);
    setCentralWidget(view);
}

void MainWindow::loadPage(const QString &uri)
{
    view->loadPage(uri);
}

void MainWindow:: loadImage(const QString &uri)
{
    view->loadImage(uri);
}
