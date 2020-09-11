// OutputStream.h : main header file for the OUTPUTSTREAM application
//

#if !defined(AFX_OUTPUTSTREAM_H__D6B9786F_6DFA_4591_B013_C5E29B05CD3B__INCLUDED_)
#define AFX_OUTPUTSTREAM_H__D6B9786F_6DFA_4591_B013_C5E29B05CD3B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// COutputStreamApp:
// See OutputStream.cpp for the implementation of this class
//

class COutputStreamApp : public CWinApp
{
public:
	COutputStreamApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputStreamApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(COutputStreamApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTSTREAM_H__D6B9786F_6DFA_4591_B013_C5E29B05CD3B__INCLUDED_)
