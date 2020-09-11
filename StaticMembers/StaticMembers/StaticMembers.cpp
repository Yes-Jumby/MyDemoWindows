// StaticMembers.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <stdio.h>  
class Point
{
public:
    Point()
    {
        m_nPointCount++;
        m_nMyValue = 100;
    }
    ~Point()
    {
        m_nPointCount--;
    }
    static void output(Point* tP)
    {
        printf("%d\n%d\n", m_nPointCount, tP->m_nMyValue);
    }
    void output1()
    {
        printf("%d\n", m_nPointCount);
    }
private:
    static int m_nPointCount;
    int m_nMyValue;
};

int Point::m_nPointCount = 0;

void main()
{
    Point pt;
    pt.output(&pt);
    pt.output1();
    Point pt1;
    pt.output(&pt);
    pt1.output(&pt1);
    return;

}

