/********************************************************************************
** Form generated from reading UI file 'imgreader.ui'
**
** Created by: Qt User Interface Compiler version 5.11.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMGREADER_H
#define UI_IMGREADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <include/imageviewer.h>

QT_BEGIN_NAMESPACE

class Ui_ImgReader
{
public:
    QAction *actionOpen;
    QAction *actionExit;
    QAction *actionAbout;
    QAction *actionCloseAll;
    QWidget *centralWidget;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout;
    QPushButton *previousButton;
    QPushButton *nextButton;
    ImageViewer *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QMenuBar *menuBar;
    QMenu *menuImageReader;
    QMenu *menuAbout;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ImgReader)
    {
        if (ImgReader->objectName().isEmpty())
            ImgReader->setObjectName(QStringLiteral("ImgReader"));
        ImgReader->resize(557, 417);
        actionOpen = new QAction(ImgReader);
        actionOpen->setObjectName(QStringLiteral("actionOpen"));
        actionOpen->setMenuRole(QAction::ApplicationSpecificRole);
        actionExit = new QAction(ImgReader);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAbout = new QAction(ImgReader);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionCloseAll = new QAction(ImgReader);
        actionCloseAll->setObjectName(QStringLiteral("actionCloseAll"));
        centralWidget = new QWidget(ImgReader);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_3 = new QGridLayout(centralWidget);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        previousButton = new QPushButton(centralWidget);
        previousButton->setObjectName(QStringLiteral("previousButton"));

        gridLayout->addWidget(previousButton, 1, 1, 1, 1);

        nextButton = new QPushButton(centralWidget);
        nextButton->setObjectName(QStringLiteral("nextButton"));

        gridLayout->addWidget(nextButton, 1, 2, 1, 1);

        scrollArea = new ImageViewer(centralWidget);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollArea->sizePolicy().hasHeightForWidth());
        scrollArea->setSizePolicy(sizePolicy);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 535, 309));
        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout->addWidget(scrollArea, 0, 1, 1, 2);


        gridLayout_3->addLayout(gridLayout, 0, 0, 1, 1);

        ImgReader->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ImgReader);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 557, 23));
        menuImageReader = new QMenu(menuBar);
        menuImageReader->setObjectName(QStringLiteral("menuImageReader"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        ImgReader->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ImgReader);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        ImgReader->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ImgReader);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        ImgReader->setStatusBar(statusBar);

        menuBar->addAction(menuImageReader->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuImageReader->addAction(actionOpen);
        menuImageReader->addAction(actionCloseAll);
        menuImageReader->addAction(actionExit);
        menuAbout->addAction(actionAbout);

        retranslateUi(ImgReader);
        QObject::connect(actionExit, SIGNAL(triggered()), ImgReader, SLOT(close()));

        QMetaObject::connectSlotsByName(ImgReader);
    } // setupUi

    void retranslateUi(QMainWindow *ImgReader)
    {
        ImgReader->setWindowTitle(QApplication::translate("ImgReader", "ImgReader", nullptr));
        actionOpen->setText(QApplication::translate("ImgReader", "Open", nullptr));
        actionExit->setText(QApplication::translate("ImgReader", "Exit", nullptr));
        actionAbout->setText(QApplication::translate("ImgReader", "About", nullptr));
        actionCloseAll->setText(QApplication::translate("ImgReader", "Close All", nullptr));
        previousButton->setText(QApplication::translate("ImgReader", "Previous", nullptr));
        nextButton->setText(QApplication::translate("ImgReader", "Next", nullptr));
        menuImageReader->setTitle(QApplication::translate("ImgReader", "File", nullptr));
        menuAbout->setTitle(QApplication::translate("ImgReader", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ImgReader: public Ui_ImgReader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMGREADER_H
