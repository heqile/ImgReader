#include "include/imgreader.h"
#include "ui_imgreader.h"

#include <QObject>
#include <QFileDialog>
#include <QSizePolicy>
#include <QSharedPointer>
#include <QLabel>
#include <QMouseEvent>
#include <QMessageBox>
#include <QScrollBar>


ImgReader::ImgReader(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::ImgReader), m_currentImageIndex(0)
{
    this->ui->setupUi(this);

    this->m_statusBarMessage = QSharedPointer<QLabel>(new QLabel(this));
    this->ui->statusBar->addWidget(this->m_statusBarMessage.get());
    this->m_statusBarFilePath = QSharedPointer<QLabel>(new QLabel(this));
    this->ui->statusBar->addPermanentWidget(this->m_statusBarFilePath.get());

    this->m_imageContainer = QSharedPointer<QLabel>(new QLabel(this));
    this->m_imageContainer->setSizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);

    ui->scrollArea->setAlignment(Qt::AlignCenter);
    ui->scrollArea->setWidget(this->m_imageContainer.get());

    this->m_imageScaledPercentage = 100;

    this->updateStatusBar();

    connect(this->ui->actionOpen, SIGNAL(triggered()), this, SLOT(loadFilesList()));
    connect(this->ui->actionAbout, SIGNAL(triggered()), this, SLOT(displayAbout()));
    connect(this->ui->actionCloseAll, SIGNAL(triggered()), this, SLOT(handleCloseAll()));
    connect(this->ui->previousButton, SIGNAL(clicked()), this, SLOT(handlePrevious()));
    connect(this->ui->nextButton, SIGNAL(clicked()), this, SLOT(handleNext()));
}

ImgReader::~ImgReader()
{
    delete ui;
}

void ImgReader::_setUpImageContainer(const QSharedPointer<QPixmap>& pixmap, int percentage)
{
    int height = int(pixmap->height() * (percentage / float(100.0)) );
    this->m_imageContainer->setPixmap(pixmap->scaledToHeight(height, Qt::TransformationMode::FastTransformation));
}

void ImgReader::display()
{
    if (this->m_filesList.isEmpty()) {
        this->m_imageContainer->clear();
    }
    else {
        QImage image;
        image.load(this->m_filesList[this->m_currentImageIndex]);
        this->m_image = QSharedPointer<QPixmap>(new QPixmap(QPixmap::fromImage(image)));

        this->_setUpImageContainer(this->m_image, this->m_imageScaledPercentage);

        this->ui->scrollArea->verticalScrollBar()->setValue(0);
    }
    this->updateStatusBar();
}

void ImgReader::updateStatusBar()
{
    QString statusMessage;
    QString filePath;
    if (this->m_filesList.isEmpty() || this->m_filesList.size() == 0) {
        statusMessage = "Ready";
    }
    else {
        filePath = this->m_filesList[this->m_currentImageIndex];
        statusMessage = QString("%1/%2")
                .arg(QString::number(this->m_currentImageIndex+1))
                .arg(QString::number(this->m_filesList.size()));
    }
    this->m_statusBarMessage->setText(statusMessage);
    this->m_statusBarFilePath->setText(filePath);
}

void ImgReader::_zoomImage(int percentage)
{
    const QPixmap *localPixmap = this->m_imageContainer->pixmap();
    if (localPixmap){
        if (percentage <= 0) {
            return;
        }
        this->_setUpImageContainer(this->m_image, this->m_imageScaledPercentage);
    }
}

