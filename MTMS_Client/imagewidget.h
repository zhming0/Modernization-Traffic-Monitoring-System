#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include <QWidget>

class QLabel;
class QPixmap;
class QMenu;
class QVBoxLayout;
class QScrollArea;
class QScrollBar;

//!A widget to display an image
/*!
  You need to use the load function to load an image. Right click to show the context menu,
  in which you are able to zoom in, zoom out, set to the normal size, or fit to window.
 */
class ImageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImageWidget(QWidget *parent = 0);

    /*!
      @return The file name, which is the comment.
      */
    QString fileName() const;

signals:
    /*!
      emits when the image is successfully displayed.
      @param fitToWindow Whether it is displayed fitting to window.
      */
    void displayed(bool fitToWindow);

public slots:
    /*!
      Loads a pixmap to display and sets the comment.
      @param pixmap The pixmap to load.
      @param comment The comment of pixmap, can be an empty string.
      */
    void load(QPixmap pixmap, QString comment);

    /*!
      Sets if fit to window
      @param fitToWindow Whether to fit to window.
      */
    void fitToWindowChange(bool fitToWindow);

private slots:
    /*!
      Zoom in.
      */
    void zoomIn();
    /*!
      Zoom out.
      */
    void zoomOut();
    /*!
      Sets to normal size.
      */
    void normalSize();
    /*!
      Fits to window.
      */
    void fitToWindow();

protected:
    /*!
      Reimplements to customize context menu.
      */
    void contextMenuEvent(QContextMenuEvent * e);
    /*!
      Reimplements to customize zooming using mouse wheel.
      @param e Event handler.
      */
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
