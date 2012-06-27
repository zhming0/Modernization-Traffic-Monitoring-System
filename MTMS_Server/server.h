#ifndef Server_H
#define Server_H

#include <QObject>
#include<QTcpServer>
class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    void startListening(const int& port);
signals:
    void imageRead(const QByteArray&);
public slots:
    void on_socket_imageRead(const QByteArray&);
private:
    void incomingConnection(int socketId);
};

#endif // Server_H
