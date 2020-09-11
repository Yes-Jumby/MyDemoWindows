#include "QwidgetPromoted.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QwidgetPromoted w;
    w.show();

    return a.exec();
}
