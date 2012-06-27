#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>

class QLabel;
class QPixmap;
class QMenu;
class QVBoxLayout;
class QScrollArea;
class QScrollBar;

class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = 0);
    QString fileName() const;

signals:
    void displayed(bool fitToWindow);

public slots:
    void load(QPixmap pixmap, QString comment);
    void fitToWindowChange(bool fitToWindow);

private slots:
    void zoomIn();
    void zoomOut();
    void normalSize();
    void fitToWindow();
protected:
    void contextMenuEvent(QContextMenuEvent * e);
    void wheelEvent(QWheelEvent * e);

private:
    QVBoxLayout* m_layout;
    QLabel* m_imageLabel;
    QScrollArea* m_scrollArea;

    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);
    void updateActions();

    double m_scaleFactor;

    QString m_fileName;

    QAction* m_actionZoomIn;
    QAction* m_actionZoomOut;
    QAction* m_actionNormalSize;
    QAction* m_actionFitToWindow;
    QMenu* m_contextMenu;

};

#endif // IMAGEWIDGET_H
