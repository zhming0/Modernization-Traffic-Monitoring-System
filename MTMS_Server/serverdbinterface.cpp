#include "serverdbinterface.h"
#include<QTSQL>
ServerDBInterface::ServerDBInterface(QObject *parent) :
    QObject(parent)
{
}

bool ServerDBInterface::login(const QString& username, const QString& passwd)
{
    QSqlQuery query;
    if (query.exec(QString("SELECT passwd FROM admin WHERE username '%1'").arg(username)))
    {
        query.next();
        if (query.value(0).toString() == passwd)
            return true;
    }
    return false;
}
