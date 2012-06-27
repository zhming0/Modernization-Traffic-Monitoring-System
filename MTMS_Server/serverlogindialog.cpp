#include "serverlogindialog.h"
#include "ui_serverlogindialog.h"
#include"serverdbinterface.h"
#include<QMessageBox>
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
    if (ServerDBInterface::login(ui->userNameEdit->text(), ui->userNameEdit->text()))
        done(QDialog::Accepted);
    else
        QMessageBox::warning(this, "You idiot", " Login failed, check your username and passwd darling~");
}
