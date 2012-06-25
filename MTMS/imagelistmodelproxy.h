#ifndef IMAGELISTMODELPROXY_H
#define IMAGELISTMODELPROXY_H

#include <QObject>

class QStandardItemModel;
class ImageListItem;

class ImageListModelProxy : public QObject
{
    Q_OBJECT
public:
    explicit ImageListModelProxy(QObject *parent = 0);
    void add(ImageListItem item);
    void remove(int index);
    void setChecked(int index, bool isChecked);

signals:

public slots:

private:
    QStandardItemModel* m_model;

};

#endif // IMAGELISTMODELPROXY_H
