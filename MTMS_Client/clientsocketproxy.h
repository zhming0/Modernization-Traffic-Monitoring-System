#ifndef CLIENTSOCKETPROXY_H
#define CLIENTSOCKETPROXY_H

#include <QObject>

class QTcpSocket;
class QHostAddress;
class QImage;
class ImageListModelProxy;

/* A Proxy to Client Socket, which helps the client easily realize communication with server */
class ClientSocketProxy : public QObject
{
    Q_OBJECT

    /* Communication flags */
    enum Flag{
        LOGIN,
        IMAGE,
        FAILED,
        SUCCEEDED,
        PROGRESS
    };
public:
    /* Keeps a referece of ImageListModelProxy to know what needs to be sent */
    explicit ClientSocketProxy(ImageListModelProxy* modelProxy = NULL, QObject *parent = 0);

    /* Terminates the connection */
    void terminate();

    /* Sets server with an address and a port number */
    void setServer(QHostAddress address, quint16 port);

    /* Returns the hostAddress */
    const QHostAddress& hostAddress();

    /* Returns the port number */
    quint16 port();

    /* Logins, username and password needed of course */
    void login(QString username, QString password);

    /* Send a image to the server */
    void sendImage(const QImage& image);

    /* returns the remaining bytes to write */
    int bytesToWrite();

signals:
    /* emits when login succeeded */
    void login_succeeded();
    /* emits when login failed */
    void login_failed();
    /* emits when timeout */
    void timeout();
    /* emits to indicate the bytes that has written */
    void bytesWritten(qint64);

public slots:
    /* Called when connection established, sending the username and password to the
     * server,
     * Called also, when after terminated and reconnection needed.
     */
    bool on_m_socket_connected();


private slots:
    void on_m_socket_error();
    void on_m_socket_bytesWritten(qint64);
    void on_m_socket_readyRead();
    void reconnect();

private:
    void sendData(QString data);
    void sendData(const QImage& data);
    void sendData(int flag);
    void initConnection();

    QTcpSocket* m_socket;
    QHostAddress* m_hostAddress;
    quint16 m_port;
    ImageListModelProxy* m_modelProxy;
    QString m_username, m_passwd;
    QDataStream* m_stream;
};

#endif // CLIENTSOCKETPROXY_H
