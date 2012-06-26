#include <QtGui/QApplication>
#include "clientmainwindow.h"
#include "clientlogindialog.h"
#include "imagelistmodelproxy.h"
#include "clientsocketproxy.h"
#include <QDebug>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageListModelProxy modelProxy;
    ClientSocketProxy socket;
    ClientLoginDialog dialog(&socket);
    int code = dialog.exec();
    if(code == QDialog::Accepted)
    {
       ClientMainWindow w(&socket, &modelProxy);
       w.show();
       return a.exec();
    }
    else
    {
         return 0;
    }
}
