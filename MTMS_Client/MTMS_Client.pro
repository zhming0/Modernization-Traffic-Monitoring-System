#-------------------------------------------------
#
# Project created by QtCreator 2012-06-25T16:56:51
#
# Modernization-Traffic-Monitoring-System
# It is a C/S architecture desktop application, in
# whose server side, users are able to recognize
# car plate numbers.
#-------------------------------------------------

QT       += core gui
QT       += network

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



RESOURCES += \
    images.qrc
RC_FILE = logo.rc

