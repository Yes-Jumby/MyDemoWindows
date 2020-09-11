#include "DllProject.h"
#include "cinterface.h"
#include "dllprojecthead.h"
typedef std::shared_ptr<DllProjectHead>(*FunPtr)(void);
DllProject::DllProject()
{
}

DllProject::~DllProject()
{
}

int DllProject::MyCheck(int iType, int value)
{
    switch(iType)
    {
            case 0:
                    {
                        HINSTANCE hDll = LoadLibrary(L"Interface.dll");// 加载DLL库文件，DLL名称和路径用自己的
                        if (hDll == NULL)
                        {
                            return -1;//std::cout << "load dll fail \n";
                        }
                        FunPtr MyGet = (FunPtr)GetProcAddress(hDll, "Export");// 将指针指向函数首地址
                        if (MyGet == NULL)
                        {
                            return -2;//std::cout << "load dll fail \n";
                        }

                        std::shared_ptr<DllProjectHead> t = MyGet();// 调用导出函数获得抽象类指针
                        value = t->MyCheck(value);// 通过该指针调用类成员函数

                        //FreeLibrary(hDll); //释放库句柄
                    }

                  break;
            case 1:
                        {
                            HINSTANCE hDll = LoadLibrary(L"Interface1.dll");// 加载DLL库文件，DLL名称和路径用自己的
                            if (hDll == NULL)
                            {
                                return -11;//std::cout << "load dll fail \n";
                            }
                            FunPtr MyGet = (FunPtr)GetProcAddress(hDll, "Export");// 将指针指向函数首地址
                            if (MyGet == NULL)
                            {
                                return -12;//std::cout << "load dll fail \n";
                            }

                            std::shared_ptr<DllProjectHead> t = MyGet();// 调用导出函数获得抽象类指针
                            value = t->MyCheck(value);// 通过该指针调用类成员函数

                            FreeLibrary(hDll); //释放库句柄
                        }

                      break;
            case 2:
                        {
                            HINSTANCE hDll = LoadLibrary(L"Interface2.dll");// 加载DLL库文件，DLL名称和路径用自己的
                            if (hDll == NULL)
                            {
                                return -21;//std::cout << "load dll fail \n";
                            }
                            FunPtr MyGet = (FunPtr)GetProcAddress(hDll, "Export");// 将指针指向函数首地址
                            if (MyGet == NULL)
                            {
                                return -22;//std::cout << "load dll fail \n";
                            }

                            std::shared_ptr<DllProjectHead> t = MyGet();// 调用导出函数获得抽象类指针
                            value = t->MyCheck(value);// 通过该指针调用类成员函数

                            //FreeLibrary(hDll); //释放库句柄
                        }

                      break;
            case 3:
                        {
                            HINSTANCE hDll = LoadLibrary(L"Interface3.dll");// 加载DLL库文件，DLL名称和路径用自己的
                            if (hDll == NULL)
                            {
                                return -31;//std::cout << "load dll fail \n";
                            }
                            FunPtr MyGet = (FunPtr)GetProcAddress(hDll, "Export");// 将指针指向函数首地址
                            if (MyGet == NULL)
                            {
                                return -32;//std::cout << "load dll fail \n";
                            }

                            std::shared_ptr<DllProjectHead> t = MyGet();// 调用导出函数获得抽象类指针
                            value = t->MyCheck(value);// 通过该指针调用类成员函数
//                            delete t; // 释放DLL中生成的对象
//                            FreeLibrary(hDll); //释放库句柄
                        }

                      break;
            case 4:
                        {
                            HINSTANCE hDll = LoadLibrary(L"Interface4.dll");// 加载DLL库文件，DLL名称和路径用自己的
                            if (hDll == NULL)
                            {
                                return -41;//std::cout << "load dll fail \n";
                            }
                            FunPtr MyGet = (FunPtr)GetProcAddress(hDll, "Export");// 将指针指向函数首地址
                            if (MyGet == NULL)
                            {
                                return -42;//std::cout << "load dll fail \n";
                            }

                            std::shared_ptr<DllProjectHead> t = MyGet();// 调用导出函数获得抽象类指针
                            value = t->MyCheck(value);// 通过该指针调用类成员函数
//                            delete t; // 释放DLL中生成的对象
//                            FreeLibrary(hDll); //释放库句柄
                        }

                      break;
//            case 5:
//                  value = value + 5;
//                  break;
            default:
                value = -1000;
                  break;

    }

    return value;
}
