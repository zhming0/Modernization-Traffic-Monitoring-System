#include "imagepreviewdialog.h"
#include "ui_imagepreviewdialog.h"

ImagePreviewDialog::ImagePreviewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImagePreviewDialog)
{
    ui->setupUi(this);
}

ImagePreviewDialog::~ImagePreviewDialog()
{
    delete ui;
}
