#include "clientlogindialog.h"
#include "ui_clientlogindialog.h"

ClientLoginDialog::ClientLoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ClientLoginDialog)
{
    ui->setupUi(this);
}

ClientLoginDialog::~ClientLoginDialog()
{
    delete ui;
}
