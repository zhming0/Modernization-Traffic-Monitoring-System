#ifndef IMAGEPREVIEWDIALOG_H
#define IMAGEPREVIEWDIALOG_H

#include <QDialog>

namespace Ui {
    class ImagePreviewDialog;
}

class ImagePreviewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ImagePreviewDialog(const QImage& image, QWidget *parent = 0);
    ~ImagePreviewDialog();

private:
    Ui::ImagePreviewDialog *ui;
};

#endif // IMAGEPREVIEWDIALOG_H
