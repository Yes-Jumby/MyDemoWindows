// PerformanceTime.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <Windows.h>

int main()
{
    __int64           m_nFrequency;

    LARGE_INTEGER     nFrequency;

    if (QueryPerformanceFrequency(&nFrequency))
        m_nFrequency = nFrequency.QuadPart;
    else
        m_nFrequency = -1;

    return 0;
}

