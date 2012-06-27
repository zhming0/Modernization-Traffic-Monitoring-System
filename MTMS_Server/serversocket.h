#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H
#include<QTcpSocket>
class ServerSocket : public QTcpSocket
{
    Q_OBJECT
    enum Flag{
        LOGIN,
        IMAGE,
        FAILED,
        SUCCEEDED
    };
public:
    ServerSocket(int id);
signals:
    void imageRead(QByteArray);
private slots:
    void on_readyRead();
private:

};

#endif // SERVERSOCKET_H
