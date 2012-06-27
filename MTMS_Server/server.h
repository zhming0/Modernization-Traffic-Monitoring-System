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
public slots:

private:
    void incomingConnection(int socketId);
};

#endif // Server_H
