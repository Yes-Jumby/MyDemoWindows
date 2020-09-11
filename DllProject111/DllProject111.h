#ifndef DLLPROJECT111_H
#define DLLPROJECT111_H

#include <memory>

#if defined(DLLPROJECT111_LIBRARY)
#  define DLLPROJECT111SHARED_EXPORT __declspec(dllexport)
#else
#  define DLLPROJECT111SHARED_EXPORT __declspec(dllimport)
#endif
class DllProject111impl;
class DLLPROJECT111SHARED_EXPORT DllProject111
{

public:
    DllProject111();
public:
    int MyCheck(int value);
private:
    std::shared_ptr<DllProject111impl> m_pDllProject111impl;
};

#endif // DLLPROJECT111_H
