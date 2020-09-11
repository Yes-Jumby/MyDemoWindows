// Struct.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
using namespace std;
#define FreePt(Pt) if(Pt!=nullptr){delete Pt;Pt=nullptr;}else{Pt=nullptr;}
/*封装多类型变量*/
struct AVariant
{
public:
    enum DATATYPE { INT, FLOAT, STRING, NAL };
    AVariant() {
        pnVal = nullptr;
        pstrVal = nullptr;
        pfVal = nullptr;
        nType = NAL;
    }
    AVariant(const int& nVal) {
        pnVal = new int(nVal);
        pstrVal = nullptr;
        pfVal = nullptr;
        nType = INT;
    }
    AVariant(const float &fVal) {
        pfVal = new float(fVal);
        pnVal = nullptr;
        pstrVal = nullptr;
        nType = FLOAT;
    }
    AVariant(const std::string& strVal) {
        pstrVal = new std::string(strVal);
        pnVal = nullptr;
        pfVal = nullptr;
        nType = STRING;
    }
    AVariant(const AVariant& val) {
        nType = val.nType;
        if (nType == INT&&val.pnVal != nullptr)
        {

            pnVal = new int(*val.pnVal);
            pfVal = nullptr;
            pstrVal = nullptr;
        }
        else if (nType == FLOAT&&val.pfVal != nullptr)
        {

            pfVal = new float(*val.pfVal);
            pnVal = nullptr;
            pstrVal = nullptr;

        }
        else if (nType == STRING&&val.pstrVal != nullptr)
        {

            pstrVal = new std::string(*val.pstrVal);
            pnVal = nullptr;
            pfVal = nullptr;
        }
        else
        {
            nType = NAL;
            pnVal = nullptr;
            pnVal = nullptr;
            pfVal = nullptr;
        }
    }
    ~AVariant() {
        if (nType == STRING)
        {
            FreePt(pstrVal);
        }
        if (nType == INT)
        {
            FreePt(pnVal);
        }
        if (nType == FLOAT)
        {
            FreePt(pfVal);
        }

    }

    AVariant& operator=(const int& nVal) {
        if (pnVal == nullptr)
        {
            pnVal = new int(nVal);
        }
        else
        {
            *pnVal = nVal;
        }
        nType = INT;
        FreePt(pstrVal);
        FreePt(pfVal);
        return *this;
    }
    AVariant& operator=(const float& fVal) {
        if (pfVal == nullptr)
        {
            pfVal = new float(fVal);
        }
        else
        {
            *pfVal = fVal;
        }
        nType = FLOAT;
        FreePt(pstrVal);
        FreePt(pnVal);
        return *this;
    }
    AVariant& operator=(const std::string& strVal) {
        if (pstrVal == nullptr)
        {
            pstrVal = new std::string(strVal);
        }
        else
        {
            *pstrVal = strVal;
        }
        nType = STRING;
        FreePt(pfVal);
        FreePt(pnVal);
        return *this;
    }
    AVariant& operator=(const AVariant& val) {
        nType = val.nType;
        if (nType == INT&&val.pnVal != nullptr)
        {
            if (pnVal == nullptr)
            {
                pnVal = new int(*val.pnVal);
            }
            else
            {
                *pnVal = (*val.pnVal);
            }
            FreePt(pstrVal);
            FreePt(pfVal);
        }
        else if (nType == FLOAT&&val.pfVal != nullptr)
        {
            if (pfVal == nullptr)
            {
                pfVal = new float(*val.pfVal);
            }
            else
            {
                *pfVal = (*val.pfVal);
            }
            FreePt(pstrVal);
            FreePt(pnVal);
        }
        else if (nType == STRING&&val.pstrVal != nullptr)
        {
            if (pstrVal == nullptr)
            {
                pstrVal = new std::string(*val.pstrVal);
            }
            else
            {
                *pstrVal = (*val.pstrVal);
            }
            FreePt(pfVal);
            FreePt(pnVal);
        }
        else
        {
            nType = NAL;
            FreePt(pfVal);
            FreePt(pstrVal);
            FreePt(pnVal);
        }
        return *this;
    }
    int GetIValue()
    {
        if (nType == INT&&pnVal != nullptr)
        {
            return *pnVal;
        }
        return 0;
    }
    float GetFValue()
    {
        if (nType == FLOAT&&pfVal != nullptr)
        {
            return *pfVal;
        }
        return 0;
    }
    std::string GetStrValue()
    {
        if (nType == STRING&&pstrVal != nullptr)
        {
            return *pstrVal;
        }
        return "NAL";
    }
    DATATYPE GetType()
    {
        return nType;
    }
private:
    DATATYPE nType;
    int *pnVal;
    std::string *pstrVal;
    float *pfVal;
};
struct MyStruct //定义一个struct
{
    char c1;
    int n2;
    double db3;
    void fun();
};
void f()
{
    int a = 90;
}
int main()
{
    MyStruct a = {'C',9,7.6};
    int b = a.n2;
    return 0;
}

