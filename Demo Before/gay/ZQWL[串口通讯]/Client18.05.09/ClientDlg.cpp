// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
#include "Parameter.h"//串口通信
#pragma comment(lib,"PCOMM")  ////串口lib文件

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
Parameter Parameter;//串口通信
DWORD m_TimerID;//定时器ID
SYSTEMTIME utm0;//系统时间
CString Str;
bool flag[2]={false};
bool IsOpen=false;
bool IsClose=false;
int num=0;
int num1=1;
char Close[BUFFERSIZE]={0x48,0x3A,0x01,0x57,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xDA,0x45,0x44};
char Open[BUFFERSIZE]={0x48,0x3A,0x01,0x57,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xDB,0x45,0x44};
class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg dialog

CClientDlg::CClientDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CClientDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CClientDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CClientDlg)
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_EDIT_Current, m_Current1);
	DDX_Control(pDX, IDC_EDIT_Code, m_Code);
	DDX_Control(pDX, IDC_EDIT_Time, m_Time);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	//{{AFX_MSG_MAP(CClientDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOGIN, OnLogin)
	ON_BN_CLICKED(IDC_SENDTEXT, OnSendText)
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CClientDlg message handlers

BOOL CClientDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	m_SockClient.Create();
	m_SockClient.SetDialog(this);

	flag[0]=Parameter.Open(1,3);//打开串口
	flag[1]=m_SockClient.Connect("192.168.1.253",1030);//连接IP地址
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClientDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClientDlg::OnPaint() 
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
HCURSOR CClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClientDlg::OnOK() 
{

}

void CClientDlg::ReceiveText()
{

	/*
	int len =  m_SockClient.Receive(buffer,BUFFERSIZE);
	CString STR;
	STR.Format("%s",buffer);*/
	//m_List.AddString(STR);
	/*if (len != -1)
	{
		buffer[len] = '\0';
		m_List.AddString(buffer);
	}*/
}

void CClientDlg::OnLogin() //开始做实验
{
	m_TimerID=SetTimer(0, // timer identifier 
             30000, // 1 second interval 
            (TIMERPROC) NULL  // no timer callback 
             );
	m_TimerID=SetTimer(1, // timer identifier 
             1000, // 30 second interval 
            (TIMERPROC) NULL  // no timer callback 
             );
		

    m_SockClient.Send(Open,15);//开启
	m_SockClient.Receive(buffer,BUFFERSIZE);
	Str.Format("0x%2X 0x%2X 0x0%X 0x%2X 0x0%X 0x0%X 0x0%X 0x0%X 0x0%X 0x0%X 0x0%X 0x0%X 0x%X 0x%2X 0x%2X",
	buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5],
	buffer[6],buffer[7],buffer[8],buffer[9],buffer[10],buffer[11],buffer[12]&0xFF,buffer[13],buffer[14]);
	 m_Code.SetWindowText(Str);
	IsOpen=true;
}

void CClientDlg::OnSendText() //关闭
{
	/*
	CString strText,strInfo;
	m_Text.GetWindowText(strText);
	if (!strText.IsEmpty() && !m_Name.IsEmpty())
	{
		strInfo.Format("%s说: %s",m_Name,strText);
		int len = m_SockClient.Send(strInfo.GetBuffer(strInfo.GetLength()),strInfo.GetLength());
	}
	*/

	Parameter.Close();//关闭串口	
    KillTimer(0);//关闭状态显示
	m_SockClient.Send(Close,15);
	IsOpen=false;
	IsClose=true;
	CDialog::OnOK();

}


void CClientDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(0 == nIDEvent)
	{
	sprintf(buf,"%d",Parameter.Read());
	m_Current1.SetWindowText(buf);
	num++;
	if(IsOpen && num==1)
	{
	m_SockClient.Send(Close,15);
	IsOpen=false;
	IsClose=true;
	num=0;
	m_SockClient.Receive(buffer,BUFFERSIZE);
	Str.Format("0x%2X 0x%2X 0x0%X 0x%2X 0x0%X 0x0%X 0x0%X 0x0%X 0x0%X 0x0%X 0x0%X 0x0%X 0x%X 0x%2X 0x%2X",
	buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5],
	buffer[6],buffer[7],buffer[8],buffer[9],buffer[10],buffer[11],buffer[12]&0xFF,buffer[13],buffer[14]);
	}
	if(IsClose && num==4)
	{
	    m_SockClient.Send(Open,15);
		m_SockClient.Receive(buffer,BUFFERSIZE);
	IsOpen=true;
	IsClose=false;
	num=0;
	Str.Format("0x%2X 0x%2X 0x0%X 0x%2X 0x0%X 0x0%X 0x0%X 0x0%X 0x0%X 0x0%X 0x0%X 0x0%X 0x%X 0x%2X 0x%2X",
	buffer[0],buffer[1],buffer[2],buffer[3],buffer[4],buffer[5],
	buffer[6],buffer[7],buffer[8],buffer[9],buffer[10],buffer[11],buffer[12]&0xFF,buffer[13],buffer[14]);
	}
    m_Code.SetWindowText(Str);
	}

	if(1 == nIDEvent)
	{
    sprintf(buf,"%d",num1);
	m_Time.SetWindowText(buf);
	sprintf(buf,"%d",Parameter.Read());
	m_Current1.SetWindowText(buf);

	
	GetLocalTime(&utm0);
	FILE* file0 = fopen("Curent.txt", "a+");
    fprintf(file0, "%d\t%s\t%s\t%d:%d:%dT%d:%d:%d:%d\n",num1,buf,Str,utm0.wYear,utm0.wMonth,utm0.wDay,utm0.wHour,utm0.wMinute,utm0.wSecond,utm0.wMilliseconds);
	fclose(file0);
	if(num1==150)
		num1=0;
	num1++;
	}
	CDialog::OnTimer(nIDEvent);
}
