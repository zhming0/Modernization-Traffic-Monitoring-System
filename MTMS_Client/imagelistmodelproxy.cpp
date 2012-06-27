#include "imagelistmodelproxy.h"

#include "imagelistitem.h"

#include <QStandardItemModel>
#include <QMessageBox>
#include <QDebug>

ImageListModelProxy::ImageListModelProxy(QObject *parent) :
    QObject(parent)
{
    createModel();
}

void ImageListModelProxy::add(ImageListItem item)
{
    QList<QStandardItem*> list = createRow();
    list.at(0)->setCheckState(Qt::Checked);
    QStringList strList;

    strList << "" << item.name() << item.path() << item.size() << "Ready";
    qDebug() << strList;
    for(int i = 0; i < c_columnCount; ++i)
    {
        list.at(i)->setText(strList.at(i));
    }
    if(m_model == NULL)
    {
        qDebug() << "Internal Error#m_model is NULL.";
        return;
    }
    m_model->appendRow(list);
}

void ImageListModelProxy::remove(int index)
{
    if(m_model == NULL)
    {
        qDebug() << "Internal Error#m_model is NULL.";
        return;
    }
    if(index < 0 || index >= m_model->rowCount())
    {
        qDebug() << "Internal Error#Index out of bounds.";
        return;
    }
    m_model->removeRow(index);
}

void ImageListModelProxy::setChecked(int index, bool isChecked)
{
    if(m_model == NULL)
    {
        qDebug() << "Internal Error#m_model is NULL.";
        return;
    }
    if(index < 0 || index >= m_model->rowCount())
    {
        qDebug() << "Internal Error#Index out of bounds.";
        return;
    }
    Qt::CheckState checkState;
    if(isChecked)
    {
        checkState = Qt::Checked;
    }
    else
    {
        checkState = Qt::Unchecked;
    }
    m_model->item(index, 0)->
            setCheckState(checkState);

}

QAbstractItemModel * ImageListModelProxy::model()
{
    return m_model;
}

void ImageListModelProxy::createModel()
{
    m_model = new QStandardItemModel(this);
    m_model->setColumnCount(c_columnCount);

    QStringList columnHeaderTextList;
    columnHeaderTextList << "Selection" << "Name" << "Path" << "Size"<< "Status";
    m_model->setHorizontalHeaderLabels(columnHeaderTextList);
}

QList<QStandardItem*> ImageListModelProxy::createRow()
{
    QList<QStandardItem*> list;
    for(int i = 0; i < c_columnCount; ++i)
    {
        QStandardItem* item = new QStandardItem();
        if(i == 0)
        {
            item->setCheckable(true);
        }
        list << item;
    }
    return list;
}
