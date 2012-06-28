#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>
#include <QModelIndex>

class Server;
class ImageListModelProxy;


namespace Ui {
    class ServerWindow;
}


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

};

#endif // SERVERWINDOW_H
