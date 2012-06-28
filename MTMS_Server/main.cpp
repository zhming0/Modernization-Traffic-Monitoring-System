#include <QtGui/QApplication>
#include "serverwindow.h"
#include<QMessageBox>
#include<QtSql>
#include"serverlogindialog.h"
#include<QDir>
bool createConnection()
{
        QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName("MTMSDB.sqlite");
        if (!db.open()) {
                QMessageBox::critical(0,QObject::tr("Database Error"),
                              db.lastError().text());
                return false;
        }
        return true;
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QLocale::setDefault(QLocale(QLocale::English, QLocale::AnyCountry));
    if (!createConnection())
        return -1;
    ServerLoginDialog login;
    if (login.exec() == QDialog::Accepted)
    {
        ServerWindow w;
        w.show();
        return a.exec();
    }else
        return -1;
}
