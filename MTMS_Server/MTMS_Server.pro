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
        serverproxy.cpp \
    serverdbinterface.cpp

HEADERS  += serverwindow.h \
            serverproxy.h \
    serverdbinterface.h

FORMS    += serverwindow.ui








