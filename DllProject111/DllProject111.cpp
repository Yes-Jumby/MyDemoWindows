#include "DllProject111.h"
#include "DllProject111impl.h"

DllProject111::DllProject111()
{
    m_pDllProject111impl = std::make_shared<DllProject111impl>();
}

int DllProject111::MyCheck(int value)
{
    value = value + 111;
    return value;
}
