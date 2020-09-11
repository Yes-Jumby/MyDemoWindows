#if !defined(AFX_CLIENTSOCKET_H__16B79640_951B_45F4_9C07_6C044DD43416__INCLUDED_)
#define AFX_CLIENTSOCKET_H__16B79640_951B_45F4_9C07_6C044DD43416__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ClientSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// CClientSocket command target
#include "Afxsock.h"
//
class CClientDlg;
class CClientSocket : public CSocket
{
// Attributes
public:

// Operations
public:

	CClientSocket();
	virtual ~CClientSocket();
	
// Overrides
public:
	void SetDialog(CClientDlg* pDialog);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSocket)
	public:
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
	CClientDlg *m_pDialog;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTSOCKET_H__16B79640_951B_45F4_9C07_6C044DD43416__INCLUDED_)
