#ifndef IMAGESENDER_H
#define IMAGESENDER_H

#include <QObject>

class QTcpSocket;
class QHostAddress;

class ImageSender : public QObject
{
    Q_OBJECT
public:
    explicit ImageSender(QObject *parent = 0);
    void send();
    void terminate();
    void setHostAddress(QHostAddress address);
    const QHostAddress& hostAddress();


signals:

public slots:

private:
    QTcpSocket* m_socket;
    QHostAddress* hostAddress;

};

#endif // IMAGESENDER_H
