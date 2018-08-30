#include "imgreader.h"
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

    this->m_imageContainer = QSharedPointer<QLabel>(new QLabel(this));
    this->m_imageContainer->setSizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);

    ui->scrollArea->setAlignment(Qt::AlignCenter);
    ui->scrollArea->setWidget(this->m_imageContainer.get());

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

void ImgReader::display()
{
    if (this->m_filesList.isEmpty()) {
        this->m_imageContainer->clear();
    }
    else {
        QImage image;
        image.load(this->m_filesList[this->m_currentImageIndex]);
        this->m_imageContainer->setPixmap(QPixmap::fromImage(image));
        this->ui->scrollArea->verticalScrollBar()->setValue(0);
    }
    this->updateStatusBar();
}

void ImgReader::updateStatusBar()
{
    QString statusMessage;
    if (this->m_filesList.isEmpty() || this->m_filesList.size() == 0) {
        statusMessage = "Ready";
    }
    else {
        statusMessage = QString("%1/%2").arg(QString::number(this->m_currentImageIndex+1)).arg(QString::number(this->m_filesList.size()));
    }
    this->m_statusBarMessage->setText(statusMessage);
}

void ImgReader::mousePressEvent(QMouseEvent *ev)
{
    if(ev->buttons() == Qt::LeftButton){
        this->handleNext();
    }
    else if(ev->buttons() == Qt::RightButton) {
        this->handlePrevious();
    }
    else {
        return;
    }
    this->updateStatusBar();
}

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
    this->m_filesList.clear();
    this->display();
}
