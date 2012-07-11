#ifndef CLIENTLOGINDIALOG_H
#define CLIENTLOGINDIALOG_H

#include <QDialog>

namespace Ui {
    class ClientLoginDialog;
}

class QTcpSocket;
class ClientSocketProxy;

/* The login dialog which is shown before the MainWindow launches. */
class ClientLoginDialog : public QDialog
{
    Q_OBJECT

public:
    /* Constructor keeps a reference of socketProxy for network connections. */
    explicit ClientLoginDialog(ClientSocketProxy* socketProxy = NULL, QWidget *parent = 0);

    /* Destructor */
    ~ClientLoginDialog();

private:
    /* Validates if an address is a valid ipv4 address. */
    bool validateAddress(QString address);

    /* The reference of socketProxy kept inside. */
    ClientSocketProxy* m_socketProxy;

    /* UI */
    Ui::ClientLoginDialog *ui;


private slots:

    /* Shows or hides the extension area of dialog according to the check state of the button 'more'
     * Shows when checked is true; Hides when checked is false.
     */
    void on_pushButton_more_clicked(bool checked);

    /* Try to connect to the server, validate the username and password,
     * If succeeded hides the dialog, and shows the MainWindow.
     */
    void on_pushButton_login_clicked();

    /* Validates the ipv4 and port number first, if correct, apply to the socketProxy, else
     *  shows warnings.
     */
    void on_pushButton_apply_clicked();

    /* If succeeded in logining, this slot will be called. */
    void on_m_socketProxy_login_succeeded();

    /* If failed in logining, this slot will be called. */
    void on_m_socketProxy_login_failed();

    /* If timeout in connecting to the server, this slot will be called */
    void on_m_socketProxy_timeout();

    /* Be called at the death of the dialog, disconnect connections to end up with its events loop. */
    void on_finished(int code);

};

#endif // CLIENTLOGINDIALOG_H
