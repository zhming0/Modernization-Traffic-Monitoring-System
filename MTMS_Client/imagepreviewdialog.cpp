#include "imagepreviewdialog.h"
#include "ui_imagepreviewdialog.h"

ImagePreviewDialog::ImagePreviewDialog(const QImage& image, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ImagePreviewDialog)
{
    ui->setupUi(this);
    QPixmap pixmap = QPixmap::fromImage(image);
    ui->widget->load(pixmap, "");
}

ImagePreviewDialog::~ImagePreviewDialog()
{
    delete ui;
}
