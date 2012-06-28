#include "recognizedialog.h"
#include "ui_recognizedialog.h"

RecognizeDialog::RecognizeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecognizeDialog)
{
    ui->setupUi(this);
}

RecognizeDialog::~RecognizeDialog()
{
    delete ui;
}
