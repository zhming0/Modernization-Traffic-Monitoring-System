#ifndef IMAGELISTITEM_H
#define IMAGELISTITEM_H

#include <QObject>

class QFileInfo;

//! A abstract item to keep the image informatiom
/*!
  */
class ImageListItem : public QObject
{
    Q_OBJECT
public:
    /*! Passing in a fileinfo to establish the item @param fileInfo the file info being passed.*/
    explicit ImageListItem(QFileInfo fileInfo, QObject *parent = 0);

    /*! Copy constructor needed @param item the constant referece to another object.*/
    ImageListItem( const ImageListItem& item);

    virtual ~ImageListItem();

    /*! Set fileinfo to establish the item @param fileInfo the file info being passed*/
    void setFileInfo(QFileInfo fileInfo);

    /*! @return the fileInfo object */
    QFileInfo fileInfo() const;

    /*! @return the filename without path */
    QString name() const;

    /*! @return the filapath which includes the path and filename */
    QString path() const;

    /*! @return the size of the file, which has already converted to PNG format*/
    QString size() const;

private:

    /*! The private QFileInfo object pointer kept inside */
    QFileInfo* m_info;
};

#endif // IMAGELISTITEM_H
