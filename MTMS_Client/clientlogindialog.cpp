#include "clientlogindialog.h"
#include "ui_clientlogindialog.h"

#include "clientsocketproxy.h"

#include <QDebug>
#include <QRegExpValidator>
#include <QRegExp>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>

ClientLoginDialog::ClientLoginDialog(ClientSocketProxy* socketProxy, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientLoginDialog)
{
    ui->setupUi(this);

    ui->widget_configuration->setVisible(false);

    QString Octet = "(?:[0-1]?[0-9]?[0-9]|2[0-4][0-9]|25[0-5])";
    ui->lineEdit_host->setValidator(new QRegExpValidator(
             QRegExp("^" + Octet + "\\." + Octet + "\\." + Octet + "\\." + Octet + "$"), this));

    adjustSize();

    m_socketProxy = socketProxy;
}

ClientLoginDialog::~ClientLoginDialog()
{
    delete ui;
}

void ClientLoginDialog::on_pushButton_more_clicked(bool checked)
{
    ui->widget_configuration->setShown(checked);
    this->adjustSize();
}

void ClientLoginDialog::on_pushButton_login_clicked()
{
    if(m_socketProxy == NULL)
    {
        QMessageBox::warning(this, "Warning", "Internal Error#m_imageSender is NULL.");
        return;
    }
    m_socketProxy->login(ui->lineEdit_account->text(), ui->lineEdit_password->text());
}

void ClientLoginDialog::on_pushButton_apply_clicked()
{
    QString addressStr = ui->lineEdit_host->text();
    quint16 port = ui->spinBox_port->value();

    bool addressValid = validateAddress(addressStr);
    if(!addressValid)
    {
        QMessageBox::warning(this, "Warning",
                             "Host address is not valid!");
        return;
    }
    QHostAddress host(addressStr);

    if(m_socketProxy != NULL)
    {
        m_socketProxy->setServer(host, port);
    }
    else
    {
        QMessageBox::warning(this, "Warning", "Internal Error#m_imageSender is NULL.");
        return;
    }

    QMessageBox::information(this, "Information",
                             "Configuration has been applied successfully!");
}


bool ClientLoginDialog::validateAddress(QString address)
{
    QStringList slist = address.split(".");
    if(slist.length() != 4)
    {
        return false;
    }
    foreach(QString str, slist)
    {
        if(str.isEmpty())
        {
            return false;
        }
    }

    return true;
}
