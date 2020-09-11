#include "cinterface.h"
#include <iostream>
#include "Test.h"


//通过导出函数形式向调用方提供指向派生类对象的基类指针
Interface* Export(int iType)
{
    if(iType == 0)
    return (Interface*)new Test();
}
