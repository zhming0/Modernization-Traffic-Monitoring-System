#ifndef CLIENTMAINWINDOW_H
#define CLIENTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class ClientMainWindow;
}

class ImageListModelProxy;
class ClientSocketProxy;
class ClientLoginDialog;
class QApplication;

class ClientMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientMainWindow(ClientSocketProxy* socketProxy = NULL, ImageListModelProxy* modelProxy = NULL, QWidget *parent = 0);
    ~ClientMainWindow();
    void setModelProxy(ImageListModelProxy* modelProxy);
    void setSocketProxy(ClientSocketProxy* socketProxy);

private:
    void open();

    Ui::ClientMainWindow *ui;
    ImageListModelProxy* m_modelProxy;
    ClientSocketProxy* m_socketProxy;
    ClientLoginDialog* m_loginDialog;
    int total_sendData;


private slots:
    void on_action_Open_triggered();
    void on_action_Exit_triggered();
    void on_action_About_triggered();
    void on_pushButton_open_clicked();
    void on_pushButton_remove_clicked();
    void on_pushButton_send_clicked();
    void on_pushButton_terminate_clicked();
    void on_pushButton_clear_clicked();
    void on_pushButton_preview_clicked();
    void on_pushButton_check_clicked();
    void on_pushButton_checkAll_clicked();
    void on_pushButton_uncheck_clicked();
    void on_pushButton_uncheckAll_clicked();
    void on_m_socketProxy_bytesWritten(int);
};

#endif // CLIENTMAINWINDOW_H
