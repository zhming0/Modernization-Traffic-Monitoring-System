#ifndef IMAGEPREVIEWDIALOG_H
#define IMAGEPREVIEWDIALOG_H

#include <QDialog>

namespace Ui {
    class ImagePreviewDialog;
}

//! A dialog simply containing a ImageWidget
/*!
  You need to specify a constant referece to a QImage while constructing it.
  On the opening, it will be displaying such image.
  */
class ImagePreviewDialog : public QDialog
{
    Q_OBJECT

public:
    /*!
      You need to specify the image to be shown in this dialog at the constructing.
     */
    explicit ImagePreviewDialog(const QImage& image, QWidget *parent = 0);
    ~ImagePreviewDialog();

private:
    Ui::ImagePreviewDialog *ui;
};

#endif // IMAGEPREVIEWDIALOG_H
