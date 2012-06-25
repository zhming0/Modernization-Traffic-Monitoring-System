#include <QtGui/QApplication>
#include "clientmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClientMainWindow w;
    w.show();

    return a.exec();
}
