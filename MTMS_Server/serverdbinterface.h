#ifndef SERVERDBINTERFACE_H
#define SERVERDBINTERFACE_H

#include <QObject>

class ServerDBInterface : public QObject
{
    Q_OBJECT
public:
    explicit ServerDBInterface(QObject *parent = 0);
    static bool login(const QString& username, const QString& passwd);
signals:

public slots:

};

#endif // SERVERDBINTERFACE_H
