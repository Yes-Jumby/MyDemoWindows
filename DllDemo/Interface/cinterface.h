#ifndef CINTERFACE_H
#define CINTERFACE_H

#if defined(INTERFACE_LIBRARY)
#  define INTERFACESHARED_EXPORT __declspec(dllexport)
#else
#  define INTERFACESHARED_EXPORT __declspec(dllimport)
#endif
#include "dllprojecthead.h"
#include <memory>
class Interface :public DllProjectHead
{
public:
    Interface()
    {}
    ~Interface(){}
    int MyCheck(int value);
    //void MyDestroy(void);
};
std::shared_ptr<DllProjectHead> m_pDllProjectHead;
extern "C" INTERFACESHARED_EXPORT std::shared_ptr<DllProjectHead> Export();
#endif // CINTERFACE_H
