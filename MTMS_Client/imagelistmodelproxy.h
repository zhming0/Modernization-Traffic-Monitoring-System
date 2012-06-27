#ifndef IMAGELISTMODELPROXY_H
#define IMAGELISTMODELPROXY_H

#include <QObject>

class ImageListItem;
class QAbstractItemModel;
class QStandardItemModel;
class QStandardItem;

class ImageListModelProxy : public QObject
{
    Q_OBJECT
public:
    explicit ImageListModelProxy(QObject *parent = 0);
    void add(ImageListItem item);
    void remove(int index);
    void remove(QList<int> indexes);
    void setChecked(int index, bool isChecked);
    QAbstractItemModel * model();

signals:

public slots:

private:
    QStandardItemModel* m_model;

    void createModel();
    QList<QStandardItem*> createRow();

    const static int c_columnCount = 4;

};

#endif // IMAGELISTMODELPROXY_H
