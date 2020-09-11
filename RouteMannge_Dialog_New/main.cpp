#include "RouteManage.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RouteManage w;
    w.show();

    return a.exec();
}
