/************************************************************************/
/* Copyright (c) 
/* All rights reserved.													
/*																		
/* 文件名称： SpendTime.h
/* 摘要： 获得毫秒级的精确耗时。
/*
/* 当前版本： 1.0
/* 作者： 
/* 完成日期：
/************************************************************************/

#if !defined(SpendTime_h_)
#define SpendTime_h_
#include <windows.h>
class CSpendTime
{
public:
    CSpendTime()
	{
        m_dSpendTime = 0.0;

        QueryPerformanceFrequency(&m_lgiFrequency);
	}

	virtual ~CSpendTime()
	{
	}
    double GetTimeInterval()
    {
        m_lgiCounterEnd = GetMicrosecond();
        return (m_lgiCounterEnd - m_lgiCounterStart)*1.0/ m_lgiFrequency.QuadPart;
    }
    __int64 GetTimeStamp()
    {
    	return GetMicrosecond();
    }
	void Start()
	{
        m_lgiCounterStart = GetMicrosecond();
	}
    __int64 End()
	{
		m_lgiCounterEnd = GetMicrosecond();
		return (m_lgiCounterEnd - m_lgiCounterStart);
	}
protected:
    __int64 GetMicrosecond() {
        LARGE_INTEGER m_lgiTimeStamp;
        QueryPerformanceCounter(&m_lgiTimeStamp);
        return m_lgiTimeStamp.QuadPart;
    }
    __int64 m_lgiCounterStart;
    __int64 m_lgiCounterEnd;
    LARGE_INTEGER m_lgiFrequency;
    double m_dSpendTime;
};

#endif// !defined(SpendTime)
