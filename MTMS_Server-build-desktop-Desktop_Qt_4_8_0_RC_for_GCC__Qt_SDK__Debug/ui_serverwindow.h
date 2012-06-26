/********************************************************************************
** Form generated from reading UI file 'serverwindow.ui'
**
** Created: Tue Jun 26 14:30:01 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERVERWINDOW_H
#define UI_SERVERWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ServerWindow
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ServerWindow)
    {
        if (ServerWindow->objectName().isEmpty())
            ServerWindow->setObjectName(QString::fromUtf8("ServerWindow"));
        ServerWindow->resize(400, 300);
        menuBar = new QMenuBar(ServerWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        ServerWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ServerWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        ServerWindow->addToolBar(mainToolBar);
        centralWidget = new QWidget(ServerWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        ServerWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(ServerWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ServerWindow->setStatusBar(statusBar);

        retranslateUi(ServerWindow);

        QMetaObject::connectSlotsByName(ServerWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ServerWindow)
    {
        ServerWindow->setWindowTitle(QApplication::translate("ServerWindow", "ServerWindow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ServerWindow: public Ui_ServerWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERVERWINDOW_H
