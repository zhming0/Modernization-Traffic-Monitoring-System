#include "serverdbinterface.h"
#include <QDebug>
#include<QTSQL>
#include<QStringList>
#include<QList>
ServerDBInterface::ServerDBInterface(QObject *parent) :
    QObject(parent)
{
}

bool ServerDBInterface::login(const QString& username, const QString& passwd)
{
    QSqlQuery query;
    if (query.exec(QString("SELECT password FROM admin WHERE username = '%1'").arg(username)))
    {
        query.next();
        //qDebug() << query.value(0).toString() << "|" << passwd;
        if (query.value(0).toString() == passwd)
            return true;
    } else {
        qDebug() << query.lastError();
    }
    return false;
}

bool ServerDBInterface::addImage(const QString& name, const QString& globalPath)
{
    QSqlQuery query;
    if (query.exec(QString("INSERT INTO images VALUES('%1', 0, '%2')").arg(name).arg(globalPath)))
        return true;
    qDebug() << query.lastError();
    return false;
}

const QList<QStringList>& ServerDBInterface::getImageList()
{
    QList<QStringList> ret;
    QSqlQuery query;
    if (query.exec(QString("SELECT * FROM images")))
    {
        while (query.next())
        {
            QStringList list;
            list << query.value(0).toString() << query.value(1).toString() << query.value(2).toString();
            ret.append(list);
        }
    } else
        qDebug() << query.lastError();
    return ret;
}

bool ServerDBInterface::setImageStatus(const QString& name, int status)
{
    QSqlQuery query;
    if (query.exec(QString("UPDATE images SET status = %1 WHERE name = '%2'").arg(status).arg(name)))
    {
        return true;
    }
    qDebug() << query.lastError();
    return false;
}

bool ServerDBInterface::removeImage(const QString &name)
{
    QSqlQuery query;
    if (query.exec(QString("DELETE FROM images WHERE name = '%1'").arg(name)))
        return true;
    qDebug() << query.lastError();
    return false;
}

bool ServerDBInterface::updateCar(const QString& owner, const int& violation, const QString& carId)
{
    QSqlQuery query;
    if (query.exec(QString("UPDATE car SET owner = '%1' , violation = %2 , carid = '%3' WHERE carId = '%3'").arg(owner).arg(violation).arg(carId)))
        return true;
    qDebug() << query.lastError();
    return false;
}

bool ServerDBInterface::addCar(const QString& owner, const int& violation, const QString& carId)
{
    QSqlQuery query;
    if (query.exec(QString("INSERT INT car VALUES('%3' , '%1' , %2)").arg(owner).arg(violation).arg(carId)))
        return true;
    qDebug() << query.lastError();
    return false;
}

QStringList ServerDBInterface::getCar(const QString &carid)
{
    QStringList list;
    QSqlQuery query;
    if (query.exec(QString("SELECT * FROM car WHERE carid = '%1'").arg(carid)))
    {
        query.next();
        list << query.value(0).toString() << query.value(1).toString() << query.value(2).toString();
    }else
        qDebug() << query.lastError();
    return list;
}
