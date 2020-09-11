// ClientDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Client.h"
#include "ClientDlg.h"
//#include "Parameter.h"//串口通信
//#pragma comment(lib,"PCOMM")  ////串口lib文件

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About


unsigned char buffer_out[OUTBUFFERSIZE] = {0x00,0x00,0x00,0x00,0x00,0x06,0x01,0x00,0x00,0x00,0x00,0x00};
unsigned char buffer_in[INBUFFERSIZE] = {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};
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
	DDX_Control(pDX, IDC_EDIT_IP, m_IP);
	DDX_Control(pDX, IDC_EDIT_PORT, m_PORT);
	DDX_Control(pDX, IDC_EDIT_Return, m_Return);
	DDX_Control(pDX, IDC_EDIT_Speed, m_Speed);
	//  DDX_Control(pDX, IDC_BTN_StarSpeed, m_StarSpeed);
	DDX_Control(pDX, IDC_EDIT_StarSpeed, m_StarSpeed);
	DDX_Control(pDX, IDC_EDIT_DEC, m_DEC);
	DDX_Control(pDX, IDC_EDIT_ACC, m_ACC);
	DDX_Control(pDX, IDC_EDIT_Sensor1, m_Sensor1);
	DDX_Control(pDX, IDC_EDIT_Sensor2, m_Sensor2);
	DDX_Control(pDX, IDC_EDIT_Sensor3, m_Sensor3);
	DDX_Control(pDX, IDC_EDIT_Sensor4, m_Sensor4);
	DDX_Control(pDX, IDC_EDIT_CircleNum, m_CircleNum);
	DDX_Control(pDX, IDC_EDIT_LineNum, m_LineNum);
	DDX_Control(pDX, IDC_EDIT_Result, m_Result);
}

BEGIN_MESSAGE_MAP(CClientDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LOGIN, OnLogin)
	ON_BN_CLICKED(IDC_SENDTEXT, OnSendText)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_Back, OnBnClickedBtnBack)
	ON_BN_CLICKED(IDC_BTN_Stop, OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_Speed, OnBnClickedBtnSpeed)
	ON_BN_CLICKED(IDC_BTN_StarSpeed, &CClientDlg::OnBnClickedBtnStarspeed)
	ON_BN_CLICKED(IDC_BTN_ACC, &CClientDlg::OnBnClickedBtnAcc)
	ON_BN_CLICKED(IDC_BTN_DEC, &CClientDlg::OnBnClickedBtnDec)
	ON_BN_CLICKED(IDC_BTN_Trig, &CClientDlg::OnBnClickedBtnTrig)
	ON_BN_CLICKED(IDC_BTN_SpeedRead, &CClientDlg::OnBnClickedBtnSpeedread)
	ON_BN_CLICKED(IDC_BTN_StarSpeedRead, &CClientDlg::OnBnClickedBtnStarspeedread)
	ON_BN_CLICKED(IDC_BTN_ACCRead, &CClientDlg::OnBnClickedBtnAccread)
	ON_BN_CLICKED(IDC_BTN_DECRead, &CClientDlg::OnBnClickedBtnDecread)
	ON_BN_CLICKED(IDC_BTN_StarStopWord, &CClientDlg::OnBnClickedBtnStarstopword)
	ON_BN_CLICKED(IDC_BTN_TrigWord, &CClientDlg::OnBnClickedBtnTrigword)
	ON_BN_CLICKED(IDC_BTN_MotorStatus, &CClientDlg::OnBnClickedBtnMotorstatus)
	ON_BN_CLICKED(IDC_BTN_EncoderLine, &CClientDlg::OnBnClickedBtnEncoderline)
	ON_BN_CLICKED(IDC_BTN_EncoderCircle, &CClientDlg::OnBnClickedBtnEncodercircle)
	ON_BN_CLICKED(IDC_BTN_Sensor1Circle, &CClientDlg::OnBnClickedBtnSensor1circle)
	ON_BN_CLICKED(IDC_BTN_Sensor2Line, &CClientDlg::OnBnClickedBtnSensor2line)
	ON_BN_CLICKED(IDC_BTN_Sensor2Circle, &CClientDlg::OnBnClickedBtnSensor2circle)
	ON_BN_CLICKED(IDC_BTN_Sensor2Line2, &CClientDlg::OnBnClickedBtnSensor2line2)
	ON_BN_CLICKED(IDC_BTN_Sensor3Circle, &CClientDlg::OnBnClickedBtnSensor3circle)
	ON_BN_CLICKED(IDC_BTN_Sensor3Line, &CClientDlg::OnBnClickedBtnSensor3line)
	ON_BN_CLICKED(IDC_BTN_Sensor4Circle, &CClientDlg::OnBnClickedBtnSensor4circle)
	ON_BN_CLICKED(IDC_BTN_Sensor4Line, &CClientDlg::OnBnClickedBtnSensor4line)
	ON_BN_CLICKED(IDC_BTN_Sensor1, &CClientDlg::OnBnClickedBtnSensor1)
	ON_BN_CLICKED(IDC_BTN_Sensor2, &CClientDlg::OnBnClickedBtnSensor2)
	ON_BN_CLICKED(IDC_BTN_Sensor3, &CClientDlg::OnBnClickedBtnSensor3)
	ON_BN_CLICKED(IDC_BTN_Sensor4, &CClientDlg::OnBnClickedBtnSensor4)
	ON_BN_CLICKED(IDC_BTN_CircleNum, &CClientDlg::OnBnClickedBtnCirclenum)
	ON_BN_CLICKED(IDC_BTN_LineNum, &CClientDlg::OnBnClickedBtnLinenum)
	ON_BN_CLICKED(IDC_BTN_Result, &CClientDlg::OnBnClickedBtnResult)
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
	m_IP.SetWindowText("192.168.0.1");
	m_PORT.SetWindowText("506");

	m_SockClient.Create();
	m_SockClient.SetDialog(this);
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

