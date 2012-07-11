#ifndef IMAGEPREVIEWDIALOG_H
#define IMAGEPREVIEWDIALOG_H

#include <QDialog>

namespace Ui {
    class ImagePreviewDialog;
}

/* A dialog which simply contains a ImageWidget */
class ImagePreviewDialog : public QDialog
{
    Q_OBJECT

public:
    /* You need to specify the image to be shown in this dialog */
    explicit ImagePreviewDialog(const QImage& image, QWidget *parent = 0);
    ~ImagePreviewDialog();

private:
    Ui::ImagePreviewDialog *ui;
};

#endif // IMAGEPREVIEWDIALOG_H
