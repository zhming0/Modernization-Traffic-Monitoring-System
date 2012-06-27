#ifndef CLIENTLOGINDIALOG_H
#define CLIENTLOGINDIALOG_H

#include <QDialog>

namespace Ui {
    class ClientLoginDialog;
}

class QTcpSocket;
class ClientSocketProxy;

class ClientLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClientLoginDialog(ClientSocketProxy* socketProxy = NULL, QWidget *parent = 0);
    ~ClientLoginDialog();

private:
    bool validateAddress(QString address);
    Ui::ClientLoginDialog *ui;
    ClientSocketProxy* m_socketProxy;


private slots:
    void on_pushButton_more_clicked(bool checked);
    void on_pushButton_login_clicked();
    void on_pushButton_apply_clicked();
    void on_m_socketProxy_login_succeeded();
    void on_m_socketProxy_login_failed();
    void on_m_socketProxy_timeout();

};

#endif // CLIENTLOGINDIALOG_H
