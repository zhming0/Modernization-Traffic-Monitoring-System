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

//! The client main window
/*!

  */
class ClientMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*!
      Keeps a socketProxy to communicate with the server, an ImageListModelProxy to manage the image list
      @param socketProxy The reference of socket proxy kept inside
      @param modelProxy The reference of model proxy kept inside
      */
    explicit ClientMainWindow(ClientSocketProxy* socketProxy = NULL, ImageListModelProxy* modelProxy = NULL, QWidget *parent = 0);
    ~ClientMainWindow();

    /*!
      Keeps a reference of the modelProxy
      @param modelProxy The reference of model proxy kept inside
      */
    void setModelProxy(ImageListModelProxy* modelProxy);

    /*!
      Keeps a reference of the socketProxy
      @param socketProxy The reference of socket proxy kept inside
      */
    void setSocketProxy(ClientSocketProxy* socketProxy);

private:
    /*! Opens image files*/
    void open();

    /*! UI */
    Ui::ClientMainWindow *ui;

    /*! Login Dialog */
    ClientLoginDialog* m_loginDialog;

    /*! The reference of model proxy kept inside */
    ImageListModelProxy* m_modelProxy;

    /*! The reference of socket proxy kept inside */
    ClientSocketProxy* m_socketProxy;


    /*! The data used to compute the percentage of databytes being sent */
    qint64 total_sendData;

    /*! The data used to compute the percentage of databytes being sent */
    qint64 writtenBytes;


    /* These variables following are used to indicate the connection state */
    /*! Used to store a red light picture */
    QString c_redLightPath;
    /*! Used to store a green light picture */
    QString c_greenLightPath;
    /*! Used to make red light flash while connecting */
    QTimer* m_connecting_timer;


    /*! The timer used to reconnect */
    QTimer* m_timer;


private slots:
    /*! Called when open file needed */
    void on_action_Open_triggered();

    /*! Called to exit */
    void on_action_Exit_triggered();

    /*! Called to see the about */
    void on_action_About_triggered();

    /*! Called when open file needed */
    void on_pushButton_open_clicked();

    /*! Called to remove selected items */
    void on_pushButton_remove_clicked();

    /*! Called to send the checked items */
    void on_pushButton_send_clicked();

    /*! Called to terminate the connection */
    void on_pushButton_terminate_clicked();

    /*! Called to clear all the items in the item list */
    void on_pushButton_clear_clicked();

    /*! Called to preview the selected image */
    void on_pushButton_preview_clicked();

    /*! Called to check the item(s) selected */
    void on_pushButton_check_clicked();

    /*! Called to check all the items inside the list */
    void on_pushButton_checkAll_clicked();

    /*! Called to uncheck the selcted item(s) */
    void on_pushButton_uncheck_clicked();

    /*! Called to uncheck all the items inside the list */
    void on_pushButton_uncheckAll_clicked();

    /*! Called to update the progress bar */
    void on_m_socketProxy_bytesWritten(qint64);

    /*! Called when connecting, which makes red light flash */
    void on_connecting();

    /*! Called when connection established, which makes light green */
    void on_connected();

    /*! Called when connection is closed, which makes light red */
    void on_disconnected();

    /*! Called every time the timer timeout to try to reconnect */
    void on_m_connecting_timer_timeout();
};

#endif // CLIENTMAINWINDOW_H
