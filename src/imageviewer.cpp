#include "include/imageviewer.h"

#include <QApplication>
#include <QKeyEvent>

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

void ImageViewer::keyPressEvent(QKeyEvent *event)
{
    // process key press in sub frame
    if (event->key() == Qt::Key_Left) {
        // Prevent the default event control, let the parent widget take control
        emit LeftKeyPressed();
        return;
    }
    if (event->key() == Qt::Key_Right) {
        // Prevent the default event control, let the parent widget take control
        emit RightKeyPressed();
        return;
    }
    QScrollArea::keyPressEvent(event);
}
