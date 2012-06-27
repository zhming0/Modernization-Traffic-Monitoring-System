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
        ui->tableView->setModel((QAbstractItemModel*)m_modelProxy->model());
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
    if(lastRow != -1 &&
       m_modelProxy->rowCount() > 0)
    {
        int rowToBeSelected = lastRow - selectedRows.length();
        if(rowToBeSelected < 0)
        {
            rowToBeSelected =  0;
        }
        ui->tableView->selectRow(rowToBeSelected);
    }
}
void ClientMainWindow::on_pushButton_clear_clicked()
{
    ui->tableView->selectAll();
    on_pushButton_remove_clicked();
}

void ClientMainWindow::on_pushButton_check_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    QList<int> selectedRows;
    foreach(QModelIndex index, selectedIndexes)
    {
        selectedRows << index.row();
    }
    foreach(int i, selectedRows)
    {
        this->m_modelProxy->setChecked(i, true);
    }
}

void ClientMainWindow::on_pushButton_checkAll_clicked()
{
    for(int i = 0; i < m_modelProxy->rowCount(); ++i)
    {
        this->m_modelProxy->setChecked(i, true);
    }
}

void ClientMainWindow::on_pushButton_uncheck_clicked()
{
    QModelIndexList selectedIndexes = ui->tableView->selectionModel()->selectedRows();
    QList<int> selectedRows;
    foreach(QModelIndex index, selectedIndexes)
    {
        selectedRows << index.row();
    }
    foreach(int i, selectedRows)
    {
        this->m_modelProxy->setChecked(i, false);
    }
}

void ClientMainWindow::on_pushButton_uncheckAll_clicked()
{
    for(int i = 0; i < m_modelProxy->rowCount(); ++i)
    {
        this->m_modelProxy->setChecked(i, false);
    }
}

void ClientMainWindow::on_pushButton_send_clicked()
{
    this->ui->progressBar->setValue(0);
    this->ui->progressBar->setShown(true);
    this->adjustSize();
    QStringList paths = m_modelProxy->checkedPaths();
    QList<int> checkedRows = m_modelProxy->checkedRows();
    for(int i = 0; i < checkedRows.size(); ++i)
    {
        this->m_modelProxy->setStatus(checkedRows.at(i), ImageListModelProxy::READY);
    }
    QList<int> errorRows;
    for(int i = 0; i < paths.length(); ++i)
    {
        this->m_modelProxy->setStatus(checkedRows.at(i), ImageListModelProxy::SENDING);
        QString path = paths.at(i);
        QImage image(path);
        if(image.isNull())
        {
            errorRows << checkedRows.at(i);
            this->m_modelProxy->setStatus(checkedRows.at(i), ImageListModelProxy::ERROR);
            int button = QMessageBox::warning(this, "Warning",
                                 QString("File %1 is invalid. Do you want to continue?")
                                 .arg(path), QMessageBox::Yes, QMessageBox::No);
            if(QMessageBox::No == button)
            {
                break;
            }
            else if(QMessageBox::Yes == button)
            {
                continue;
            }
        }
        else
        {
            this->m_socketProxy->sendImage(image, "PNG");
            this->m_modelProxy->setChecked(checkedRows.at(i), false);
            this->m_modelProxy->setStatus(checkedRows.at(i), ImageListModelProxy::FINISHED);
        }
        //this->ui->progressBar->setValue(int(100.0 / path.length() * i));
    }
    qDebug() << errorRows;
    //this->ui->progressBar->setValue(100);
    //this->ui->progressBar->setShown(false);
    this->m_modelProxy->remove(errorRows);
    this->adjustSize();
}

void ClientMainWindow::on_pushButton_terminate_clicked()
{
    m_socketProxy->terminate();
}

void ClientMainWindow::on_pushButton_preview_clicked()
{
    QModelIndexList list = this->ui->tableView->selectionModel()->selectedRows();
    if(list.isEmpty())
        return;
    int row = list.first().row();
    QImage image(this->m_modelProxy->path(row));
    if(image.isNull())
    {

    } else
    {
        ImagePreviewDialog dialog(image);
        dialog.exec();
    }

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

