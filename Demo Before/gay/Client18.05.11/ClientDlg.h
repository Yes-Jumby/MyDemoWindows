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
#include "afxwin.h"

#define OUTBUFFERSIZE 12
#define INBUFFERSIZE 11

class CClientDlg : public CDialog
{
// Construction
public:
	CClientDlg(CWnd* pParent = NULL);	// standard constructor
	CClientSocket m_SockClient;
	CString Str;
	enum { IDD = IDD_CLIENT_DIALOG };
	void ReceiveText();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
protected:
	HICON m_hIcon;
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_IP;
	CEdit m_PORT;
//	CEdit m_Message;
	CEdit m_Return;
	CEdit m_Speed;
	afx_msg void OnLogin();
	afx_msg void OnSendText();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnBack();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnSpeed();
	afx_msg void OnBnClickedBtnStarspeed();
//	CButton m_StarSpeed;
	CEdit m_StarSpeed;
	CEdit m_DEC;
	CEdit m_ACC;
	afx_msg void OnBnClickedBtnAcc();
	afx_msg void OnBnClickedBtnDec();
	afx_msg void OnBnClickedBtnTrig();
	afx_msg void OnBnClickedBtnSpeedread();
	afx_msg void OnBnClickedBtnStarspeedread();
	afx_msg void OnBnClickedBtnAccread();
	afx_msg void OnBnClickedBtnDecread();
	afx_msg void OnBnClickedBtnStarstopword();
	afx_msg void OnBnClickedBtnTrigword();
	afx_msg void OnBnClickedBtnMotorstatus();
	afx_msg void OnBnClickedBtnEncoderline();
	afx_msg void OnBnClickedBtnEncodercircle();
	afx_msg void OnBnClickedBtnSensor1circle();
	afx_msg void OnBnClickedBtnSensor2line();
	afx_msg void OnBnClickedBtnSensor2circle();
	afx_msg void OnBnClickedBtnSensor2line2();
	afx_msg void OnBnClickedBtnSensor3circle();
	afx_msg void OnBnClickedBtnSensor3line();
	afx_msg void OnBnClickedBtnSensor4circle();
	afx_msg void OnBnClickedBtnSensor4line();
	CEdit m_Sensor1;
	CEdit m_Sensor2;
	CEdit m_Sensor3;
	CEdit m_Sensor4;
	afx_msg void OnBnClickedBtnSensor1();
	afx_msg void OnBnClickedBtnSensor2();
	afx_msg void OnBnClickedBtnSensor3();
	afx_msg void OnBnClickedBtnSensor4();
	afx_msg void OnBnClickedBtnCirclenum();
	CEdit m_CircleNum;
	CEdit m_LineNum;
	CEdit m_Result;
	afx_msg void OnBnClickedBtnLinenum();
	afx_msg void OnBnClickedBtnResult();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLIENTDLG_H__BF8F4ED0_3068_40FE_98E2_5C9EBA676EA0__INCLUDED_)
