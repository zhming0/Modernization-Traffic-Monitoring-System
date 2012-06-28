#ifndef IMAGELISTITEM_H
#define IMAGELISTITEM_H

#include <QObject>

class QFileInfo;
class QFile;
class ImageListItem : public QObject
{
    Q_OBJECT
public:
    explicit ImageListItem(const QFileInfo& fileInfo, bool aliasEnabled = false, QString alias = "", QObject *parent = 0);
    explicit ImageListItem(QFile* file, QObject *parent = 0);
    ImageListItem( const ImageListItem& item);
    virtual ~ImageListItem();
    void setFileInfo(QFileInfo fileInfo);
    QFileInfo fileInfo() const;
    QString name() const;
    QString path() const;
    QString size() const;
    QString alias() const;
    void setAliasEnabled(bool enabled);
    void setAlias(QString alias);

signals:

public slots:

private:
    QFileInfo* m_info;
    bool m_aliasEnabled;
    QString m_alias;
};

#endif // IMAGELISTITEM_H
