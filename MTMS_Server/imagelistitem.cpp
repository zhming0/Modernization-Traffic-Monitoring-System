#include "imagelistitem.h"
#include <QFileInfo>
#include <QDebug>
#include <cmath>
#include <QFile>

ImageListItem::ImageListItem(const QFileInfo& fileInfo, bool aliasEnabled, QString alias, QObject *parent) :
    QObject(parent)
{
    m_info = NULL;
    setFileInfo(fileInfo);
    setAliasEnabled(aliasEnabled);
    setAlias(alias);
}

ImageListItem::ImageListItem(QFile* file, QObject *parent) :
    QObject(parent)
{
    QFileInfo info((*file));
    m_info = NULL;
    setFileInfo(info);
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
        str = QString("%1 KB").arg(ceil((m_info->size()/1024.0)));
    }
    return str;
}

void ImageListItem::setAliasEnabled(bool enabled)
{
    this->m_aliasEnabled = enabled;
}

void ImageListItem::setAlias(QString alias)
{
    this->m_alias = alias;
}

QString ImageListItem::alias() const
{
    return this->alias();
}
