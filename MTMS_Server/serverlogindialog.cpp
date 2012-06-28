#include "serverlogindialog.h"
#include "ui_serverlogindialog.h"
#include"serverdbinterface.h"
#include<QMessageBox>
#include<QCryptographicHash>
ServerLoginDialog::ServerLoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerLoginDialog)
{
    ui->setupUi(this);
}

ServerLoginDialog::~ServerLoginDialog()
{
    delete ui;
}

void ServerLoginDialog::on_loginButton_clicked()
{
    if (ServerDBInterface::login(ui->userNameEdit->text(), QString(QCryptographicHash::hash(ui->userNameEdit->text().toAscii(),QCryptographicHash::Md5).toHex())))
        done(QDialog::Accepted);
    else
        QMessageBox::warning(this, "Warning", " Login failed!");
}
