#include "serverwindow.h"
#include "ui_serverwindow.h"
#include "server.h"
#include "imagelistmodelproxy.h"
#include"serverdbinterface.h"
#include"imagelistitem.h"

#include <QDebug>
#include <QDateTime>
#include <QFileInfo>
#include <QDir>
#include <QFile>
#include <QStringList>
#include <QModelIndex>
#include <QMessageBox>

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

    //connect(ui->tableView_unrecognized, SIGNAL(pressed(QModelIndex)), this, SLOT(on_tableView_unrecognized_pressed(QModelIndex)));
   // connect(ui->tableView_recognized, SIGNAL(pressed(QModelIndex)), this, SLOT(on_tableView_recognized_pressed(QModelIndex)));
}

void ServerWindow::loadImageList()
{
    QList<QStringList> list = ServerDBInterface::getImageList();
    for (int i = 0; i < list.size(); i++)
    {
        QFile file(list[i][2] + list[i][0]);
        QFileInfo fileInfo(file);
        QString timeString(list[i][0]);
        int pointIndex = timeString.indexOf('.');
        timeString = timeString.mid(0, pointIndex);
        qDebug() << timeString;
        qint64 time= (qint64)timeString.toInt();
        ImageListItem item(fileInfo, true, QDateTime::fromMSecsSinceEpoch(time).toString(), this);
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
    QPixmap pixelmap = QPixmap();
    pixelmap.loadFromData(bytes, "PNG");
    ui->imageWidget->load(pixelmap, "");
    qint64 currentMSecsSinceEpoch = QDateTime::currentMSecsSinceEpoch();
    QString filename = QString("%1.png").arg(currentMSecsSinceEpoch);
    filename = filename.trimmed();
    pixelmap.save(imagePath + filename, "PNG");
    qDebug() <<  "Image path : " << imagePath + filename;

    ServerDBInterface::addImage(filename, QDir::currentPath() + "/" + imagePath);

    QFile file(imagePath + filename);
    if (file.exists())
    {
        QFileInfo fileInfo(file);
        ImageListItem item(fileInfo, true, QDateTime::fromMSecsSinceEpoch(currentMSecsSinceEpoch).toString(), this);
        m_modelProxy_unrecognized->add(item);
    }
    else
        on_m_server_logGenerated(imagePath + filename + " is invalid.");
}

void ServerWindow::initTableViews()
{
    m_modelProxy_recognized = new ImageListModelProxy(ImageListModelProxy::UNPROCESSED, this);
    ui->tableView_recognized->setModel((QAbstractItemModel*)m_modelProxy_recognized->model());
    ui->tableView_recognized->setColumnHidden(1, true);
    ui->tableView_recognized->setColumnHidden(2, true);
    ui->tableView_recognized->horizontalHeader()->setResizeMode(0, QHeaderView::Stretch);
    ui->tableView_recognized->horizontalHeader()->setResizeMode(3,QHeaderView::ResizeToContents);
    m_modelProxy_unrecognized = new ImageListModelProxy(ImageListModelProxy::UNRECOGNIZED,this);
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

void ServerWindow::on_tableView_unrecognized_pressed(QModelIndex index)
{
    int row = index.row();
    QString path = m_modelProxy_unrecognized->path(row);
    QImage image(path);
    qDebug() << path;
    if(image.isNull())
    {
        m_modelProxy_unrecognized->setStatus(row, ImageListModelProxy::ERROR);
        QMessageBox::warning(this, "Warning", "File invalid, will be removed from the list.");
        ServerDBInterface::removeImage(m_modelProxy_unrecognized->name(row));
        m_modelProxy_unrecognized->remove(row);
        QFile::remove(path);
    }
    else
    {
        QPixmap pixmap = QPixmap::fromImage(image);
        ui->imageWidget->load(pixmap, "");
    }
}

void ServerWindow::on_tableView_recognized_pressed(QModelIndex index)
{
    int row = index.row();
    QString path = m_modelProxy_recognized->path(row);
    QImage image(path);

    if(image.isNull())
    {

        m_modelProxy_recognized->setStatus(row, ImageListModelProxy::ERROR);
        QMessageBox::warning(this, "Warning", "File invalid, will be removed from the list.");
        ServerDBInterface::removeImage(m_modelProxy_recognized->name(row));
        m_modelProxy_recognized->remove(row);
        QFile::remove(path);
    }
    else
    {
        QPixmap pixmap = QPixmap::fromImage(image);
        ui->imageWidget->load(pixmap, "");
    }

}
