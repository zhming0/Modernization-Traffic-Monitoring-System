#ifndef SERVERWINDOW_H
#define SERVERWINDOW_H

#include <QMainWindow>
class Server;
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
    void on_m_server_logGenarated(const QString& s);
    void on_m_server_imageRead(const QByteArray&);
private:
    void initConnection();
    Ui::ServerWindow *ui;
    Server* m_server;
    bool enable;
};

#endif // SERVERWINDOW_H
