TEMPLATE = app

QT += core dbus webkit webkitwidgets
CONFIG += c++11

SOURCES += src/cookiejar.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/view.cpp

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(src/deployment.pri)

HEADERS += \
    src/mainwindow.h \
    src/view.h
