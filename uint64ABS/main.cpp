#include <QDebug>
uint64_t uint64_abs(uint64_t a,uint64_t b)
{
    return (a>b)?(a-b):(b-a);
}
int main()
{

    uint64_t a = 9;
    uint64_t b = 20;
    uint64_t c = 20;
    qDebug()<<a-b;
    qDebug()<<b-a;
    qDebug()<<b-c;
    qDebug()<<"uint64_abs";
    qDebug()<<uint64_abs( a, b);
    qDebug()<<uint64_abs( b, a);;
    qDebug()<<uint64_abs( c, b);;
    long long kkk = -10;
    qDebug()<<kkk;
    bool flag = (b==c);
    qDebug()<<flag;
    qDebug()<<a/2;
    qDebug()<<(a>>1);
    uint64_t aa = 1;
    qDebug()<<(aa>>1);
    qDebug()<<(aa>>2);
    qDebug()<<(aa>>3);
    qDebug()<<(aa>>10);
    return 0;
}
