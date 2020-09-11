// SingleInstance.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<iostream>
using namespace std;

class singleton
{
public:
    static singleton* getpsin()
    {
        if (psin == nullptr)
        {
            psin = new singleton();
        }
        return psin;
    }
    static void relice()
    {
        if (psin != nullptr)
        {
            cout << "-----" << endl;
            delete psin;
        }
        psin = nullptr;
    }

private:
    singleton()
    {
        cout << "+++++" << endl;
    }
    ~singleton()
    {
        if (psin != nullptr)
        {
            cout << "-----" << endl;
            delete psin;
        }
        psin = nullptr;
    }
    static singleton* psin;
};

singleton* singleton::psin = nullptr;

int main()
{
    singleton* p = singleton::getpsin();
    singleton* p1 = singleton::getpsin();
    return 0;
}

