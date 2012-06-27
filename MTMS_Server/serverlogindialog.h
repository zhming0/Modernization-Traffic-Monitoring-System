#ifndef SERVERLOGINDIALOG_H
#define SERVERLOGINDIALOG_H

#include <QDialog>

namespace Ui {
    class ServerLoginDialog;
}

class ServerLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerLoginDialog(QWidget *parent = 0);
    ~ServerLoginDialog();
private slots:
    void on_loginButton_clicked();
private:
    Ui::ServerLoginDialog *ui;
};

#endif // SERVERLOGINDIALOG_H
