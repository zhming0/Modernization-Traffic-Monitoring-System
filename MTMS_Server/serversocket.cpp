#include "serversocket.h"
#include"serverdbinterface.h"
#include<QBuffer>
#include<QImage>
ServerSocket::ServerSocket(int id)
{
    this->setSocketDescriptor(id);
    connect(this, SIGNAL(readyRead()),
            this, SLOT(on_readyRead()));
    connect(this, SIGNAL(disconnected()),
            this, SLOT(deleteLater()));
    connect(this, SIGNAL(disconnected()),
            this, SLOT(on_disconnected()));
}
bool ServerSocket::waitNextMessage(int timeout)
{
    if (this->bytesAvailable())
        return true;
    if (waitForReadyRead(timeout))
        return true;
    return false;
}
void ServerSocket::on_disconnected()
{
    emit logGenerated(username + " leaved.");
}
void ServerSocket::on_readyRead()
{
    qDebug() << "Reading";
    QDataStream stream(this);
    stream.setVersion(QDataStream::Qt_4_7);
    while (!stream.atEnd())
    {
        int flag;
        stream >> flag;
        if (flag == LOGIN)
        {
            QString pd;
            waitNextMessage(10000);
            stream>>username;
            waitNextMessage(10000);
            stream>>pd;
            qDebug() << username + " is logining.";

            emit logGenerated(username + " is logining.");

            if (!ServerDBInterface::login(username, pd)) {
                stream << FAILED;
                abort();
            }else
                stream << SUCCEEDED;
        }
        if (flag == IMAGE)
        {
            int size;
            waitNextMessage(20000);
            stream >> size;
            qDebug() << "Someone is uploading image, size is " << size;
            QByteArray bytes;
            QBuffer buf(&bytes);
            buf.open(QIODevice::WriteOnly);
            while (bytes.length() < size) {
                waitNextMessage(20000);
                buf.write(this->read(size - bytes.length()));
            }
            //stream << PROGRESS << size;
            emit imageRead(bytes);
            emit logGenerated("Received an image from " + username + QString(", image size is %1 bytes.").arg(size));
        }
    }
    qDebug() << "Read End";
}

void ServerSocket::abortConnection()
{
    this->abort();
}
