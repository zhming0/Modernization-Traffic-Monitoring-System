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
#include <QTimer>
#include <QThread>
#include <QApplication>
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

    /* Do not modify the sequence of the following function calls.*/
    /**/c_redLightPath = ":/led_red_black.png";
    /**/c_greenLightPath = ":/led_green_black.png";
    /**/this->m_connecting_timer = NULL;
    /**///this->on_connected();

    m_timer = new QTimer(this);

    connect(this->m_socketProxy, SIGNAL(timeout()), this, SLOT(on_disconnected()));
    connect(this->m_socketProxy, SIGNAL(login_succeeded()), this, SLOT(on_connected()));
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
    //QThread* thread = new QThread();
    m_socketProxy = socketProxy;
    //m_socketProxy->moveToThread(thread);
    //thread->start();
    //connect(m_socketProxy, SIGNAL(destroyed()), thread, SLOT(quit()));
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
    QMessageBox::about(this, "About", "<b>Modernization Traffic Monitoring System</b>\n"
"is a C/S architecture desktop application, in\n"
"whose server side, users are able to recognize\n"
"car plate numbers.\n");
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
    this->adjustSize();
    QStringList paths = m_modelProxy->checkedPaths();
    QList<int> checkedRows = m_modelProxy->checkedRows();
    total_sendData = m_modelProxy -> checkedSize();
    writtenBytes = 0;
    if (total_sendData > 0)
        this->ui->progressBar->setShown(true);
    connect(m_socketProxy, SIGNAL(bytesWritten(qint64)),
            this, SLOT(on_m_socketProxy_bytesWritten(qint64)));

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
            while (this->m_socketProxy->bytesToWrite() > 0) {
                QApplication::processEvents();
            }
            this->m_socketProxy->sendImage(image);

            this->m_modelProxy->setChecked(checkedRows.at(i), false);
            if (i > 0)
                this->m_modelProxy->setStatus(checkedRows.at(i - 1), ImageListModelProxy::FINISHED);
        }
        QApplication::processEvents();
    }
    while (this->m_socketProxy->bytesToWrite() > 0)
        QApplication::processEvents();
    if (paths.length() > 0)
        this->m_modelProxy->setStatus(checkedRows.at(paths.length() - 1), ImageListModelProxy::FINISHED);

    //qDebug() << errorRows;
    //this->ui->progressBar->setValue(100);
    //this->ui->progressBar->setShown(false);
    this->m_modelProxy->remove(errorRows);
    this->adjustSize();
}

void ClientMainWindow::on_pushButton_terminate_clicked()
{
    qDebug() << "I want to terminate!!!";
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

void ClientMainWindow::on_m_socketProxy_bytesWritten(qint64 v)
{
    writtenBytes += v;
    if (writtenBytes >= total_sendData - 1024) {
        qDebug() << "Finish!";
        this->ui->progressBar->setValue(100);
        this->ui->progressBar->hide();
        disconnect(m_socketProxy, SIGNAL(bytesWritten(qint64)),
                this, SLOT(on_m_socketProxy_bytesWritten(qint64)));
        return;
    }
    qDebug() << "total" << total_sendData;
    qDebug() << "value" << writtenBytes;
    ui->progressBar->setValue((double)writtenBytes * 100.0/total_sendData);
    QApplication::processEvents();
}

void ClientMainWindow::on_connecting()
{
    if(this->m_connecting_timer != NULL)
    {
        m_connecting_timer->stop();
        disconnect(m_connecting_timer, SIGNAL(timeout()), this, SLOT(on_m_connecting_timer_timeout()));
        m_connecting_timer->deleteLater();;
    }
    ui->label_connectionLight->setEnabled(true);
    ui->label_connection->setText("connecting");
    m_connecting_timer = new QTimer(this);
    connect(m_connecting_timer, SIGNAL(timeout()), this, SLOT(on_m_connecting_timer_timeout()));
    ui->label_connectionLight->setPixmap(QPixmap::fromImage(QImage(this->c_redLightPath)));
    m_connecting_timer->start(1000);
}

void ClientMainWindow::on_connected()
{

    ui->pushButton_send->setEnabled(true);
    ui->pushButton_terminate->setEnabled(true);
    if(this->m_connecting_timer != NULL)
    {
        m_connecting_timer->stop();
        disconnect(m_connecting_timer, SIGNAL(timeout()), this, SLOT(on_m_connecting_timer_timeout()));
        m_connecting_timer->deleteLater();;
    }
    m_connecting_timer = NULL;

    m_timer->stop();
    disconnect(m_timer, SIGNAL(timeout()), this->m_socketProxy, SLOT(reconnect()));


    ui->label_connectionLight->setEnabled(true);
    ui->label_connection->setText("connected");
    ui->label_connectionLight->setPixmap(QPixmap::fromImage(QImage(this->c_greenLightPath)));
}

void ClientMainWindow::on_disconnected()
{
    ui->pushButton_send->setEnabled(false);
    ui->pushButton_terminate->setEnabled(false);
    if(this->m_connecting_timer != NULL)
    {
        m_connecting_timer->stop();
        disconnect(m_connecting_timer, SIGNAL(timeout()), this, SLOT(on_m_connecting_timer_timeout()));
        m_connecting_timer->deleteLater();;
    }
    ui->label_connectionLight->setEnabled(true);
    ui->label_connection->setText("disconnected");
    ui->label_connectionLight->setPixmap(QPixmap::fromImage(QImage(this->c_redLightPath)));

    /* reconnection*/

    m_timer->stop();
    disconnect(m_timer, SIGNAL(timeout()), this->m_socketProxy, SLOT(reconnect()));

    m_timer->start(10000);
    connect(m_timer, SIGNAL(timeout()), this->m_socketProxy, SLOT(reconnect()));
    this->on_connecting();
}

void ClientMainWindow::on_m_connecting_timer_timeout()
{
    ui->label_connectionLight->setEnabled(!ui->label_connectionLight->isEnabled());
}
