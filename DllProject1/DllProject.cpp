#include "DllProject.h"
#include "DllProjectImpl.h"

DllProject::DllProject()
{
    m_pDllProjectImpl = std::make_shared<DllProjectImpl>();
}

DllProject::~DllProject()
{
}

int DllProject::MyCheck(int iType, int value)
{
    return m_pDllProjectImpl->MyCheck(iType, value);
}
