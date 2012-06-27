#include "serversocket.h"
#include"serverdbinterface.h"
ServerSocket::ServerSocket(int id)
{
    this->setSocketDescriptor(id);
    connect(this, SIGNAL(readyRead()),
            this, SLOT(on_readyRead()));
    connect(this, SIGNAL(disconnected()),
            this, SLOT(deleteLater()));
}
bool ServerSocket::waitNextMessage(int timeout)
{
    if (this->bytesAvailable())
        return true;
    if (waitForReadyRead(timeout))
        return true;
    return false;
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
            QString un, pd;
            waitNextMessage(10000);
            stream>>un;
            waitNextMessage(10000);
            stream>>pd;
            qDebug() << un + " is logining.";
            if (!ServerDBInterface::login(un, pd))
                stream << FAILED;
            else
                stream << SUCCEEDED;
        }
        if (flag == IMAGE)
        {
            waitNextMessage(20000);
            qDebug() << "Someone is uploading image";
            QByteArray bytes;
            stream >> bytes;
            emit imageRead(bytes);
        }
    }
    qDebug() << "Read End";
}
