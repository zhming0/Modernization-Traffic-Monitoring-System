#ifndef CLIENTSOCKETPROXY_H
#define CLIENTSOCKETPROXY_H

#include <QObject>

class QTcpSocket;
class QHostAddress;
class QImage;
class ImageListModelProxy;

//! A proxy to client socket, which helps the client easily realize communication with server
/*!
  */
class ClientSocketProxy : public QObject
{
    Q_OBJECT

    /*! Communication flags */
    enum Flag{
        LOGIN,
        IMAGE,
        FAILED,
        SUCCEEDED,
        PROGRESS
    };
public:
    /*! Keeps a referece of ImageListModelProxy to know what needs to be sent
      @param modelProxy The model proxy kept inside.
      */
    explicit ClientSocketProxy(ImageListModelProxy* modelProxy = NULL, QObject *parent = 0);

    /*! Terminates the connection */
    void terminate();

    /*! Sets server with an address and a port number
      @param address The ipv4 server address
      @param port The port number
      */
    void setServer(QHostAddress address, quint16 port);

    /*! @return Returns the hostAddress */
    const QHostAddress& hostAddress();

    /*! @return Returns the port number */
    quint16 port();

    /*! Logins
      @param username The username
      @param password The password
      */
    void login(QString username, QString password);

    /*! Send a image to the server
      @param image The image being sent
      */
    void sendImage(const QImage& image);

    /*! returns the remaining bytes to write */
    int bytesToWrite();

signals:
    /*! emits when login succeeded */
    void login_succeeded();
    /*! emits when login failed */
    void login_failed();
    /*! emits when timeout */
    void timeout();
    /*! emits to indicate the bytes that has written
      @param the byte that has written
      */
    void bytesWritten(qint64);

public slots:
    /*! Called when connection established, sending the username and password to the
      server,
      Called also, when after terminated and reconnection needed.
      */
    void on_m_socket_connected();


private slots:
    /*! Called when connection is error */
    void on_m_socket_error();

    /*! Called to update progress information
      @param bytes the bytes written.
      */
    void on_m_socket_bytesWritten(qint64 bytes);
    /*! Called when connection established */
    void on_m_socket_readyRead();

    /*! Reconnect to the server */
    void reconnect();

private:
    /*! Send data */
    void sendData(QString data);
    /*! Send data */
    void sendData(const QImage& data);
    /*! Send data */
    void sendData(int flag);
    /*! initialize connections */
    void initConnection();

    /*! The socket kept inside */
    QTcpSocket* m_socket;
    /*! Current host address */
    QHostAddress* m_hostAddress;
    /*! Current port number */
    quint16 m_port;
    /*! Model proxy kept inside */
    ImageListModelProxy* m_modelProxy;
    /*! User Name */
    QString m_username;
    /*! Password */
    QString m_passwd;
    /*! The data stream */
    QDataStream* m_stream;
};

#endif // CLIENTSOCKETPROXY_H
