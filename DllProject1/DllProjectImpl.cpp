#include "DllProjectImpl.h"

DllProjectImpl::DllProjectImpl()
{

}
int DllProjectImpl::MyCheck(int iType, int value)
{
    switch(iType)
    {
            case 3:
                  value = value + 3;
                  break;
            case 4:
                  value = value + 4;
                  break;
            case 5:
                  value = value + 5;
                  break;
            default:
                  value = -1;
                  break;
    }
    return value;
}
