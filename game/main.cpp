#include <QApplication>
#include "api.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    API api;
    api.getMainWindow()->show();

    return a.exec();
}
