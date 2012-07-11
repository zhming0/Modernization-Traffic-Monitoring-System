#ifndef IMAGELISTMODELPROXY_H
#define IMAGELISTMODELPROXY_H

#include <QObject>

class ImageListItem;
class QStandardItemModel;
class QStandardItem;

//! A proxy helps easily maintain and manage the image list
/*!
  ImageListItem is seen as the basic element of this class, whenever you need to add a new
  item, make one.
  To remove one or more items, use remove.
  To set the check state of one item, use setChecked.
  To set the status of one item, use setStatus.
  To get the total number of items in the list, use rowCount.
  To get the index list of all the checked items, use checkedRows.
  You can get a specific item's path, using path, you may also need to get the path list of all the checked items, use checkedPath.
  If the total size of checked item is needed, use checkedSize.
  When you need to set model to a view, use model to get the inside model.
 */
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

    explicit ImageListModelProxy(QObject *parent = 0);

    /*!
      Adds one item.
      @param item ImageListItem is seen as the basic element of this class, to add one
      you need to construct an ImageListItem object, and pass it to this function.
      */
    void add(ImageListItem item);

    /*! Removes one item according to the index
      @param index The item to be removed.
      */
    void remove(int index);

    /*! Removes a list of items according to the indexes
      @param indexes The indexes of items to be removed.
      */
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
