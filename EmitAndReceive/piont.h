#ifndef PIONT_H
#define PIONT_H
#include <iostream>
using namespace std;
class point
{
public:
    int xPos;
    int yPos;
public:
    point(int x = 0, int y = 0)
    {
        cout << "construct" << endl;
        xPos = x;
        yPos = y;
    }
    ~point()
    {
        cout << "destruct" << endl;
    }
    point(const point & pt)//复制构造函数的定义及实现
    {
        cout << "copy construct" << endl;
        xPos = pt.xPos;
        yPos = pt.yPos;
    }
    point & operator =(const point&p)
    {
        xPos = p.xPos;
        yPos = p.yPos;
        return *this;
    }
    void print()
    {
        cout << "xPos: " << xPos << ",yPos: " << yPos << endl;
    }
};
#endif // PIONT_H
