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
    m_socket->connectToHost(*m_hostAddress, m_port);
    qDebug() << "Login start..\n";
    m_username = username, m_passwd = password;
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
//    QString s;
//    s.setNum(flag);
//    this->sendData(s);
    (*m_stream) << flag;
    m_socket -> flush();
}

void ClientSocketProxy::sendData(const QImage& data)
{
    QByteArray bytes;
    QBuffer buf(&bytes);
    buf.open(QIODevice::WriteOnly);
    data.save(&buf);
    m_socket->write(bytes);
    m_socket->flush();
}

bool ClientSocketProxy::on_m_socket_connected()
{
    sendData(USERNAME);
    sendData(m_username);
    //m_socket->flush();

    sendData(PASSWORD);
    sendData(m_passwd);
    //m_socket->flush();
}
void ClientSocketProxy::on_m_socket_readyRead()
{
    qDebug() << "Reading something";
}
void ClientSocketProxy::terminate()
{
    m_socket->abort();
    login(m_username, m_passwd);
}

void ClientSocketProxy::on_m_socket_error()
{
    qDebug() << "Connection error\n";
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