HCURSOR CClientDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CClientDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strIP, strPORT;
	m_IP.GetWindowText(strIP);
	m_PORT.GetWindowText(strPORT);
	int PORT = _ttoi(strPORT);

	if (m_SockClient.Connect(strIP, PORT))//连接IP地址
	{
		Str.Format("连接服务器成功！");
		m_Return.SetWindowText(Str);
		MessageBox(Str);
	}
	else
	{
		Str.Format("连接服务器失败！");
		m_Return.SetWindowText(Str);
		MessageBox(Str);
	}
}

void CClientDlg::OnLogin() //正向运行
{
	buffer_out[7] = 0x06;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x05;

	buffer_out[10] = 0x00;//数据区地址
	buffer_out[11] = 0x0A;
    m_SockClient.Send(buffer_out, OUTBUFFERSIZE);//开启
	m_SockClient.Receive(buffer_out, OUTBUFFERSIZE);
	Str.Format("电机正向运行！ \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		buffer_out[0], buffer_out[1], buffer_out[2], buffer_out[3], buffer_out[4], buffer_out[5],
		buffer_out[6], buffer_out[7], buffer_out[8], buffer_out[9], buffer_out[10], buffer_out[11]);
	m_Return.SetWindowText(Str);

}

void CClientDlg::OnSendText() //关闭
{
	m_SockClient.Close();
	CDialog::OnOK();
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

void CClientDlg::OnOK()
{

}

void CClientDlg::OnBnClickedBtnBack()//反向运行
{

	buffer_out[7] = 0x06;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x05;

	buffer_out[10] = 0x00;//数据区地址
	buffer_out[11] = 0x0C;
	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);//开启
	m_SockClient.Receive(buffer_out, OUTBUFFERSIZE);
	Str.Format("电机反向运行！ \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		buffer_out[0], buffer_out[1], buffer_out[2], buffer_out[3], buffer_out[4], buffer_out[5],
		buffer_out[6], buffer_out[7], buffer_out[8], buffer_out[9], buffer_out[10], buffer_out[11]);
	m_Return.SetWindowText(Str);

}

void CClientDlg::OnBnClickedBtnStop()
{

	buffer_out[7] = 0x06;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x05;

	buffer_out[10] = 0x00;//数据区地址
	buffer_out[11] = 0x0B;
	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);//开启
	m_SockClient.Receive(buffer_out, OUTBUFFERSIZE);
	Str.Format("电机停止！ \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		buffer_out[0], buffer_out[1], buffer_out[2], buffer_out[3], buffer_out[4], buffer_out[5],
		buffer_out[6], buffer_out[7], buffer_out[8], buffer_out[9], buffer_out[10], buffer_out[11]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnSpeed()
{
	
	buffer_out[7] = 0x06;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x03;

	m_Speed.GetWindowText(Str);
	int temp = _ttoi(Str);

	buffer_out[10] = (temp >> 8) & 0xFF;//数据区地址
	buffer_out[11] = temp & 0xFF;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_out, OUTBUFFERSIZE);
	Str.Format("设置运行速度为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_out[0], buffer_out[1], buffer_out[2], buffer_out[3], buffer_out[4], buffer_out[5],
		buffer_out[6], buffer_out[7], buffer_out[8], buffer_out[9], buffer_out[10], buffer_out[11]);
	m_Return.SetWindowText(Str);

}


