#ifndef IMAGELISTITEM_H
#define IMAGELISTITEM_H

#include <QObject>

class QFileInfo;
class QFile;
class ImageListItem : public QObject
{
    Q_OBJECT
public:
    explicit ImageListItem(QFileInfo fileInfo, QObject *parent = 0);
    explicit ImageListItem(QFile* file, QObject *parent = 0);
    ImageListItem( const ImageListItem& item);
    virtual ~ImageListItem();
    void setFileInfo(QFileInfo fileInfo);
    QFileInfo fileInfo() const;
    QString name() const;
    QString path() const;
    QString size() const;

signals:

public slots:

private:
    QFileInfo* m_info;
};

#endif // IMAGELISTITEM_H