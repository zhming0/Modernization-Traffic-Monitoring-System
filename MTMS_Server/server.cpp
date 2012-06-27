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
    emit logGenarated("Server start!");
    this->listen(QHostAddress::Any, port);
}

void Server::stopListening()
{
    emit logGenarated("Server stop!");
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
            this, SLOT(on_socket_logGenarated(QString)));
}

void Server::on_socket_imageRead(const QByteArray& bytes)
{
    emit imageRead(bytes);
}

void Server::on_socket_logGenarated(const QString & s)
{
    emit logGenarated(s);
}
