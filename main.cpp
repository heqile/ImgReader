#include "imgreader.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImgReader w;
    w.show();
    QIcon icon(":/resource/icon.jpg");
    a.setWindowIcon(icon);

    return a.exec();
}
