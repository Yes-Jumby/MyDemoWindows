// ClientDlg.h : header file
//

#if !defined(AFX_CLIENTDLG_H__BF8F4ED0_3068_40FE_98E2_5C9EBA676EA0__INCLUDED_)
#define AFX_CLIENTDLG_H__BF8F4ED0_3068_40FE_98E2_5C9EBA676EA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

#include "ClientSocket.h"
#define BUFFERSIZE 15

class CClientDlg : public CDialog
{
// Construction
public:
	void ReceiveText();
	CClientDlg(CWnd* pParent = NULL);	// standard constructor
	CClientSocket m_SockClient;
// Dialog Data
	//{{AFX_DATA(CClientDlg)
	enum { IDD = IDD_CLIENT_DIALOG };
	char buffer[BUFFERSIZE];
	char buf[8];
	char buf1[8];
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CClientDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	afx_msg void OnLogin();
	afx_msg void OnSendText();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CEdit m_Current1;
	CEdit m_Code;
	CEdit m_Count;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDLG_H__BF8F4ED0_3068_40FE_98E2_5C9EBA676EA0__INCLUDED_)
