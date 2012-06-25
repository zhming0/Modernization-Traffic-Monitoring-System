#ifndef IMAGELISTITEM_H
#define IMAGELISTITEM_H

#include <QObject>

class QFileInfo;

class ImageListItem : public QObject
{
    Q_OBJECT
public:
    explicit ImageListItem(QFileInfo fileInfo, QObject *parent = 0);
    void setFileInfo(QFileInfo fileInfo);

signals:

public slots:

};

#endif // IMAGELISTITEM_H
