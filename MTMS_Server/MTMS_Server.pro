#-------------------------------------------------
#
# Project created by QtCreator 2012-06-26T11:02:48
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql

TARGET = MTMS_Server
TEMPLATE = app


SOURCES += main.cpp\
        serverwindow.cpp \
    serverdbinterface.cpp \
    serversocket.cpp \
    server.cpp \
    imagewidget.cpp \
    serverlogindialog.cpp

HEADERS  += serverwindow.h \
    serverdbinterface.h \
    serversocket.h \
    server.h \
    imagewidget.h \
    serverlogindialog.h

FORMS    += serverwindow.ui \
    serverlogindialog.ui























