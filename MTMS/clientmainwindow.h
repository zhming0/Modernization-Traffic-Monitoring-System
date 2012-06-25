#ifndef CLIENTMAINWINDOW_H
#define CLIENTMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class ClientMainWindow;
}

class ClientMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ClientMainWindow(QWidget *parent = 0);
    ~ClientMainWindow();

private:
    Ui::ClientMainWindow *ui;
};

#endif // CLIENTMAINWINDOW_H
