#include "DllProject.h"
#include "DllProjectImpl.h"
#include "dllprojecthead.h"
#include "DllProject111.h"
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
                  m_pDllProjectHead = std::make_shared<DllProjectImpl>();
                  value = m_pDllProjectHead->MyCheck(value);
                  break;
            case 1:
                  m_pDllProject111 =std::make_shared<DllProject111>();
                  value = m_pDllProject111->MyCheck(value);
                  break;
//            case 4:
//                  value = value + 4;
//                  break;
//            case 5:
//                  value = value + 5;
//                  break;
            default:
                  value = -1;
                  break;

    }
    return value;
}
