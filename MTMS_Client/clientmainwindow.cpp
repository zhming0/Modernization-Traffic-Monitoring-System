#include "clientmainwindow.h"
#include "ui_clientmainwindow.h"

#include "imagelistmodelproxy.h"
#include "clientsocketproxy.h"

#include <QDebug>


ClientMainWindow::ClientMainWindow(ClientSocketProxy* socketProxy, ImageListModelProxy* modelProxy, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientMainWindow)
{
    ui->setupUi(this);
    setModelProxy(modelProxy);
    setSocketProxy(socketProxy);
}

ClientMainWindow::~ClientMainWindow()
{
    delete ui;
}

void ClientMainWindow::setModelProxy(ImageListModelProxy* modelProxy)
{
    m_modelProxy = modelProxy;
    if(m_modelProxy != NULL)
    {
        ui->tableView->setModel(m_modelProxy->model());
    }
}

void ClientMainWindow::setSocketProxy(ClientSocketProxy* socketProxy)
{
    m_socketProxy = socketProxy;
}

void ClientMainWindow::on_action_Open_triggered()
{

}

void ClientMainWindow::on_action_Exit_triggered()
{
    this->close();
}

void ClientMainWindow::on_action_About_triggered()
{

}




