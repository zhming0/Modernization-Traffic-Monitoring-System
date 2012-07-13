#ifndef Server_H
#define Server_H


#include<QTcpServer>

//! Inherits from QTcpServer, used to communicate with clients
/*!
  */
class Server : public QTcpServer
{
    Q_OBJECT
public:
    /*! Constructor */
    explicit Server(QObject *parent = 0);
    /*! Start listen to some specific port @param port The port to listen*/
    void startListening(const int& port);
    /*! Stop listening */
    void stopListening();
signals:
    /*! Emited when image being read */
    void imageRead(const QByteArray&);
    /*! Emited to write to log @param log The log string.*/
    void logGenerated(const QString& log);
    /*! Emited when server teminated.*/
    void serverTerminated();
public slots:
    /*! Called when image being read */
    void on_socket_imageRead(const QByteArray&);
    /*! Called to write to log @param log The log string.*/
    void on_socket_logGenerated(const QString &);
private:
    void incomingConnection(int socketId);


};

#endif // Server_H
