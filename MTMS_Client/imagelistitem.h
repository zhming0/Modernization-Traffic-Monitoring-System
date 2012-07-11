#ifndef IMAGELISTITEM_H
#define IMAGELISTITEM_H

#include <QObject>

class QFileInfo;

/* A abstract item to keep the image information */
class ImageListItem : public QObject
{
    Q_OBJECT
public:
    /* Passing in a fileinfo to establish the item */
    explicit ImageListItem(QFileInfo fileInfo, QObject *parent = 0);

    /* Copy constructor needed */
    ImageListItem( const ImageListItem& item);

    /* Destructor */
    virtual ~ImageListItem();

    /* Set fileinfo to establish the item */
    void setFileInfo(QFileInfo fileInfo);

    /* Returns the fileInfo object */
    QFileInfo fileInfo() const;

    /* Returns the filename without path */
    QString name() const;

    /* Returns the filapath which includes the path and filename */
    QString path() const;

    /* Returns the size of the file, which has already converted to PNG format*/
    QString size() const;

private:

    /* The private QFileInfo object pointer kept inside */
    QFileInfo* m_info;
};

#endif // IMAGELISTITEM_H
