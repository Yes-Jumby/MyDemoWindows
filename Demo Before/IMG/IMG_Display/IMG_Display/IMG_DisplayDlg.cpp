
// IMG_DisplayDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "IMG_Display.h"
#include "IMG_DisplayDlg.h"
#include "afxdialogex.h"
#include <amp_graphics.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CIMG_DisplayDlg �Ի���



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


// CIMG_DisplayDlg ��Ϣ�������

BOOL CIMG_DisplayDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CIMG_DisplayDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CIMG_DisplayDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CIMG_DisplayDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//CDialogEx::OnOK();

	//���ļ�
	
	CFile file;
	file.Open(_T("D://WOrks//GlassInspect-client-1.0.3//Pic//back//20180802_1_0000001.bmp"), CFile::modeRead);
	int len = file.GetLength();
	file.Seek(14, CFile::begin);	//λͼ�ļ�ͷ

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
	CWnd *pWnd = GetDlgItem(IDC_PIC);//IDC_pictureΪpicture�ؼ�ID
	CStatic *pstatic = (CStatic*)pWnd;
	pWnd->GetWindowRect(&rect);//rcΪ�ؼ��Ĵ�С��
	int x_pic = rect.Width();
	int y_pic = rect.Height();
	int x1 = rect.left;//587
	int y1 = rect.top;//245
	m_PIC.MoveWindow(200,60, x_pic, x_pic*y/x);

	StretchDIBits(pstatic->GetDC()->m_hDC, 0, 0, x_pic, x_pic*y / x, 0, 0, x, y, pHeader, m_pShowBitmapInfo, DIB_RGB_COLORS, SRCCOPY);
	
}


void CIMG_DisplayDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	delete[] m_pBmpData;
	delete[] m_pShowBitmapInfo;
	CDialogEx::OnCancel();
}


void CIMG_DisplayDlg::OnBnClickedButton1()
{
	CFile file;
	BITMAPFILEHEADER FILE_HEADER; //�ļ�ͷ
	BITMAPINFOHEADER INFO_HEADER; //��Ϣͷ
	file.Open(_T("D://WOrks//GlassInspect-client-1.0.3//Pic//back//20180802_1_0000001.bmp"), CFile::modeRead);

	file.Read(&FILE_HEADER, sizeof(BITMAPFILEHEADER));
	if (FILE_HEADER.bfType != 0x4d42)
	{
		file.Close();
		MessageBox(_T("ԭͼ��ΪBMPͼ��"));
		return;
	}

	file.Read(&INFO_HEADER, sizeof(BITMAPINFOHEADER));

	// ��ɫ����Ŀ
	int numQuad = 0;
	if (INFO_HEADER.biBitCount < 24)
	{
		numQuad = 1 << INFO_HEADER.biBitCount; //1����?λ = 2��?�η�
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
	CWnd *pWnd = GetDlgItem(IDC_PIC);//IDC_pictureΪpicture�ؼ�ID
	CStatic *pstatic = (CStatic*)pWnd;
	pWnd->GetWindowRect(&rect);//rcΪ�ؼ��Ĵ�С��
	int x_pic = rect.Width();
	int y_pic = rect.Height();
	int x1 = rect.left;//587
	int y1 = rect.top;//245
	m_PIC.MoveWindow(200, 60, x_pic, x_pic*y / x);

	StretchDIBits(pstatic->GetDC()->m_hDC, 0, 0, x_pic, x_pic*y / x, 0, 0, x, y, bmpBuf, pBMP_INFO, DIB_RGB_COLORS, SRCCOPY);
	
}
