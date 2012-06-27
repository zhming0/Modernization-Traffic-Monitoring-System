#include "serverwindow.h"
#include "ui_serverwindow.h"
#include "server.h"

ServerWindow::ServerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerWindow)
{
    ui->setupUi(this);
    m_server = new Server(this);
    m_server->startListening(4000);
}

ServerWindow::~ServerWindow()
{
    delete ui;
}

