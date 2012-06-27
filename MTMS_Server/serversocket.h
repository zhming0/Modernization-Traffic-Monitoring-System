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
        SUCCEEDED,
        PROGRESS
    };
public:
    ServerSocket(int id);
signals:
    void imageRead(const QByteArray&);
    void logGenerated(const QString&);
private slots:
    void on_readyRead();
    void on_disconnected();
private:
    bool waitNextMessage(int); //For intermission
    QString username;
};

#endif // SERVERSOCKET_H
