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
    int m_currentImageIndex;

    void display();
    void updateStatusBar();

    void mousePressEvent(QMouseEvent *ev);

private slots:
     void loadFilesList();
     void handleNext();
     void handlePrevious();
     void displayAbout();
     void handleCloseAll();
};

#endif // IMGREADER_H
