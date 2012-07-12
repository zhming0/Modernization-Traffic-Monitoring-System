#ifndef SERVERDBINTERFACE_H
#define SERVERDBINTERFACE_H

#include <QObject>
#include<QList>
class QStringList;
class ServerDBInterface : public QObject
{
    Q_OBJECT
public:
    explicit ServerDBInterface(QObject *parent = 0);
    static bool login(const QString& username, const QString& passwd);

    static bool addImage(const QString& name, const QString& globalPath);
    static QList<QStringList> getImageList();   //return: list<name, status, path>
    static bool setImageStatus(const QString& name, int status);
    static bool removeImage(const QString& name);
    static QString getImageResult(const QString& name);
    static void setImageResult(const QString& name, const QString& result);

    static bool updateCar(const QString& name, const int& violation, const QString& carId);
    static bool addCar(const QString& name, const int& violation, const QString& carId);
    static QStringList getCar(const QString& carid);
signals:

public slots:

};

#endif // SERVERDBINTERFACE_H
