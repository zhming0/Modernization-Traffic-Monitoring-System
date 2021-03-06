#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

class Server;
class ImageListModelProxy;


namespace Ui {
    class ServerWindow;
}

//! The server window
/*!
  */
class ServerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerWindow(QWidget *parent = 0);
    ~ServerWindow();

private slots:
    void on_serverEnableButton_clicked();
    void on_m_server_logGenerated(const QString& s);
    void on_m_server_imageRead(const QByteArray&);
    void on_pushButton_update_clicked();
    void on_pushButton_processAll_clicked();
    void on_pushButton_clearAllProcessed_clicked();
    void on_pushButton_recognize_clicked();
    void on_tableView_unrecognized_pressed(QModelIndex index);
    void on_tableView_recognized_pressed(QModelIndex index);
    void on_recognized_currentRowChanged(QModelIndex current, QModelIndex previous);
    void on_unrecognized_currentRowChanged(QModelIndex current, QModelIndex previous);

    void on_pushButton_unrecognized_delete_clicked();
    void on_pushButton_unrecognized_check_clicked();
    void on_pushButton_unrecognized_checkAll_clicked();
    void on_pushButton_unrecognized_uncheck_clicked();
    void on_pushButton_unrecognized_uncheckAll_clicked();
    void on_pushButton_recognized_delete_clicked();
    void on_pushButton_recognized_check_clicked();
    void on_pushButton_recognized_checkAll_clicked();
    void on_pushButton_recognized_uncheck_clicked();
    void on_pushButton_recognized_uncheckAll_clicked();
    void on_action_about_triggered();

private:
    void initConnection();
    void initTableViews();
    void loadImageList();

    Ui::ServerWindow *ui;
    Server* m_server;
    bool enable;
    ImageListModelProxy* m_modelProxy_recognized;
    ImageListModelProxy* m_modelProxy_unrecognized;

    QString imagePath;

    QVector<QString> recognizedPlate;
};

#endif // SERVERWINDOW_H
