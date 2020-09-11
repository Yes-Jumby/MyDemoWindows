#ifndef TEST_H
#define TEST_H

#if defined(TEST_LIBRARY)
#  define TESTSHARED_EXPORT __declspec(dllexport)
#else
#  define TESTSHARED_EXPORT __declspec(dllimport)
#endif
#include "cinterface.h"
#include <string>
class TESTSHARED_EXPORT Test:public Interface
{
public:
    Test();
    virtual ~Test();
    virtual void ShowMsg(void);
private:
    std::string s;
};


#endif // TEST_H
