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
    void imageRead(const QByteArray&);
private slots:
    void on_readyRead();
private:
    bool waitNextMessage(int); //For intermission
};

#endif // SERVERSOCKET_H
