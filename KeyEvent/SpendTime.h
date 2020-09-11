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
#include <Windows.h>
#if !defined(SpendTime_h_)
#define SpendTime_h_
	
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

	// 开始
	void Start()
	{
		QueryPerformanceCounter(&m_lgiCounterStart);
	}

	// 结束
	int End()	// 返回值：耗时（单位：毫秒）
	{
		QueryPerformanceCounter(&m_lgiCounterEnd);
		
		m_dSpendTime = (m_lgiCounterEnd.QuadPart - m_lgiCounterStart.QuadPart)*1.0 / m_lgiFrequency.QuadPart;

        return (int)(m_dSpendTime*1000);
	}
	
	// 获得耗时（单位：毫秒）
	int GetMillisecondInt()
	{
		return (int)(m_dSpendTime*1000);
	}
	
	// 获得耗时（单位：毫秒）
	double GetMillisecondDouble()
	{
		return (m_dSpendTime*1000);
	}

    //
    int GetFrequency()
    {
        return m_lgiFrequency.QuadPart;
    }
    //

protected:
	
	LARGE_INTEGER m_lgiCounterStart;
	LARGE_INTEGER m_lgiCounterEnd;
	LARGE_INTEGER m_lgiFrequency;
	double m_dSpendTime;
};

#endif// !defined(SpendTime)
