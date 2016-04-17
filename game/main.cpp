#include "mainwindow_connect.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow_connect w;
    w.show();

    return a.exec();
}
