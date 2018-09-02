#include "imageviewer.h"

#include <QApplication>
#include <qevent.h>

ImageViewer::ImageViewer(QWidget *parent) : QScrollArea(parent)
{}

void ImageViewer::wheelEvent(QWheelEvent *event)
{
    if (QApplication::queryKeyboardModifiers().testFlag(Qt::ControlModifier) ) {
        // Prevent the default event control
        return;
    }
    QScrollArea::wheelEvent(event);
}
