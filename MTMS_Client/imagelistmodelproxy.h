#ifndef IMAGELISTMODELPROXY_H
#define IMAGELISTMODELPROXY_H

#include <QObject>

class ImageListItem;
class QStandardItemModel;
class QStandardItem;

/* A Proxy helps the Client MainWindow easily maintain and manage the image list */
class ImageListModelProxy : public QObject
{
    Q_OBJECT
public:
    /* The enum type used to indicate the current state of one specific item */
    enum Status {
        READY,
        SENDING,
        FINISHED,
        ERROR
    };

    /* Constructor */
    explicit ImageListModelProxy(QObject *parent = 0);

    /* Destructor */
    void add(ImageListItem item);

    /* Removes one item according to index or say, an index list */
    void remove(int index);
    void remove(QList<int> indexes);

    /* Sets specific item checked */
    void setChecked(int index, bool isChecked);

    /* Sets the status of a specific item */
    void setStatus(int index, ImageListModelProxy::Status s);

    /* Returns the number of all items */
    int rowCount();

    /* Returns the list of all checked item paths */
    QList<QString> checkedPaths();

    /* Returns the list of all checked row indeces */
    QList<int> checkedRows();

    /* Returns the size in byte of all checked items */
    int checkedSize();

    /* Returns the path of a specific item */
    QString path(int index);

    /* Returns the model kept inside, needed only when calling setModel of view. */
    QStandardItemModel * model();

private:
    /* A function used to init the model */
    void createModel();

    /* The model kept inside */
    QStandardItemModel* m_model;
    /* Creates row */
    QList<QStandardItem*> createRow();
    /* Column numbers */
    const static int c_columnCount = 4;

};

#endif // IMAGELISTMODELPROXY_H
