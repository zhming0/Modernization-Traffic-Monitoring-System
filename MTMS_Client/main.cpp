#include <QtGui/QApplication>
#include "clientmainwindow.h"
#include "clientlogindialog.h"
#include "imagelistmodelproxy.h"
#include "clientsocketproxy.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageListModelProxy modelProxy;
    ClientSocketProxy socket;
    ClientMainWindow w(&socket, &modelProxy);
    return a.exec();
}
