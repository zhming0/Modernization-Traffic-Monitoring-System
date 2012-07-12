#ifndef SERVERDBINTERFACE_H
#define SERVERDBINTERFACE_H

#include <QObject>
#include<QList>
class QStringList;

//! The Database interface for server
/*!
 */
class ServerDBInterface : public QObject
{
    Q_OBJECT
public:
    explicit ServerDBInterface(QObject *parent = 0);
    /*! Login
      @param username The username
      @param password The password
      */
    static bool login(const QString& username, const QString& passwd);

    /*! Add an image record
      @param name the filename of the image
      @param globalPath the path of the image
      */
    static bool addImage(const QString& name, const QString& globalPath);
    /*!
      @return list<name, status, path>
      */
    static QList<QStringList> getImageList();
    /*!
      @param name the file name of the image
      @param status the status to be set
      */
    static bool setImageStatus(const QString& name, int status);
    /*!
      Remove an image record
      @param name The file name
      */
    static bool removeImage(const QString& name);

    /*!
      Update a record of a car
      */
    static bool updateCar(const QString& name, const int& violation, const QString& carId);
    /*!
      Add a record of car
      */
    static bool addCar(const QString& name, const int& violation, const QString& carId);
    /*!
     @return get the car information
     */
    static QStringList getCar(const QString& carid);
signals:

public slots:

};

#endif // SERVERDBINTERFACE_H
