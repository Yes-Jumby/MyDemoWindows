#include "DllProjectDialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DllProjectDialog w;
    w.show();

    return a.exec();
}