void ImgReader::_moveImage(int deltaX, int deltaY)
{
    if (!this->m_imageContainerCurrentPos || !this->m_scrollBarsValueRegister) {
        //TODO: exception here
        return;
    }
    // down -> neg delta, up -> pos delta
    int verticalScrollBarValue = this->m_scrollBarsValueRegister->y();
    int verticalScrollBarMaximun = this->ui->scrollArea->verticalScrollBar()->maximum();
    int verticalScrollBarMinimun = this->ui->scrollArea->verticalScrollBar()->minimum();

    if (verticalScrollBarValue - deltaY > verticalScrollBarMaximun) {
        deltaY = verticalScrollBarValue - verticalScrollBarMaximun;
    }
    if (verticalScrollBarValue - deltaY < verticalScrollBarMinimun) {
        deltaY = verticalScrollBarValue - verticalScrollBarMinimun;
    }

    // right -> neg delta, left -> pos delta
    int horizontalScrollBarValue = this->m_scrollBarsValueRegister->x();
    int horizontalScrollBarMaximun = this->ui->scrollArea->horizontalScrollBar()->maximum();
    int horizontalScrollBarMinimun = this->ui->scrollArea->horizontalScrollBar()->minimum();

    if (horizontalScrollBarValue - deltaX > horizontalScrollBarMaximun) {
        deltaX = horizontalScrollBarValue - horizontalScrollBarMaximun;
    }
    if (horizontalScrollBarValue - deltaX < horizontalScrollBarMinimun) {
        deltaX = horizontalScrollBarValue - horizontalScrollBarMinimun;
    }
    this->m_imageContainer->move(this->m_imageContainerCurrentPos->x() + deltaX, this->m_imageContainerCurrentPos->y() + deltaY);
    this->ui->scrollArea->horizontalScrollBar()->setValue(m_scrollBarsValueRegister->x() - deltaX);
    this->ui->scrollArea->verticalScrollBar()->setValue(m_scrollBarsValueRegister->y() - deltaY);
}

void ImgReader::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton){
        this->m_mousePosition = QSharedPointer<QPoint>(new QPoint(ev->windowPos().toPoint()));
        this->m_imageContainerCurrentPos = QSharedPointer<QPoint>(new QPoint(this->m_imageContainer->pos()));
        this->m_scrollBarsValueRegister = QSharedPointer<QPoint>(new QPoint(
                                                               this->ui->scrollArea->horizontalScrollBar()->sliderPosition(),
                                                               this->ui->scrollArea->verticalScrollBar()->sliderPosition()));
    }
}

void ImgReader::mouseMoveEvent(QMouseEvent *ev)
{
    if (this->m_mousePosition) {
        QPoint currentPos = ev->windowPos().toPoint();
        int deltaX = currentPos.x() - this->m_mousePosition->x();
        int deltaY = currentPos.y() - this->m_mousePosition->y();
        this->_moveImage(deltaX, deltaY);
    }
}

void ImgReader::mouseReleaseEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::LeftButton){
        if (*this->m_mousePosition == ev->windowPos().toPoint()) {
            this->handleNext();
        }
        this->m_mousePosition.clear();
    }
    else if(ev->button() == Qt::RightButton) {
        this->handlePrevious();
    }
    else {
        return;
    }
    this->updateStatusBar();
}

void ImgReader::wheelEvent(QWheelEvent *event)
{
    if (QApplication::queryKeyboardModifiers().testFlag(Qt::ControlModifier) ) {
        QPoint p = event->angleDelta()/8;
        if (p.y() > 0) {
            this->m_imageScaledPercentage +=5;
        }
        else {
            if (this->m_imageScaledPercentage > 5) {
                this->m_imageScaledPercentage -= 5;
            }
        }
        this->_zoomImage(this->m_imageScaledPercentage);
    }
    event->accept();
}

// TODO: config pannel;
void ImgReader::loadFilesList()
{
    QFileDialog dialog(this);
    QStringList mimeTypeFilters;
    mimeTypeFilters << "image/jpeg" // will show "JPEG image (*.jpeg *.jpg *.jpe)
                << "image/png"  // will show "PNG image (*.png)"
                << "application/octet-stream"; // will show "All files (*)"
    dialog.setMimeTypeFilters(mimeTypeFilters);
    dialog.setFileMode(QFileDialog::FileMode::ExistingFiles);
    if (dialog.exec()) {
        this->handleCloseAll();
        this->m_filesList.append(dialog.selectedFiles());
    }
    this->display();
}

void ImgReader::handleNext()
{
    if (this->m_filesList.isEmpty()) {
        return;
    }
    this->m_currentImageIndex = (this->m_filesList.size() + this->m_currentImageIndex + 1) % this->m_filesList.size();
    this->display();
}

void ImgReader::handlePrevious()
{
    if (this->m_filesList.isEmpty()) {
        return;
    }
    this->m_currentImageIndex = (this->m_filesList.size() + this->m_currentImageIndex - 1) % this->m_filesList.size();
    this->display();
}

void ImgReader::displayAbout()
{
    QMessageBox aboutMessageBox(this);
    aboutMessageBox.setText("Welcome to use image reader! Have fun!");
    aboutMessageBox.setIcon(QMessageBox::Information);
    aboutMessageBox.exec();
}

void ImgReader::handleCloseAll()
{
    // reset list and current index indicator
    this->m_filesList.clear();
    this->m_currentImageIndex = 0;
    this->display();
}
