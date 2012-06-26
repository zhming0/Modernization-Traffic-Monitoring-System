#include "serverwindow.h"
#include "ui_serverwindow.h"
#include "serverproxy.h"

ServerWindow::ServerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerWindow)
{
    ui->setupUi(this);
    m_server = new ServerProxy(this);
    m_server->startListening(4000);
}

ServerWindow::~ServerWindow()
{
    delete ui;
}

