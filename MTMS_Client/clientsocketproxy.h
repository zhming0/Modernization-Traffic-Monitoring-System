#ifndef CLIENTSOCKETPROXY_H
#define CLIENTSOCKETPROXY_H

#include <QObject>

class QTcpSocket;
class QHostAddress;
class ImageListModelProxy;
class ClientSocketProxy : public QObject
{
    Q_OBJECT

public:
    explicit ClientSocketProxy(ImageListModelProxy* modelProxy = NULL, QObject *parent = 0);
    void send();
    void terminate();
    void setServer(QHostAddress address, quint16 port);
    const QHostAddress& hostAddress();
    quint16 port();


signals:

public slots:

private:
    QTcpSocket* m_socket;
    QHostAddress* m_hostAddress;
    quint16 m_port;
    ImageListModelProxy* m_modelProxy;
};

#endif // CLIENTSOCKETPROXY_H
