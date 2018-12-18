#ifndef IMGREADER_H
#define IMGREADER_H

#include <QMainWindow>

class QLabel;

namespace Ui {
class ImgReader;
}

class ImgReader : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImgReader(QWidget *parent = nullptr);
    ~ImgReader();

private:
    Ui::ImgReader *ui;
    QStringList m_filesList;
    QSharedPointer<QLabel> m_imageContainer;
    QSharedPointer<QLabel> m_statusBarMessage;
    QSharedPointer<QLabel> m_statusBarFilePath;
    QSharedPointer<QPixmap> m_image;
    QSharedPointer<const QPoint> m_mousePosition;
    QSharedPointer<const QPoint> m_scrollBarsValueRegister;
    QSharedPointer<const QPoint> m_imageContainerCurrentPos;

    int m_imageScaledPercentage;
    int m_currentImageIndex;

    void _setUpImageContainer(const QSharedPointer<QPixmap> &pixmap, int percentage);

    void display();
    void updateStatusBar();
    void _zoomImage(int percentage);
    void _moveImage(int deltaX, int deltaY);

    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void keyPressEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

private slots:
     void loadFilesList();
     void handleNext();
     void handlePrevious();
     void displayAbout();
     void handleCloseAll();
};

#endif // IMGREADER_H
