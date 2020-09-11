
// IMG_DisplayDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CIMG_DisplayDlg 对话框
class CIMG_DisplayDlg : public CDialogEx
{
// 构造
public:
	CIMG_DisplayDlg(CWnd* pParent = NULL);	// 标准构造函数
	char * m_pBmpData;
	BITMAPINFO* m_pShowBitmapInfo;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMG_DISPLAY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CStatic m_PIC;
	afx_msg void OnBnClickedButton1();
};
