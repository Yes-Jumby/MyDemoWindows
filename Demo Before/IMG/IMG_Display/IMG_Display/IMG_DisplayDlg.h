
// IMG_DisplayDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CIMG_DisplayDlg �Ի���
class CIMG_DisplayDlg : public CDialogEx
{
// ����
public:
	CIMG_DisplayDlg(CWnd* pParent = NULL);	// ��׼���캯��
	char * m_pBmpData;
	BITMAPINFO* m_pShowBitmapInfo;
// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IMG_DISPLAY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
