#ifndef CLIENTMAINWINDOW_H
#define CLIENTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class ClientMainWindow;
}

class ImageListModelProxy;
class ClientSocketProxy;


class ClientMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientMainWindow(ClientSocketProxy* socketProxy = NULL, ImageListModelProxy* modelProxy = NULL, QWidget *parent = 0);
    ~ClientMainWindow();
    void setModelProxy(ImageListModelProxy* modelProxy);
    void setSocketProxy(ClientSocketProxy* socketProxy);


private:
    Ui::ClientMainWindow *ui;
    ImageListModelProxy* m_modelProxy;
    ClientSocketProxy* m_socketProxy;

};

#endif // CLIENTMAINWINDOW_H
