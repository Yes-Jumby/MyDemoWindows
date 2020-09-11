#include "ertete.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ertete w;
    w.show();
    return a.exec();
}
