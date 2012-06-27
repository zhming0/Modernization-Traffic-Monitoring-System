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
    emit logGenerated("Server started!");
    this->listen(QHostAddress::Any, port);
}

void Server::stopListening()
{
    emit logGenerated("Server stopped!");
    this->close();
}

void Server::incomingConnection(int id)
{
    QThread* thread = new QThread();
    ServerSocket* socket = new ServerSocket(id);
    socket->moveToThread(thread);
    thread->start();
    connect(thread, SIGNAL(finished()),
            thread, SLOT(deleteLater()));
    connect(socket, SIGNAL(logGenerated(QString)),
            this, SLOT(on_socket_logGenerated(QString)));
    connect(socket, SIGNAL(imageRead(QByteArray)),
            this, SLOT(on_socket_imageRead(QByteArray)));
}

void Server::on_socket_imageRead(const QByteArray& bytes)
{
    emit imageRead(bytes);
}

void Server::on_socket_logGenerated(const QString & s)
{
    emit logGenerated(s);
}
