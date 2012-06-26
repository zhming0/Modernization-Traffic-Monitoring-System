#-------------------------------------------------
#
# Project created by QtCreator 2012-06-25T16:56:51
#
#-------------------------------------------------

QT       += core gui

TARGET = MTMS_Client
TEMPLATE = app


SOURCES += main.cpp\
        clientmainwindow.cpp \
    clientlogindialog.cpp \
    imagelistmodelproxy.cpp \
    imagelistitem.cpp \
    clientsocketproxy.cpp

HEADERS  += clientmainwindow.h \
    clientlogindialog.h \
    imagelistmodelproxy.h \
    imagelistitem.h \
    clientsocketproxy.h

FORMS    += clientmainwindow.ui \
    clientlogindialog.ui

QT += network
