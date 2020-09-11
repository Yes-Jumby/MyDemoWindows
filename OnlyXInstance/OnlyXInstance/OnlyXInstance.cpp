// OnlyXInstance.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <process.h>
#include <iostream>
using namespace std;

class CFinalClass
{
public:
    static CFinalClass* GetInstance()
    {
        if (m_index >= m_count)
        {
            return nullptr;
        }
        m_index++;
        return new CFinalClass();
    }
    static void SetCount(int n)
    {
        m_count = n;
    }
private:
    static int m_index;
    static int m_count;
private://将构造函数和析构函数定义为私有的，这样就不会被继承
    CFinalClass()
    {

    }
    ~CFinalClass()
    {

    }
};
int CFinalClass::m_index = 0;
int CFinalClass::m_count = 0;
int main()
{


    CFinalClass::SetCount(3);
    CFinalClass *p1 = CFinalClass::GetInstance();
    CFinalClass *p2 = CFinalClass::GetInstance();
    CFinalClass *p3 = CFinalClass::GetInstance();
    CFinalClass *p4 = CFinalClass::GetInstance();
    CFinalClass *p5 = CFinalClass::GetInstance();

    if (p1 == nullptr)
    {
        cout << "p1 is nullptr" << endl;
    }
    else
    {
        cout << "p1 is not nullptr" << endl;
    }

    if (p2 == nullptr)
    {
        cout << "p2 is nullptr" << endl;
    }
    else
    {
        cout << "p2 is not nullptr" << endl;
    }

    if (p3 == nullptr)
    {
        cout << "p3 is nullptr" << endl;
    }
    else
    {
        cout << "p3 is not nullptr" << endl;
    }
    cout << "-----------------------------------------" << endl << endl;
    if (p4 == nullptr)
    {
        cout << "p4 is nullptr" << endl;
    }
    if (p5 == nullptr)
    {
        cout << "p5 is nullptr" << endl;
    }
    system("pause");
    return 0;
}
