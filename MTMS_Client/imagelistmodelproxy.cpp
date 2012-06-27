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

    QStringList strList;

    strList << item.name() << item.path() << item.size() << "Ready";
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

void ImageListModelProxy::remove(QList<int> indexes)
{
    int rowCount = m_model->rowCount();
    int delta = 0;
    foreach(int index, indexes)
    {
        index = index + delta;
        if(index >= 0 && index < rowCount)
        {
            m_model->removeRow(index);
        }
        else
        {
            qDebug() << "Internal Error#index out of bounds.";
        }
        --delta;
        --rowCount;
    }
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

void ImageListModelProxy::setStatus(int index, ImageListModelProxy::Status s)
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
    QString state = "";
    if(READY == s)
    {
        state = "Ready";
    }
    else if(SENDING == s)
    {
        state = "Sending";
    }
    else if(FINISHED == s)
    {
        state = "Finished";
    }
    else if(ERROR == s)
    {
        state = "Error";
    }
    m_model->item(index, 3)->setText(state);
}

QList<QString> ImageListModelProxy::checkedPaths()
{
    QList<QStandardItem*> checkStateItems;
    for(int i = 0; i < m_model->rowCount(); ++i)
    {
        checkStateItems << m_model->item(i, 0);
    }
    QList<QString> paths;
    int rowIndex = 0;
    foreach(QStandardItem* item, checkStateItems)
    {
        Qt::CheckState state = item->checkState();
        if(Qt::Checked == state)
        {
            QString path = m_model->item(rowIndex, 1)->text();
            paths << path;
        }
        ++rowIndex;
    }
    return paths;
}

QString ImageListModelProxy::path(int index)
{
    if(m_model == NULL)
    {
        qDebug() << "Internal Error#m_model is NULL.";
        return "";
    }
    if(index < 0 || index >= m_model->rowCount())
    {
        qDebug() << "Internal Error#Index out of bounds.";
        return "";
    }
    return m_model->item(index, 1)->text();
}

QStandardItemModel * ImageListModelProxy::model()
{
    return m_model;
}

void ImageListModelProxy::createModel()
{
    m_model = new QStandardItemModel(this);
    m_model->setColumnCount(c_columnCount);

    QStringList columnHeaderTextList;
    columnHeaderTextList <<  "Name" << "Path" << "Size"<< "Status";
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
            item->setCheckState(Qt::Checked);
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignCenter);
        }
        if(i == 2)
        {
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignRight);
        }
        if(i == 3)
        {
            item->setTextAlignment(Qt::AlignVCenter | Qt::AlignCenter);
        }
        list << item;
    }
    return list;
}

int ImageListModelProxy::rowCount()
{
    return this->m_model->rowCount();
}

QList<int> ImageListModelProxy::checkedRows()
{
    QList<QStandardItem*> checkStateItems;
    for(int i = 0; i < m_model->rowCount(); ++i)
    {
        checkStateItems << m_model->item(i, 0);
    }
    QList<int> rows;
    int rowIndex = 0;
    foreach(QStandardItem* item, checkStateItems)
    {
        Qt::CheckState state = item->checkState();
        if(Qt::Checked == state)
        {
            rows << rowIndex;
        }
        ++rowIndex;
    }
    return rows;
}
