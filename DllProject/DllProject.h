#ifndef DLLPROJECT_H
#define DLLPROJECT_H

#include <memory>

#if defined(DLLPROJECT_LIBRARY)
#  define DLLPROJECTSHARED_EXPORT __declspec(dllexport)
#else
#  define DLLPROJECTSHARED_EXPORT __declspec(dllimport)
#endif
class DllProjectHead;
class DllProject111;
class DLLPROJECTSHARED_EXPORT DllProject
{

public:
    DllProject();
    ~DllProject();
public:
    int MyCheck(int iType,int value);
private:
    std::shared_ptr<DllProjectHead> m_pDllProjectHead;
    std::shared_ptr<DllProject111> m_pDllProject111;
};
#endif // DLLPROJECT_H
