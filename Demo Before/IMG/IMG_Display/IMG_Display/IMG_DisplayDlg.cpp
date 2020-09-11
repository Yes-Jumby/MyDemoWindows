
// IMG_DisplayDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IMG_Display.h"
#include "IMG_DisplayDlg.h"
#include "afxdialogex.h"
#include <amp_graphics.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CIMG_DisplayDlg 对话框



CIMG_DisplayDlg::CIMG_DisplayDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_IMG_DISPLAY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIMG_DisplayDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC, m_PIC);
}

BEGIN_MESSAGE_MAP(CIMG_DisplayDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CIMG_DisplayDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CIMG_DisplayDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CIMG_DisplayDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CIMG_DisplayDlg 消息处理程序

BOOL CIMG_DisplayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CIMG_DisplayDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CIMG_DisplayDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CIMG_DisplayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CIMG_DisplayDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	//CDialogEx::OnOK();

	//打开文件
	
	CFile file;
	file.Open(_T("D://WOrks//GlassInspect-client-1.0.3//Pic//back//20180802_1_0000001.bmp"), CFile::modeRead);
	int len = file.GetLength();
	file.Seek(14, CFile::begin);	//位图文件头

	m_pShowBitmapInfo = (BITMAPINFO *) new BYTE[sizeof(BITMAPINFO) + 255 * sizeof(RGBQUAD)];
	int a = sizeof(BITMAPINFO);//44
	int b = sizeof(BITMAPFILEHEADER);//14
	int c = sizeof(BITMAPINFOHEADER);//40
	file.Read(m_pShowBitmapInfo, sizeof(BITMAPFILEHEADER) + 255 * sizeof(RGBQUAD));

	m_pBmpData = new char[len - 14 - sizeof(BITMAPFILEHEADER) - 255 * sizeof(RGBQUAD)];

	file.Read(m_pBmpData, len - 14 - sizeof(BITMAPFILEHEADER) - 255 * sizeof(RGBQUAD));
	file.Close();

	char *pHeader = m_pBmpData;
	
	int x = m_pShowBitmapInfo->bmiHeader.biWidth;
	int y = m_pShowBitmapInfo->bmiHeader.biHeight;

	CRect rect;
	CWnd *pWnd = GetDlgItem(IDC_PIC);//IDC_picture为picture控件ID
	CStatic *pstatic = (CStatic*)pWnd;
	pWnd->GetWindowRect(&rect);//rc为控件的大小。
	int x_pic = rect.Width();
	int y_pic = rect.Height();
	int x1 = rect.left;//587
	int y1 = rect.top;//245
	m_PIC.MoveWindow(200,60, x_pic, x_pic*y/x);

	StretchDIBits(pstatic->GetDC()->m_hDC, 0, 0, x_pic, x_pic*y / x, 0, 0, x, y, pHeader, m_pShowBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	
}


void CIMG_DisplayDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	delete[] m_pBmpData;
	delete[] m_pShowBitmapInfo;
	CDialogEx::OnCancel();
}


void CIMG_DisplayDlg::OnBnClickedButton1()
{
	CFile file;
	BITMAPFILEHEADER FILE_HEADER; //文件头
	BITMAPINFOHEADER INFO_HEADER; //信息头
	file.Open(_T("D://WOrks//GlassInspect-client-1.0.3//Pic//back//20180802_1_0000001.bmp"), CFile::modeRead);

	file.Read(&FILE_HEADER, sizeof(BITMAPFILEHEADER));
	if (FILE_HEADER.bfType != 0x4d42)
	{
		file.Close();
		MessageBox(_T("原图象不为BMP图象！"));
		return;
	}

	file.Read(&INFO_HEADER, sizeof(BITMAPINFOHEADER));

	// 调色板数目
	int numQuad = 0;
	if (INFO_HEADER.biBitCount < 24)
	{
		numQuad = 1 << INFO_HEADER.biBitCount; //1右移?位 = 2的?次方
	}

	BITMAPINFO *pBMP_INFO = (BITMAPINFO*)HeapAlloc(GetProcessHeap(), 0,
		sizeof(BITMAPINFOHEADER) + numQuad * sizeof(RGBQUAD));
	memcpy(pBMP_INFO, &INFO_HEADER, sizeof(BITMAPINFOHEADER));
	RGBQUAD *quad = (RGBQUAD*)((BYTE*)pBMP_INFO + sizeof(BITMAPINFOHEADER));
	if (numQuad != 0)
	{
		file.Read(quad, sizeof(RGBQUAD) * numQuad);
	}

	int sizeBuf = FILE_HEADER.bfSize - FILE_HEADER.bfOffBits;
	BYTE *bmpBuf = new BYTE[sizeBuf];
	file.Read(bmpBuf, sizeBuf);
	file.Close();

	int x = INFO_HEADER.biWidth;
	int y = INFO_HEADER.biHeight;

	CRect rect;
	CWnd *pWnd = GetDlgItem(IDC_PIC);//IDC_picture为picture控件ID
	CStatic *pstatic = (CStatic*)pWnd;
	pWnd->GetWindowRect(&rect);//rc为控件的大小。
	int x_pic = rect.Width();
	int y_pic = rect.Height();
	int x1 = rect.left;//587
	int y1 = rect.top;//245
	m_PIC.MoveWindow(200, 60, x_pic, x_pic*y / x);

	StretchDIBits(pstatic->GetDC()->m_hDC, 0, 0, x_pic, x_pic*y / x, 0, 0, x, y, bmpBuf, pBMP_INFO, DIB_RGB_COLORS, SRCCOPY);
	
}
