// OutputStreamView.cpp : implementation of the COutputStreamView class
//

#include "stdafx.h"
#include "OutputStream.h"

#include "OutputStreamDoc.h"
#include "OutputStreamView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputStreamView
IMPLEMENT_DYNCREATE(COutputStreamView, CView)

BEGIN_MESSAGE_MAP(COutputStreamView, CView)
	//{{AFX_MSG_MAP(COutputStreamView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputStreamView construction/destruction
COutputStreamView::COutputStreamView()
{
	CFile file;
	file.Open("bk.bmp",CFile::modeReadWrite);
	int len = file.GetLength();
	file.Seek(14,CFile::begin);	//位图文件头
	m_pBmpData = new char[len-14];
	file.Read(m_pBmpData,len-14);
	file.Close();
}

COutputStreamView::~COutputStreamView()
{
	delete [] m_pBmpData;
}

BOOL COutputStreamView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COutputStreamView drawing

void COutputStreamView::OnDraw(CDC* pDC)
{
	COutputStreamDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	OutputStream(m_pBmpData);
}

/////////////////////////////////////////////////////////////////////////////
// COutputStreamView printing

BOOL COutputStreamView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COutputStreamView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COutputStreamView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COutputStreamView diagnostics

#ifdef _DEBUG
void COutputStreamView::AssertValid() const
{
	CView::AssertValid();
}

void COutputStreamView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COutputStreamDoc* COutputStreamView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COutputStreamDoc)));
	return (COutputStreamDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutputStreamView message handlers

void COutputStreamView::OutputStream(char *pStream)
{
	/*char *pHeader =pStream ;
	BITMAPINFO BitInfo;
	memset(&BitInfo,0,sizeof(BITMAPINFO));
	memcpy(&BitInfo,pHeader,sizeof(BITMAPINFO));
	int x = BitInfo.bmiHeader.biWidth;
	int y = BitInfo.bmiHeader.biHeight;
	pHeader+=40;
	StretchDIBits(GetDC()->m_hDC,0,0,x,y,0,0,x,y,pHeader,&BitInfo,DIB_RGB_COLORS,SRCCOPY);*/

	
	
	
	
	
	BitInfo.bmiHeader.biSize;
	BitInfo.bmiHeader.biSizeImage;
	BitInfo.bmiHeader.biWidth;
	BitInfo.bmiHeader.biHeight;
	BitInfo.bmiHeader.biPlanes;
	BitInfo.bmiHeader.biBitCount;

	BitInfo.bmiHeader.biCompression;

	BitInfo.bmiHeader.biXPelsPerMeter;
	BitInfo.bmiHeader.biYPelsPerMeter;
	BitInfo.bmiHeader.biClrImportant;
	BitInfo.bmiHeader.biClrUsed;
	
}
