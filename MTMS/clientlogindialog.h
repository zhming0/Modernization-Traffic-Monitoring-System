#ifndef CLIENTLOGINDIALOG_H
#define CLIENTLOGINDIALOG_H

#include <QDialog>

namespace Ui {
    class ClientLoginDialog;
}

class QTcpSocket;

class ClientLoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ClientLoginDialog(QWidget *parent = 0);
    ~ClientLoginDialog();

private:
    Ui::ClientLoginDialog *ui;
    QTcpSocket* m_socket;

};

#endif // CLIENTLOGINDIALOG_H
