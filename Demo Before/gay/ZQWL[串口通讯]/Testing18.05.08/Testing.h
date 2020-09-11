// Testing.h : main header file for the TESTING application
//

#if !defined(AFX_TESTING_H__D226A2B4_9741_4B41_ACF7_0F3F91DACB7E__INCLUDED_)
#define AFX_TESTING_H__D226A2B4_9741_4B41_ACF7_0F3F91DACB7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CTestingApp:
// See Testing.cpp for the implementation of this class
//

class CTestingApp : public CWinApp
{
public:
	CTestingApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestingApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CTestingApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTING_H__D226A2B4_9741_4B41_ACF7_0F3F91DACB7E__INCLUDED_)
