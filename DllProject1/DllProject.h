#ifndef DLLPROJECT_H
#define DLLPROJECT_H

#include <memory>

#if defined(DLLPROJECT_LIBRARY)
#  define DLLPROJECTSHARED_EXPORT __declspec(dllexport)
#else
#  define DLLPROJECTSHARED_EXPORT __declspec(dllimport)
#endif
class DllProjectImpl;
class DLLPROJECTSHARED_EXPORT DllProject
{

public:
    DllProject();
    ~DllProject();
public:
    int MyCheck(int iType,int value);
private:
    std::shared_ptr<DllProjectImpl> m_pDllProjectImpl;
};
#endif // DLLPROJECT_H
