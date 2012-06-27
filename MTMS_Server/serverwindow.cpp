#include "serverwindow.h"
#include "ui_serverwindow.h"
#include "server.h"
#include<QDebug>
#include<QDateTime>
ServerWindow::ServerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerWindow)
{
    ui->setupUi(this);
    m_server = new Server(this);
    enable = false;

    initConnection();
}
ServerWindow::~ServerWindow()
{
    delete ui;
}

void ServerWindow::initConnection()
{
    connect(m_server, SIGNAL(logGenarated(QString)),
            this, SLOT(on_m_server_logGenarated(QString)));
    connect(m_server, SIGNAL(imageRead(QByteArray)),
            this, SLOT(on_m_server_imageRead(QByteArray)));
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

void ServerWindow::on_m_server_logGenarated(const QString& s)
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
    //pixelmap->save("images/".QDateTime::currentDataTime().toString);
}
