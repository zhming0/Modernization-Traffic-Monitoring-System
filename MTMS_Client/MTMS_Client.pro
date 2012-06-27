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
    clientsocketproxy.cpp \
    imagewidget.cpp \
    imagepreviewdialog.cpp

HEADERS  += clientmainwindow.h \
    clientlogindialog.h \
    imagelistmodelproxy.h \
    imagelistitem.h \
    clientsocketproxy.h \
    imagewidget.h \
    imagepreviewdialog.h

FORMS    += clientmainwindow.ui \
    clientlogindialog.ui \
    imagepreviewdialog.ui

QT += network

RESOURCES += \
    images.qrc
