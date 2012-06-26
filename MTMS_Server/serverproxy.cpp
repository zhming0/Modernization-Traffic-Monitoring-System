#include "serverproxy.h"
#include<QTcpServer>
#include<QTcpSocket>
#include<qDebug>
#include"serverdbinterface.h"
ServerProxy::ServerProxy(QObject *parent) :
    QObject(parent)
{
    m_server = new QTcpServer(this);
    initConnection();
}

void ServerProxy::startListening(const int &port) const
{
    qDebug() << "Server started\n";
    m_server->listen(QHostAddress::Any, port);
}

void ServerProxy::initConnection()
{
    connect(m_server, SIGNAL(newConnection()),
            this, SLOT(on_m_server_newConnection()));
}

void ServerProxy::on_m_server_newConnection()
{
    m_socket = m_server->nextPendingConnection();
    connect(m_socket, SIGNAL(readyRead()),
            this, SLOT(on_m_socket_readyRead()));
    qDebug() << "Incoming new connection\n";
}

void ServerProxy::on_m_socket_readyRead()
{
    QDataStream stream(m_socket);
    while (!stream.atEnd())
    {
        int flag;
        stream >> flag;
        if (flag == LOGIN)
        {
            QString un, pd;
            stream >> un >> pd;
            qDebug() << un + " is login";
            if (!ServerDBInterface::login(un, pd))
                stream << FAILED;
            else
                stream << SUCCEEDED;
        }
        if (flag == IMAGE)
        {
            qDebug() << "Someone is uploading file";
        }
    }
    qDebug() << "Read End";
}
