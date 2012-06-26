#include "clientsocketproxy.h"

#include <QTcpSocket>
#include <QHostAddress>

ClientSocketProxy::ClientSocketProxy(ImageListModelProxy* modelProxy, QObject *parent) :
    QObject(parent)
{
    m_socket = new QTcpSocket(this);
    m_hostAddress = new QHostAddress("127.0.0.1");
    m_port = 4000;

    m_modelProxy = modelProxy;
}

void ClientSocketProxy::send()
{

}

void ClientSocketProxy::terminate()
{

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
