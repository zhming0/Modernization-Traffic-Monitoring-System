#ifndef SERVERSOCKET_H
#define SERVERSOCKET_H
#include<QTcpSocket>

//! The server socket
/*!
  */
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
    /*! initialize a new ServerSocket
      @param id The id.
      */
    ServerSocket(int id);
signals:
    void imageRead(const QByteArray&);
    void logGenerated(const QString&);
private slots:
    void on_readyRead();
    void on_disconnected();
    void abortConnection();
private:
    bool waitNextMessage(int); //For intermission
    QString username;
};

#endif // SERVERSOCKET_H
