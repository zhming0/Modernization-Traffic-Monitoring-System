#include "clientmainwindow.h"
#include "ui_clientmainwindow.h"

#include "imagelistmodelproxy.h"
#include "clientsocketproxy.h"
#include "clientlogindialog.h"
#include "imagelistitem.h"
#include "imagepreviewdialog.h"

#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>

//172.28.12.217
ClientMainWindow::ClientMainWindow(ClientSocketProxy* socketProxy, ImageListModelProxy* modelProxy,  QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::ClientMainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setShown(false);

    setModelProxy(modelProxy);


    setSocketProxy(socketProxy);
    this->adjustSize();
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
        ui->tableView->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
        ui->tableView->horizontalHeader()->setResizeMode(2, QHeaderView::ResizeToContents);

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
    QMessageBox::about(this, "About", "");
}

void ClientMainWindow::on_pushButton_open_clicked()
{
    open();
}

void ClientMainWindow::on_pushButton_remove_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    QList<int> selectedRows;
    foreach(QModelIndex index, selectedIndexes)
    {
        selectedRows << index.row();
    }
    int lastRow = -1;
    if(!selectedRows.empty())
    {
        lastRow = selectedRows.last();
    }
    m_modelProxy->remove(selectedRows);
}
void ClientMainWindow::on_pushButton_clear_clicked()
{
    ui->tableView->selectAll();
    on_pushButton_remove_clicked();
}

void ClientMainWindow::on_pushButton_send_clicked()
{
   // m_modelProxy-
    m_socketProxy->sendImage();
}

void ClientMainWindow::on_pushButton_terminate_clicked()
{
    m_socketProxy->terminate();
}

void ClientMainWindow::on_pushButton_preview_clicked()
{
    ImagePreviewDialog dialog;
    dialog.exec();
}

void ClientMainWindow::open()
{
    QStringList fileNames = QFileDialog::getOpenFileNames(this, tr("Open Files"),QDir::currentPath());
    foreach(QString fileName, fileNames)
    {
        if(!fileName.isEmpty())
        {
            if(QFile::exists(fileName))
            {
                QFileInfo info(fileName);
                ImageListItem item(info);
                this->m_modelProxy->add(item);
            }
            else
            {
                QMessageBox::warning(this,
                                     "Warning", QString("File %1 does not exist.").arg(fileName));
                continue;
            }

        }
    }
}



