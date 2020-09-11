#include "cinterface.h"
#include <iostream>

//通过导出函数形式向调用方提供指向派生类对象的基类指针
std::shared_ptr<DllProjectHead> Export()
{
    m_pDllProjectHead = std::make_shared<Interface>();
    return m_pDllProjectHead;
}

int Interface::MyCheck(int value)
{
    value = value + 100;
    return value;
}
//void Interface::MyDestroy(void)
//{


//}
