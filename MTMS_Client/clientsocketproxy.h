#ifndef CLIENTSOCKETPROXY_H
#define CLIENTSOCKETPROXY_H

#include <QObject>

class QTcpSocket;
class QHostAddress;
class ImageListModelProxy;
class QImage;
class ClientSocketProxy : public QObject
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
    explicit ClientSocketProxy(ImageListModelProxy* modelProxy = NULL, QObject *parent = 0);
    void terminate();
    void setServer(QHostAddress address, quint16 port);
    const QHostAddress& hostAddress();
    quint16 port();
    void login(QString username, QString password);
    void sendImage(const QImage& image, QString format);
signals:
    void login_succeeded();
    void login_failed();
    void timeout();
public slots:
    bool on_m_socket_connected();
private slots:
    void on_m_socket_error();
    void on_m_socket_readyRead();
private:
    void sendData(QString data);
    void sendData(const QImage& data, QString format);
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
