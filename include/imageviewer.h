#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QObject>
#include <QScrollArea>

class ImageViewer : public QScrollArea
{
    Q_OBJECT
private:
    void wheelEvent(QWheelEvent *event);
    void keyPressEvent(QKeyEvent *event);
public:
    explicit ImageViewer(QWidget *parent = nullptr);

signals:
    void LeftKeyPressed();
    void RightKeyPressed();

public slots:
};

#endif // IMAGEVIEWER_H
