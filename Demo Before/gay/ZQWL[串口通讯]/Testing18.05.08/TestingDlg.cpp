// TestingDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Testing.h"
#include "TestingDlg.h"
#include "Parameter.h"//串口通信
#pragma comment(lib,"PCOMM")  ////串口lib文件

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTestingDlg dialog
Parameter Parameter;//串口通信
DWORD m_TimerID;//定时器ID
SYSTEMTIME utm0;//系统时间
bool flag=false;
CTestingDlg::CTestingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestingDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestingDlg)
	DDX_Control(pDX, IDC_EDIT_Current1, m_Current1);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestingDlg, CDialog)
	//{{AFX_MSG_MAP(CTestingDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_RED, OnBtnRed)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestingDlg message handlers

BOOL CTestingDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

    flag=Parameter.Open(1,3);//打开串口
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestingDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestingDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CTestingDlg::OnCancel() 
{
    Parameter.Close();//关闭串口	
    KillTimer(0);//关闭状态显示
	CDialog::OnCancel();
}

void CTestingDlg::OnOK() 
{
	// TODO: Add extra validation here
    
	CDialog::OnOK();
}

void CTestingDlg::OnBtnRed() 
{
	// TODO: Add your control notification handler code here


	m_TimerID=SetTimer(0, // timer identifier 
             1000, // 5 millisecond interval 
            (TIMERPROC) NULL  // no timer callback 
             );

	
}

void CTestingDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if(0 == nIDEvent)
	{
	char buf[4];
	sprintf(buf,"%d",Parameter.Read());
	m_Current1.SetWindowText(buf);
	GetLocalTime(&utm0);
	FILE* file0 = fopen("Curent.txt", "a+");
    fprintf(file0, "%s\t%d:%d:%dT%d:%d:%d:%d\n",buf,utm0.wYear,utm0.wMonth,utm0.wDay,utm0.wHour,utm0.wMinute,utm0.wSecond,utm0.wMilliseconds);
	fclose(file0);
	}

	if(1 == nIDEvent)
	{
	}
	CDialog::OnTimer(nIDEvent);
}
