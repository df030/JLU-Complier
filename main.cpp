#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //w.setWindowFlag(w.windowFlags() &~ Qt::WindowMaximizeButtonHint);
    w.setWindowTitle(QString::fromLocal8Bit("编译原理课程设计"));
    w.show();
    return a.exec();
}
