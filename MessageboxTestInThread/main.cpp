#include "CreatEvent.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CreatEvent w;
    w.show();

    return a.exec();
}
