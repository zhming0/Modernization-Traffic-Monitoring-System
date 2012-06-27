#include "server.h"
#include<QTcpServer>
#include<QTcpSocket>
#include<QThread>
#include<qDebug>
#include"serversocket.h"
Server::Server(QObject *parent) :
    QTcpServer(parent)
{
}

void Server::startListening(const int &port)
{
    qDebug() << "Server started\n";
    this->listen(QHostAddress::Any, port);
}

void Server::incomingConnection(int id)
{
    QThread* thread = new QThread();
    ServerSocket* socket = new ServerSocket(id);
    socket->moveToThread(thread);
    thread->start();
    connect(thread, SIGNAL(finished()),
            thread, SLOT(deleteLater()));
}

void Server::on_socket_imageRead(const QByteArray& bytes)
{
    emit imageRead(bytes);
}
