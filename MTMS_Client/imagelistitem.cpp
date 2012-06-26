#include "imagelistitem.h"
#include <QFileInfo>

ImageListItem::ImageListItem(QFileInfo fileInfo, QObject *parent) :
    QObject(parent)
{
    m_info = NULL;
    setFileInfo(fileInfo);
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
        m_info->fileName();
    }
    return str;
}
QString ImageListItem::path() const
{
    QString str = "";
    if(m_info != NULL)
    {
        m_info->filePath();
    }
    return str;
}
QString ImageListItem::size() const
{
    QString str = "";
    if(m_info != NULL)
    {
        str.append((int)m_info->size());
    }
    return str;
}