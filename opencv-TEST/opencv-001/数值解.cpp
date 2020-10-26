#include <iostream>
#include <cstring>
/*
    8 * x - 3*y + 2 * z = 20
    4 * x + 11 * y - z = 33
    6 * x + 3 * y + 12 * z = 36
*/
using namespace std;
double fun1(double x, double y, double z)
{
    return 8 * x - 3*y + 2 * z;
}
double fun2(double x, double y, double z)
{
    return 4 * x + 11 * y - z;
}
double fun3(double x, double y, double z)
{
    return 6 * x + 3 * y + 12 * z;
}
double update1(double x1, double x2, double x3)
{
    return (3 * x2 - 2 * x3 + 20) / 8;
}
double update2(double x1, double x2, double x3)
{
    return (-4 * x1 + x3 + 33) / 11;
}
double update3(double x1, double x2, double x3)
{
    return (-6 * x1 - 3 * x2 + 36) / 12;
}
int mainSHUZHIJIE()
{
    double x1, x2, x3;
    x1 = 0;
    x2 = 0;
    x3 = 0;
    double cosFuntion = 100.0;
    int idx = 0;
    do {
        idx++;
        cosFuntion = pow((20 - fun1(x1, x2, x3)), 2) + pow((33 - fun2(x1, x2, x3)), 2) + pow((36 - fun3(x1, x2, x3)), 2);
        cout <<"idx:"<<idx<<"   "<< "cosFuntion:" << cosFuntion << endl;
        if (cosFuntion < 0.001) break;
        x1 = update1(x1, x2, x3);
        x2 = update2(x1, x2, x3);
        x3 = update3(x1, x2, x3);

    } while (true);
    cout << "x1:" << x1 << "   " << "x2:" << x2 << "   " << "x3:" << x3 << endl;
    return 0;
    
}