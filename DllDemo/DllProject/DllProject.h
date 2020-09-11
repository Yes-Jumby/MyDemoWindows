#ifndef DLLPROJECT_H
#define DLLPROJECT_H

#include <Windows.h>
#include <memory>

#if defined(DLLPROJECT_LIBRARY)
#  define DLLPROJECTSHARED_EXPORT __declspec(dllexport)
#else
#  define DLLPROJECTSHARED_EXPORT __declspec(dllimport)
#endif
class DLLPROJECTSHARED_EXPORT DllProject
{

public:
    DllProject();
    ~DllProject();
public:
    int MyCheck(int iType,int value);
};
#endif // DLLPROJECT_H
