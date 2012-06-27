#include "clientsocketproxy.h"

#include <QTcpSocket>
#include <QHostAddress>
#include <QDebug>
#include<QImage>
#include<QBuffer>

ClientSocketProxy::ClientSocketProxy(ImageListModelProxy* modelProxy, QObject *parent) :
    QObject(parent)
{
    m_socket = new QTcpSocket(this);
    m_stream = new QDataStream(m_socket);
    m_hostAddress = new QHostAddress("127.0.0.1");
    m_port = 4000;

    m_modelProxy = modelProxy;

    initConnection();
}

void ClientSocketProxy::login(QString username, QString password)
{
    qDebug() << "Login start..\n";
    m_username = username, m_passwd = password;
    m_socket->connectToHost(*m_hostAddress, m_port);
}

void ClientSocketProxy::initConnection()
{
    connect(m_socket, SIGNAL(connected()),
            this, SLOT(on_m_socket_connected()));
    connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(on_m_socket_error()));
    connect(m_socket, SIGNAL(readyRead()),
            this, SLOT(on_m_socket_readyRead()));
}

void ClientSocketProxy::sendData(QString data)
{
    (*m_stream) << data;
    m_socket->flush();
}

void ClientSocketProxy::sendData(int flag)
{
    (*m_stream) << flag;
    m_socket -> flush();
}

void ClientSocketProxy::sendData(const QImage& data)
{
    QByteArray bytes;
    QBuffer buf(&bytes);
    buf.open(QIODevice::WriteOnly);
    data.save(&buf);
    (*m_stream) << IMAGE;
    (*m_stream) << bytes;
}

bool ClientSocketProxy::on_m_socket_connected()
{
    sendData(LOGIN);
    sendData(m_username);
    sendData(m_passwd);
}
void ClientSocketProxy::on_m_socket_readyRead()
{
    qDebug() << "Reading something";
    int flag;
    (*m_stream) >> flag;
    if (flag == SUCCEEDED)
    {
        emit login_succeeded();
    }
    if (flag == FAILED)
    {
        emit login_failed();
    }
}
void ClientSocketProxy::terminate()
{
    m_socket->abort();
    login(m_username, m_passwd);
}

void ClientSocketProxy::on_m_socket_error()
{
    qDebug() << "Connection error\n";
    emit timeout();
}

void ClientSocketProxy::setServer(QHostAddress address, quint16 port)
{
    if(this->m_hostAddress != NULL)
    {
        delete m_hostAddress;
    }
    m_hostAddress = new QHostAddress(address);

    m_port = port;
}

const QHostAddress& ClientSocketProxy::hostAddress()
{
    return *m_hostAddress;
}

quint16 ClientSocketProxy::port()
{
    return m_port;
}
