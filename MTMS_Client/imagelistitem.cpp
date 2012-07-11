#include "imagelistitem.h"
#include <QFileInfo>
#include <QDebug>
#include <cmath>
#include<QImage>
#include<QBuffer>
ImageListItem::ImageListItem(QFileInfo fileInfo, QObject *parent) :
    QObject(parent)
{
    m_info = NULL;
    setFileInfo(fileInfo);
}

ImageListItem::ImageListItem( const ImageListItem& item)
{
    m_info = NULL;
    setFileInfo(item.fileInfo());
}

ImageListItem::~ImageListItem()
{
    if(m_info != NULL)
    {
        delete m_info;
    }
}

QFileInfo ImageListItem::fileInfo() const
{
    return *m_info;
}

void ImageListItem::setFileInfo(QFileInfo fileInfo)
{
    if(m_info != NULL)
    {
        delete m_info;
    }
    this->m_info = new QFileInfo(fileInfo);
}

QString ImageListItem::name() const
{
    QString str = "";
    if(m_info != NULL)
    {
        str = m_info->fileName();
    }
    return str;
}
QString ImageListItem::path() const
{
    QString str = "";
    if(m_info != NULL)
    {
        str = m_info->filePath();
    }
    return str;
}
QString ImageListItem::size() const
{
    QString str = "";
    if(m_info != NULL)
    {
        QImage img(m_info->absoluteFilePath());
        QByteArray ba;
        QBuffer buffer(&ba);
        buffer.open(QIODevice::WriteOnly);
        img.save(&buffer, "PNG");
        str = QString("%1 Bytes").arg(ba.size());
        //str = QString("%1 Bytes").arg(m_info->size());
    }
    return str;
}
