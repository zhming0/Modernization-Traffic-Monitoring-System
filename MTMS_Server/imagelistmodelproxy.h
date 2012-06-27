#ifndef IMAGELISTMODELPROXY_H
#define IMAGELISTMODELPROXY_H

#include <QObject>

class ImageListItem;
class QStandardItemModel;
class QStandardItem;

class ImageListModelProxy : public QObject
{
    Q_OBJECT
public:
    enum Status {
        UNRECOGNIZED,
        UNPROCESSED,
        PROCESSED,
        ERROR
    };

    explicit ImageListModelProxy(QObject *parent = 0);
    void add(ImageListItem item);
    void remove(int index);
    void remove(QList<int> indexes);
    void setChecked(int index, bool isChecked);
    void setStatus(int index, ImageListModelProxy::Status s);
    int rowCount();
    QList<QString> checkedPaths();
    QList<int> checkedRows();
    QString path(int index);
    ImageListModelProxy::Status status(int index);
    QStandardItemModel * model();

signals:

public slots:

private:
    QStandardItemModel* m_model;

    void createModel();
    QList<QStandardItem*> createRow();

    const static int c_columnCount = 4;

};

#endif // IMAGELISTMODELPROXY_H
