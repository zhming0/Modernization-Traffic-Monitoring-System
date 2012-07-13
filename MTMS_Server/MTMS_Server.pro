#-------------------------------------------------
#
# Project created by QtCreator 2012-06-26T11:02:48
#
# Modernization-Traffic-Monitoring-System
# It is a C/S architecture desktop application, in
# whose server side, users are able to recognize
# car plate numbers.
#-------------------------------------------------

QT       += core gui xml
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
    serverlogindialog.cpp \
    imagelistmodelproxy.cpp \
    imagelistitem.cpp \
    recognizedialog.cpp \
    neuron.cpp \
    neuralnetworkxmlhandler.cpp \
    neuralnetwork.cpp \
    neurallayer.cpp \
    gradient.cpp

HEADERS  += serverwindow.h \
    serverdbinterface.h \
    serversocket.h \
    server.h \
    imagewidget.h \
    serverlogindialog.h \
    imagelistitem.h \
    imagelistmodelproxy.h \
    recognizedialog.h \
    neuron.h \
    neuralnetworkxmlhandler.h \
    neuralnetwork.h \
    neurallayer.h \
    gradient.h

FORMS    += serverwindow.ui \
    serverlogindialog.ui \
    recognizedialog.ui

RESOURCES += \
    images.qrc

RC_FILE = logo.rc


