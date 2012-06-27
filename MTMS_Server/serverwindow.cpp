#include "serverwindow.h"
#include "ui_serverwindow.h"
#include "server.h"
#include "imagelistmodelproxy.h"
#include"serverdbinterface.h"
#include"imagelistitem.h"

#include<QDebug>
#include<QDateTime>
#include <QFileInfo>
#include<QDir>
#include<QFile>
#include<QStringList>

ServerWindow::ServerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerWindow)
{
    ui->setupUi(this);
    initTableViews();

    m_server = new Server(this);
    enable = false;
    imagePath = "images/";

    initConnection();
    loadImageList();
}
ServerWindow::~ServerWindow()
{
    delete ui;
}

void ServerWindow::initConnection()
{
    connect(m_server, SIGNAL(logGenerated(QString)),
            this, SLOT(on_m_server_logGenerated(QString)));
    connect(m_server, SIGNAL(imageRead(QByteArray)),
            this, SLOT(on_m_server_imageRead(QByteArray)));
}

void ServerWindow::loadImageList()
{
    QList<QStringList> list = ServerDBInterface::getImageList();
    for (int i = 0; i < list.size(); i++)
    {
        QFile* file = new QFile(list[i][2] + list[i][0]);
        ImageListItem item(file, this);
        ImageListModelProxy::Status tmp = (ImageListModelProxy::Status)list[i][1].toInt();
        if (tmp == ImageListModelProxy::UNRECOGNIZED)
            m_modelProxy_unrecognized->add(item);
        else {
            m_modelProxy_recognized->add(item);
            m_modelProxy_recognized->setStatus(m_modelProxy_recognized->rowCount() - 1, tmp);
        }
    }
}

void ServerWindow::on_serverEnableButton_clicked()
{
    if (enable)
    {
        enable = false;
        m_server->stopListening();
        ui->serverEnableButton->setText("Start Server");
    }else {
        enable = true;
        m_server->startListening(ui->portSpinBox->text().toInt());
        ui->serverEnableButton->setText("Stop Server");
    }
}

void ServerWindow::on_m_server_logGenerated(const QString& s)
{
    QString datatime = QDateTime::currentDateTime().toString();
    ui->logArea->append(datatime +":    "+ s);
}

void ServerWindow::on_m_server_imageRead(const QByteArray & bytes)
{
    QPixmap* pixelmap = new QPixmap();
    //QImage image;
    pixelmap->loadFromData(bytes, "PNG");
    ui->imageWidget->load(*pixelmap, "");
    QString filename = QDateTime::currentDateTime().toString() + ".png";
    pixelmap->save(imagePath + filename, "PNG");
    ServerDBInterface::addImage(filename, QDir::currentPath() + "/" + imagePath);

    QFile* file = new QFile(imagePath + filename);
    if (file->exists())
    {
        ImageListItem item(file, this);
        m_modelProxy_unrecognized->add(item);
    }
    else
        on_m_server_logGenerated(imagePath + filename + " is invalid.");
}

void ServerWindow::initTableViews()
{
    m_modelProxy_recognized = new ImageListModelProxy(this);
    ui->tableView_recognized->setModel((QAbstractItemModel*)m_modelProxy_recognized->model());
    ui->tableView_recognized->setColumnHidden(1, true);
    ui->tableView_recognized->setColumnHidden(2, true);
    ui->tableView_recognized->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    ui->tableView_recognized->horizontalHeader()->setResizeMode(3,QHeaderView::ResizeToContents);
    m_modelProxy_unrecognized = new ImageListModelProxy(this);
    ui->tableView_unrecognized->setModel((QAbstractItemModel*)m_modelProxy_unrecognized->model());
    ui->tableView_unrecognized->setColumnHidden(1, true);
    ui->tableView_unrecognized->setColumnHidden(2, true);
    ui->tableView_unrecognized->setColumnHidden(3, true);
    ui->tableView_unrecognized->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);

}

void ServerWindow::on_pushButton_update_clicked()
{
    QModelIndexList list = ui->tableView_recognized->selectionModel()->selectedRows();
    if(!list.empty())
    {
        int r = list.first().row();
        m_modelProxy_recognized->setStatus(r, ImageListModelProxy::PROCESSED);
    }
}

void ServerWindow::on_pushButton_processAll_clicked()
{
    int rowCount = m_modelProxy_unrecognized->rowCount();
    for(int i = 0; i < rowCount; ++i)
    {
        ui->tableView_unrecognized->selectRow(0);
        QModelIndexList list = ui->tableView_unrecognized->selectionModel()->selectedRows();
        if(!list.empty())
        {
            int r = list.first().row();
            QFile file(this->m_modelProxy_unrecognized->path(r));
            if(file.exists())
            {
                QFileInfo fileInfo(file);
                ImageListItem item(fileInfo);
                m_modelProxy_recognized->add(item);
                this->m_modelProxy_unrecognized->remove(r);
            }
        }
    }
}

void ServerWindow::on_pushButton_clearAllProcessed_clicked()
{
    int rowCount = m_modelProxy_recognized->rowCount();
    QList<int> removeList;
    for(int i = 0; i < rowCount; ++i)
    {
        if(m_modelProxy_recognized->status(i) == ImageListModelProxy::PROCESSED)
        {
            removeList << i;
        }
    }
    m_modelProxy_recognized->remove(removeList);
}

void ServerWindow::on_pushButton_recognize_clicked()
{
    QModelIndexList list = ui->tableView_unrecognized->selectionModel()->selectedRows();
    if(!list.empty())
    {
        int r = list.first().row();
        QFile file(this->m_modelProxy_unrecognized->path(r));
        if(file.exists())
        {
            QFileInfo fileInfo(file);
            ImageListItem item(fileInfo);
            m_modelProxy_recognized->add(item);
            this->m_modelProxy_unrecognized->remove(r);
        }
    }
}




