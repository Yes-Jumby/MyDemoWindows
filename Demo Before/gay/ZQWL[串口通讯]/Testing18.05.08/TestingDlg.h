// TestingDlg.h : header file
//

#if !defined(AFX_TESTINGDLG_H__B30B9310_802A_4C44_9CA4_7FCB535890FC__INCLUDED_)
#define AFX_TESTINGDLG_H__B30B9310_802A_4C44_9CA4_7FCB535890FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTestingDlg dialog

class CTestingDlg : public CDialog
{
// Construction
public:
	CTestingDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestingDlg)
	enum { IDD = IDD_TESTING_DIALOG };
	CEdit	m_Current1;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnBtnRed();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTINGDLG_H__B30B9310_802A_4C44_9CA4_7FCB535890FC__INCLUDED_)
