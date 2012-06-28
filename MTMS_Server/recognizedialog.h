#ifndef RECOGNIZEDIALOG_H
#define RECOGNIZEDIALOG_H

#include <QDialog>

namespace Ui {
    class RecognizeDialog;
}

class RecognizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecognizeDialog(QWidget *parent = 0);
    ~RecognizeDialog();

private:
    Ui::RecognizeDialog *ui;
};

#endif // RECOGNIZEDIALOG_H
