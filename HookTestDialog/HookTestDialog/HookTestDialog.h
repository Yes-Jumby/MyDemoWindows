
// HookTestDialog.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CHookTestDialogApp: 
// �йش����ʵ�֣������ HookTestDialog.cpp
//

class CHookTestDialogApp : public CWinApp
{
public:
	CHookTestDialogApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CHookTestDialogApp theApp;