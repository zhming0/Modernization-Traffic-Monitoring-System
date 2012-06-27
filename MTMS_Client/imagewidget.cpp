#include "imagewidget.h"
#include <QLabel>
#include <QPixmap>
#include <QAction>
#include <QScrollBar>
#include <QDebug>
#include <QMessageBox>
#include <QLayout>
#include <QMenu>
#include <QContextMenuEvent>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QWheelEvent>

ImageWidget::ImageWidget(QWidget *parent) :
    QWidget(parent)
{
    setMinimumSize(300, 300);
    m_layout = new QVBoxLayout(this);
    this->setLayout(m_layout);

    m_imageLabel = new QLabel(this);
    m_imageLabel->setBackgroundRole(QPalette::Base);
    m_imageLabel->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    m_imageLabel->setScaledContents(true);
    m_imageLabel->hide();
    m_scrollArea = new QScrollArea(this);
    m_scrollArea->setBackgroundRole(QPalette::Dark);
    m_scrollArea->setWidget(m_imageLabel);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    m_layout->addWidget(m_scrollArea);

    this->m_actionFitToWindow = new QAction(tr("Fit To Window"), this);
    m_actionFitToWindow->setEnabled(false);
    m_actionFitToWindow->setCheckable(true);
    this->m_actionNormalSize = new QAction(tr("Normal Size"),this);
    m_actionNormalSize->setEnabled(false);
    this->m_actionZoomIn = new QAction(tr("Zoom In"), this);
    m_actionZoomIn->setEnabled(false);
    this->m_actionZoomOut = new QAction(tr("Zoom Out"), this);
    m_actionZoomOut->setEnabled(false);
    this->m_contextMenu = new QMenu(this);
    m_contextMenu->addAction(m_actionZoomIn);
    m_contextMenu->addAction(m_actionZoomOut);
    m_contextMenu->addAction(m_actionNormalSize);
    m_contextMenu->addSeparator();
    m_contextMenu->addAction(m_actionFitToWindow);
    this->setContextMenuPolicy(Qt::DefaultContextMenu);
    connect(m_actionFitToWindow, SIGNAL(triggered()), this, SLOT(fitToWindow()));
    connect(m_actionNormalSize, SIGNAL(triggered()), this, SLOT(normalSize()));
    connect(m_actionZoomIn, SIGNAL(triggered()), this, SLOT(zoomIn()));
    connect(m_actionZoomOut, SIGNAL(triggered()), this, SLOT(zoomOut()));

}

void ImageWidget::zoomIn()
{
    if(m_scaleFactor > 3)
    {
        return;
    }
    scaleImage(1.25);
}

void ImageWidget::zoomOut()
{
    scaleImage(0.8);
}

void ImageWidget::normalSize()
{
    m_imageLabel->adjustSize();
    m_scaleFactor = 1.0;
}

void ImageWidget::fitToWindow()
{
    bool fitToWindow = m_actionFitToWindow->isChecked();
    m_scrollArea->setWidgetResizable(fitToWindow);
    if (!fitToWindow) {
        normalSize();
    }
    updateActions();
    emit displayed(fitToWindow);
}

void ImageWidget::scaleImage(double factor)
{
    Q_ASSERT(m_imageLabel->pixmap());

    m_scaleFactor *= factor;
    m_imageLabel->resize(m_scaleFactor * m_imageLabel->pixmap()->size());

    adjustScrollBar(m_scrollArea->horizontalScrollBar(), factor);
    adjustScrollBar(m_scrollArea->verticalScrollBar(), factor);

    m_actionZoomIn->setEnabled(m_scaleFactor < 3.0);
    m_actionZoomOut->setEnabled(m_scaleFactor > 0.333);
}

void ImageWidget::adjustScrollBar(QScrollBar *scrollBar, double factor)
{
    scrollBar->setValue(int(factor * scrollBar->value()
                            + ((factor - 1) * scrollBar->pageStep()/2)));
}

void ImageWidget::load(QPixmap pixmap, QString comment)
{

    m_imageLabel->setPixmap(pixmap);


    m_scaleFactor = 1.0;

    m_actionFitToWindow->setEnabled(true);
    updateActions();

    if (!m_actionFitToWindow->isChecked())
        m_imageLabel->adjustSize();
    m_imageLabel->show();
    m_fileName = comment;
    emit displayed(m_actionFitToWindow->isChecked());

}

void ImageWidget::updateActions()
{
    m_actionZoomIn->setEnabled(!m_actionFitToWindow->isChecked());
    m_actionZoomOut->setEnabled(!m_actionFitToWindow->isChecked());
    m_actionNormalSize->setEnabled(!m_actionFitToWindow->isChecked());

}

void ImageWidget::contextMenuEvent(QContextMenuEvent * e)
{
    m_contextMenu->move(e->globalPos());
    m_contextMenu->show();
    e->accept();
}

void ImageWidget::wheelEvent(QWheelEvent *e)
{
    if(e->modifiers() == Qt::ControlModifier && m_imageLabel->pixmap()!= NULL)
    {
        if(e->delta() > 0)
        {
            zoomIn();
        }
        else  if(e->delta() < 0 )
        {
            zoomOut();
        }
        e->accept();
    }

}

void ImageWidget::fitToWindowChange(bool fitToWindow)
{
    m_actionFitToWindow->setChecked(fitToWindow);
    this->fitToWindow();
}

QString ImageWidget::fileName() const
{
    return m_fileName;
}
