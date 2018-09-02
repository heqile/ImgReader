#include "include/imageviewer.h"

#include <QApplication>

ImageViewer::ImageViewer(QWidget *parent) : QScrollArea(parent)
{}

void ImageViewer::wheelEvent(QWheelEvent *event)
{
    if (QApplication::queryKeyboardModifiers().testFlag(Qt::ControlModifier) ) {
        // Prevent the default event control, let the parent widget take control
        return;
    }
    QScrollArea::wheelEvent(event);
}
