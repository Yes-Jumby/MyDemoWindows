// OutputBmp.h : main header file for the OUTPUTBMP application
//

#if !defined(AFX_OUTPUTBMP_H__C9847799_0FD0_48C0_B05A_A78C1EBAC1C8__INCLUDED_)
#define AFX_OUTPUTBMP_H__C9847799_0FD0_48C0_B05A_A78C1EBAC1C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COutputBmpApp:
// See OutputBmp.cpp for the implementation of this class
//

class COutputBmpApp : public CWinApp
{
public:
	COutputBmpApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputBmpApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(COutputBmpApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTBMP_H__C9847799_0FD0_48C0_B05A_A78C1EBAC1C8__INCLUDED_)
