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

void ServerSocket::on_readyRead()
{
    qDebug() << "Reading";
    QDataStream stream(this);
    while (!stream.atEnd())
    {
        int flag;
        stream >> flag;
        if (flag == LOGIN)
        {
            QString un, pd;
            stream >> un >> pd;
            qDebug() << un + " is logining.";
            if (!ServerDBInterface::login(un, pd))
                stream << FAILED;
            else
                stream << SUCCEEDED;
        }
        if (flag == IMAGE)
        {
            qDebug() << "Someone is uploading image";
            QByteArray bytes;
            stream >> bytes;
            emit imageRead(bytes);
        }
    }
    qDebug() << "Read End";
}
