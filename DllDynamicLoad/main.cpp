#include <QCoreApplication>
#include <Windows.h>

#include <iostream>
#include "cinterface.h"
// 在调用处添加如下代码
using pExport = Interface* (*)(void); // 定义指向导出函数的指针类型

static LPCWSTR path = L"Interface.dll";

int main()
{
    typedef Interface*(*FunPtr)(int);
    HINSTANCE hDll = LoadLibrary(L"Interface.dll");// 加载DLL库文件，DLL名称和路径用自己的
    if (hDll == NULL)
    {
        std::cout << "load dll fail \n";
        return -1;
    }
    FunPtr MyGet = (FunPtr)GetProcAddress(hDll, "Export");// 将指针指向函数首地址
    if (MyGet == NULL)
    {
        std::cout << "load address fail \n";
        return -1;
    }

    Interface *t = MyGet(0);// 调用导出函数获得抽象类指针
    t->ShowMsg();// 通过该指针调用类成员函数
    delete t; // 释放DLL中生成的对象
    FreeLibrary(hDll); //释放库句柄
    system("pause");
    return 0;
}
