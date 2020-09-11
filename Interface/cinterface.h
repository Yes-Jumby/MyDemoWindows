#ifndef CINTERFACE_H
#define CINTERFACE_H

#if defined(INTERFACE_LIBRARY)
#  define INTERFACESHARED_EXPORT __declspec(dllexport)
#else
#  define INTERFACESHARED_EXPORT __declspec(dllimport)
#endif

class Interface
{
public:
    virtual void ShowMsg() = 0; // 将调用方需要调用的成员函数声明成纯虚函数
    virtual ~Interface(){};// 抽象类的虚析构函数
};

extern "C" INTERFACESHARED_EXPORT Interface* Export(int iType);
#endif // CINTERFACE_H
