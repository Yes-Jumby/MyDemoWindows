
// IMG_Display.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIMG_DisplayApp: 
// �йش����ʵ�֣������ IMG_Display.cpp
//

class CIMG_DisplayApp : public CWinApp
{
public:
	CIMG_DisplayApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIMG_DisplayApp theApp;