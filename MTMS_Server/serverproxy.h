#ifndef ServerProxy_H
#define ServerProxy_H

#include <QObject>
class QTcpServer;
class QTcpSocket;
class ServerProxy : public QObject
{
    Q_OBJECT
    enum Flag{
        LOGIN,
        IMAGE,
        FAILED,
        SUCCEEDED
    };
public:
    explicit ServerProxy(QObject *parent = 0);
    void startListening(const int& port) const;
signals:

public slots:

private slots:
    void on_m_server_newConnection();
    void on_m_socket_readyRead();
private:
    void initConnection();

    QTcpServer* m_server;
    QTcpSocket* m_socket;
};

#endif // ServerProxy_H
