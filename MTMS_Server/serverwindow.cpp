#include "serverwindow.h"
#include "ui_serverwindow.h"
#include "server.h"
#include "imagelistmodelproxy.h"
#include<QDebug>
#include<QDateTime>
#include"serverdbinterface.h"
#include<QDir>
#include<QFile>
#include"imagelistitem.h"
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
    qDebug() << "update";
}

void ServerWindow::on_pushButton_processAll_clicked()
{
    qDebug() << "process all";
}

void ServerWindow::on_pushButton_clearAllProcessed_clicked()
{
    qDebug() << "clear all";
}

void ServerWindow::on_pushButton_recognize_clicked()
{
    qDebug() << "recognize";
}