void CClientDlg::OnBnClickedBtnStarspeed()
{

	buffer_out[7] = 0x06;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x07;

	m_StarSpeed.GetWindowText(Str);
	int temp = _ttoi(Str);

	buffer_out[10] = (temp >> 8) & 0xFF;//数据区地址
	buffer_out[11] = temp & 0xFF;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_out, OUTBUFFERSIZE);
	Str.Format("设置起始速度为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_out[0], buffer_out[1], buffer_out[2], buffer_out[3], buffer_out[4], buffer_out[5],
		buffer_out[6], buffer_out[7], buffer_out[8], buffer_out[9], buffer_out[10], buffer_out[11]);
	m_Return.SetWindowText(Str);

}

void CClientDlg::OnBnClickedBtnAcc()
{

	buffer_out[7] = 0x06;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x09;

	m_StarSpeed.GetWindowText(Str);
	int temp = _ttoi(Str);

	buffer_out[10] = (temp >> 8) & 0xFF;//数据区地址
	buffer_out[11] = temp & 0xFF;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_out, OUTBUFFERSIZE);
	Str.Format("设置加速度为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_out[0], buffer_out[1], buffer_out[2], buffer_out[3], buffer_out[4], buffer_out[5],
		buffer_out[6], buffer_out[7], buffer_out[8], buffer_out[9], buffer_out[10], buffer_out[11]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnDec()
{

	buffer_out[7] = 0x06;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x0B;

	m_StarSpeed.GetWindowText(Str);
	int temp = _ttoi(Str);

	buffer_out[10] = (temp >> 8) & 0xFF;//数据区地址
	buffer_out[11] = temp & 0xFF;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_out, OUTBUFFERSIZE);
	Str.Format("设置减速度为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_out[0], buffer_out[1], buffer_out[2], buffer_out[3], buffer_out[4], buffer_out[5],
		buffer_out[6], buffer_out[7], buffer_out[8], buffer_out[9], buffer_out[10], buffer_out[11]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnTrig()
{

	buffer_out[7] = 0x06;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x0D;

	buffer_out[10] = 0x00;//数据区地址
	buffer_out[11] = 0x32;
	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);//开启
	m_SockClient.Receive(buffer_out, OUTBUFFERSIZE);
	Str.Format("写参数进入硬件！\r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		buffer_out[0], buffer_out[1], buffer_out[2], buffer_out[3], buffer_out[4], buffer_out[5],
		buffer_out[6], buffer_out[7], buffer_out[8], buffer_out[9], buffer_out[10], buffer_out[11]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnSpeedread()
{

	buffer_out[7] = 0x03;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x03;

	buffer_out[10] = 00;//数据位数
	buffer_out[11] = 01;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_in, INBUFFERSIZE);

	int temp = buffer_in[9] * 256 + buffer_in[10];

	Str.Format("运行速度为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_in[0], buffer_in[1], buffer_in[2], buffer_in[3], buffer_in[4], buffer_in[5],
		buffer_in[6], buffer_in[7], buffer_in[8], buffer_in[9], buffer_in[10]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnStarspeedread()
{

	buffer_out[7] = 0x03;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x07;

	buffer_out[10] = 00;//数据位数
	buffer_out[11] = 01;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_in, INBUFFERSIZE);

	int temp = buffer_in[9] * 256 + buffer_in[10];

	Str.Format("起始速度为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_in[0], buffer_in[1], buffer_in[2], buffer_in[3], buffer_in[4], buffer_in[5],
		buffer_in[6], buffer_in[7], buffer_in[8], buffer_in[9], buffer_in[10]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnAccread()
{

	buffer_out[7] = 0x03;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x09;

	buffer_out[10] = 00;//数据位数
	buffer_out[11] = 01;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_in, INBUFFERSIZE);

	int temp = buffer_in[9] * 256 + buffer_in[10];

	Str.Format("加速度为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_in[0], buffer_in[1], buffer_in[2], buffer_in[3], buffer_in[4], buffer_in[5],
		buffer_in[6], buffer_in[7], buffer_in[8], buffer_in[9], buffer_in[10]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnDecread()
{

	buffer_out[7] = 0x03;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x0B;

	buffer_out[10] = 00;//数据位数
	buffer_out[11] = 01;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_in, INBUFFERSIZE);

	int temp = buffer_in[9] * 256 + buffer_in[10];

	Str.Format("减速度为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_in[0], buffer_in[1], buffer_in[2], buffer_in[3], buffer_in[4], buffer_in[5],
		buffer_in[6], buffer_in[7], buffer_in[8], buffer_in[9], buffer_in[10]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnStarstopword()
{

	buffer_out[7] = 0x03;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x05;

	buffer_out[10] = 00;//数据位数
	buffer_out[11] = 01;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_in, INBUFFERSIZE);

	int temp = buffer_in[9] * 256 + buffer_in[10];

	Str.Format("Start_Stop_WORD为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_in[0], buffer_in[1], buffer_in[2], buffer_in[3], buffer_in[4], buffer_in[5],
		buffer_in[6], buffer_in[7], buffer_in[8], buffer_in[9], buffer_in[10]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnTrigword()
{

	buffer_out[7] = 0x03;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x0D;

	buffer_out[10] = 00;//数据位数
	buffer_out[11] = 01;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_in, INBUFFERSIZE);

	int temp = buffer_in[9] * 256 + buffer_in[10];

	Str.Format("Triger_WORD为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_in[0], buffer_in[1], buffer_in[2], buffer_in[3], buffer_in[4], buffer_in[5],
		buffer_in[6], buffer_in[7], buffer_in[8], buffer_in[9], buffer_in[10]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnMotorstatus()
{
	// TODO: 在此添加控件通知处理程序代码
	buffer_out[7] = 0x03;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x15;

	buffer_out[10] = 00;//数据位数
	buffer_out[11] = 01;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_in, INBUFFERSIZE);

	int temp = buffer_in[9] * 256 + buffer_in[10];

	Str.Format("电机状态（1停止，2正转，3反转）为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_in[0], buffer_in[1], buffer_in[2], buffer_in[3], buffer_in[4], buffer_in[5],
		buffer_in[6], buffer_in[7], buffer_in[8], buffer_in[9], buffer_in[10]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnEncoderline()
{
	// TODO: 在此添加控件通知处理程序代码
	buffer_out[7] = 0x03;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x19;

	buffer_out[10] = 00;//数据位数
	buffer_out[11] = 01;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_in, INBUFFERSIZE);

	int temp = buffer_in[9] * 256 + buffer_in[10];

	Str.Format("编码器行数为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_in[0], buffer_in[1], buffer_in[2], buffer_in[3], buffer_in[4], buffer_in[5],
		buffer_in[6], buffer_in[7], buffer_in[8], buffer_in[9], buffer_in[10]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnEncodercircle()
{
	// TODO: 在此添加控件通知处理程序代码
	buffer_out[7] = 0x03;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x15;

	buffer_out[10] = 00;//数据位数
	buffer_out[11] = 01;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_in, INBUFFERSIZE);

	int temp = buffer_in[9] * 256 + buffer_in[10];

	Str.Format("编码器圈数为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_in[0], buffer_in[1], buffer_in[2], buffer_in[3], buffer_in[4], buffer_in[5],
		buffer_in[6], buffer_in[7], buffer_in[8], buffer_in[9], buffer_in[10]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnSensor1circle()
{
	// TODO: 在此添加控件通知处理程序代码
	buffer_out[7] = 0x03;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x27;

	buffer_out[10] = 00;//数据位数
	buffer_out[11] = 01;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_in, INBUFFERSIZE);

	int temp = buffer_in[9] * 256 + buffer_in[10];

	Str.Format("触发传感器1时，编码器圈数为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_in[0], buffer_in[1], buffer_in[2], buffer_in[3], buffer_in[4], buffer_in[5],
		buffer_in[6], buffer_in[7], buffer_in[8], buffer_in[9], buffer_in[10]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnSensor2line()
{
	// TODO: 在此添加控件通知处理程序代码
	buffer_out[7] = 0x03;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x29;

	buffer_out[10] = 00;//数据位数
	buffer_out[11] = 01;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_in, INBUFFERSIZE);

	int temp = buffer_in[9] * 256 + buffer_in[10];

	Str.Format("触发传感器1时，编码器行数为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_in[0], buffer_in[1], buffer_in[2], buffer_in[3], buffer_in[4], buffer_in[5],
		buffer_in[6], buffer_in[7], buffer_in[8], buffer_in[9], buffer_in[10]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnSensor2circle()
{
	// TODO: 在此添加控件通知处理程序代码
	buffer_out[7] = 0x03;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x31;

	buffer_out[10] = 00;//数据位数
	buffer_out[11] = 01;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_in, INBUFFERSIZE);

	int temp = buffer_in[9] * 256 + buffer_in[10];

	Str.Format("触发传感器2时，编码器圈数为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_in[0], buffer_in[1], buffer_in[2], buffer_in[3], buffer_in[4], buffer_in[5],
		buffer_in[6], buffer_in[7], buffer_in[8], buffer_in[9], buffer_in[10]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnSensor2line2()
{
	// TODO: 在此添加控件通知处理程序代码
	buffer_out[7] = 0x03;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x33;

	buffer_out[10] = 00;//数据位数
	buffer_out[11] = 01;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_in, INBUFFERSIZE);

	int temp = buffer_in[9] * 256 + buffer_in[10];

	Str.Format("触发传感器2时，编码器行数为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_in[0], buffer_in[1], buffer_in[2], buffer_in[3], buffer_in[4], buffer_in[5],
		buffer_in[6], buffer_in[7], buffer_in[8], buffer_in[9], buffer_in[10]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnSensor3circle()
{
	// TODO: 在此添加控件通知处理程序代码
	buffer_out[7] = 0x03;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x3B;

	buffer_out[10] = 00;//数据位数
	buffer_out[11] = 01;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_in, INBUFFERSIZE);

	int temp = buffer_in[9] * 256 + buffer_in[10];

	Str.Format("触发传感器3时，编码器圈数为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_in[0], buffer_in[1], buffer_in[2], buffer_in[3], buffer_in[4], buffer_in[5],
		buffer_in[6], buffer_in[7], buffer_in[8], buffer_in[9], buffer_in[10]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnSensor3line()
{
	// TODO: 在此添加控件通知处理程序代码
	buffer_out[7] = 0x03;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x3D;

	buffer_out[10] = 00;//数据位数
	buffer_out[11] = 01;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_in, INBUFFERSIZE);

	int temp = buffer_in[9] * 256 + buffer_in[10];

	Str.Format("触发传感器3时，编码器行数为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_in[0], buffer_in[1], buffer_in[2], buffer_in[3], buffer_in[4], buffer_in[5],
		buffer_in[6], buffer_in[7], buffer_in[8], buffer_in[9], buffer_in[10]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnSensor4circle()
{
	// TODO: 在此添加控件通知处理程序代码
	buffer_out[7] = 0x03;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x45;

	buffer_out[10] = 00;//数据位数
	buffer_out[11] = 01;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_in, INBUFFERSIZE);

	int temp = buffer_in[9] * 256 + buffer_in[10];

	Str.Format("触发传感器4时，编码器圈数为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_in[0], buffer_in[1], buffer_in[2], buffer_in[3], buffer_in[4], buffer_in[5],
		buffer_in[6], buffer_in[7], buffer_in[8], buffer_in[9], buffer_in[10]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnSensor4line()
{
	// TODO: 在此添加控件通知处理程序代码
	buffer_out[7] = 0x03;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x47;

	buffer_out[10] = 00;//数据位数
	buffer_out[11] = 01;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_in, INBUFFERSIZE);

	int temp = buffer_in[9] * 256 + buffer_in[10];

	Str.Format("触发传感器4时，编码器行数为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_in[0], buffer_in[1], buffer_in[2], buffer_in[3], buffer_in[4], buffer_in[5],
		buffer_in[6], buffer_in[7], buffer_in[8], buffer_in[9], buffer_in[10]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnSensor1()
{
	// TODO: 在此添加控件通知处理程序代码
	buffer_out[7] = 0x06;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x25;

	m_Sensor1.GetWindowText(Str);
	int temp = _ttoi(Str);

	buffer_out[10] = (temp >> 8) & 0xFF;//数据区地址
	buffer_out[11] = temp & 0xFF;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_out, OUTBUFFERSIZE);
	Str.Format("设置传感器1的延迟为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_out[0], buffer_out[1], buffer_out[2], buffer_out[3], buffer_out[4], buffer_out[5],
		buffer_out[6], buffer_out[7], buffer_out[8], buffer_out[9], buffer_out[10], buffer_out[11]);
	m_Return.SetWindowText(Str);

}


void CClientDlg::OnBnClickedBtnSensor2()
{
	// TODO: 在此添加控件通知处理程序代码
	buffer_out[7] = 0x06;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x2F;

	m_Sensor2.GetWindowText(Str);
	int temp = _ttoi(Str);

	buffer_out[10] = (temp >> 8) & 0xFF;//数据区地址
	buffer_out[11] = temp & 0xFF;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_out, OUTBUFFERSIZE);
	Str.Format("设置传感器2的延迟为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_out[0], buffer_out[1], buffer_out[2], buffer_out[3], buffer_out[4], buffer_out[5],
		buffer_out[6], buffer_out[7], buffer_out[8], buffer_out[9], buffer_out[10], buffer_out[11]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnSensor3()
{
	// TODO: 在此添加控件通知处理程序代码
	buffer_out[7] = 0x06;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x39;

	m_Sensor3.GetWindowText(Str);
	int temp = _ttoi(Str);

	buffer_out[10] = (temp >> 8) & 0xFF;//数据区地址
	buffer_out[11] = temp & 0xFF;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_out, OUTBUFFERSIZE);
	Str.Format("设置传感器3的延迟为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_out[0], buffer_out[1], buffer_out[2], buffer_out[3], buffer_out[4], buffer_out[5],
		buffer_out[6], buffer_out[7], buffer_out[8], buffer_out[9], buffer_out[10], buffer_out[11]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnSensor4()
{
	// TODO: 在此添加控件通知处理程序代码
	buffer_out[7] = 0x06;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x43;

	m_Sensor4.GetWindowText(Str);
	int temp = _ttoi(Str);

	buffer_out[10] = (temp >> 8) & 0xFF;//数据区地址
	buffer_out[11] = temp & 0xFF;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_out, OUTBUFFERSIZE);
	Str.Format("设置传感器4的延迟为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_out[0], buffer_out[1], buffer_out[2], buffer_out[3], buffer_out[4], buffer_out[5],
		buffer_out[6], buffer_out[7], buffer_out[8], buffer_out[9], buffer_out[10], buffer_out[11]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnCirclenum()
{
	// TODO: 在此添加控件通知处理程序代码
	buffer_out[7] = 0x06;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x1B;

	m_CircleNum.GetWindowText(Str);
	int temp = _ttoi(Str);

	buffer_out[10] = (temp >> 8) & 0xFF;//数据区地址
	buffer_out[11] = temp & 0xFF;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_out, OUTBUFFERSIZE);
	Str.Format("设置编码器圈数为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_out[0], buffer_out[1], buffer_out[2], buffer_out[3], buffer_out[4], buffer_out[5],
		buffer_out[6], buffer_out[7], buffer_out[8], buffer_out[9], buffer_out[10], buffer_out[11]);
	m_Return.SetWindowText(Str);

}


void CClientDlg::OnBnClickedBtnLinenum()
{
	// TODO: 在此添加控件通知处理程序代码
	buffer_out[7] = 0x06;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x1D;

	m_LineNum.GetWindowText(Str);
	int temp = _ttoi(Str);

	buffer_out[10] = (temp >> 8) & 0xFF;//数据区地址
	buffer_out[11] = temp & 0xFF;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_out, OUTBUFFERSIZE);
	Str.Format("设置编码器行数为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_out[0], buffer_out[1], buffer_out[2], buffer_out[3], buffer_out[4], buffer_out[5],
		buffer_out[6], buffer_out[7], buffer_out[8], buffer_out[9], buffer_out[10], buffer_out[11]);
	m_Return.SetWindowText(Str);
}


void CClientDlg::OnBnClickedBtnResult()
{
	// TODO: 在此添加控件通知处理程序代码
	buffer_out[7] = 0x06;//功能码

	buffer_out[8] = 0x00;//数据区地址
	buffer_out[9] = 0x1F;

	m_Result.GetWindowText(Str);
	int temp = _ttoi(Str);

	buffer_out[10] = (temp >> 8) & 0xFF;//数据区地址
	buffer_out[11] = temp & 0xFF;

	m_SockClient.Send(buffer_out, OUTBUFFERSIZE);
	m_SockClient.Receive(buffer_out, OUTBUFFERSIZE);
	Str.Format("设置结果为：%d \r\n \r\n收到返回码为：0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X 0x%2X",
		temp, buffer_out[0], buffer_out[1], buffer_out[2], buffer_out[3], buffer_out[4], buffer_out[5],
		buffer_out[6], buffer_out[7], buffer_out[8], buffer_out[9], buffer_out[10], buffer_out[11]);
	m_Return.SetWindowText(Str);
}
