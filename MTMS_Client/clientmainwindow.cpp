#include "clientmainwindow.h"
#include "ui_clientmainwindow.h"

#include "imagelistmodelproxy.h"
#include "clientsocketproxy.h"
#include "clientlogindialog.h"

#include <QDebug>


ClientMainWindow::ClientMainWindow(ClientSocketProxy* socketProxy, ImageListModelProxy* modelProxy, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ClientMainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setShown(false);
    setModelProxy(modelProxy);
    setSocketProxy(socketProxy);
    this->adjustSize();
    m_loginDialog = new ClientLoginDialog(socketProxy, this);
    if(m_loginDialog->exec() == QDialog::Rejected)
    {
        this->hide();
        this->close();
    }
    else
    {
        this->show();
    }

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
    open();
}

void ClientMainWindow::on_action_Exit_triggered()
{
    this->close();
}

void ClientMainWindow::on_action_About_triggered()
{

}

void ClientMainWindow::on_pushButton_open_clicked()
{

}

void ClientMainWindow::on_pushButton_remove_clicked()
{

}

void ClientMainWindow::on_pushButton_send_clicked()
{

}

void ClientMainWindow::on_pushButton_terminate_clicked()
{

}

void ClientMainWindow::open()
{

}



