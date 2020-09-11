// OutputBmpView.cpp : implementation of the COutputBmpView class
//

#include "stdafx.h"
#include "OutputBmp.h"

#include "OutputBmpDoc.h"
#include "OutputBmpView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBmpView

IMPLEMENT_DYNCREATE(COutputBmpView, CView)

BEGIN_MESSAGE_MAP(COutputBmpView, CView)
	//{{AFX_MSG_MAP(COutputBmpView)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputBmpView construction/destruction

COutputBmpView::COutputBmpView()
{
	// TODO: add construction code here

}

COutputBmpView::~COutputBmpView()
{
}

BOOL COutputBmpView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// COutputBmpView drawing

void COutputBmpView::OnDraw(CDC* pDC)
{
	COutputBmpDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);
	CBitmap bmp;
	bmp.LoadBitmap(IDB_BKBITMAP);
	memDC.SelectObject(&bmp);
	pDC->BitBlt(30,20,180,180,&memDC,1,1,SRCCOPY);

	
	CRect rc(30,20,210,200);
	CBrush brush(RGB(0,0,0));
	pDC->FrameRect(rc,&brush);
	
	rc.OffsetRect(220,0);

	BITMAP BitInfo;
	bmp.GetBitmap(&BitInfo);
	int x = BitInfo.bmWidth;
	int y = BitInfo.bmHeight;
	pDC->StretchBlt(rc.left,rc.top,rc.Width(),rc.Height(),&memDC,0,0,x,y,SRCCOPY);
	pDC->FrameRect(rc,&brush);
	brush.DeleteObject();
	memDC.DeleteDC();
	bmp.DeleteObject();
}

/////////////////////////////////////////////////////////////////////////////
// COutputBmpView printing

BOOL COutputBmpView::OnPreparePrinting(CPrintInfo* pInfo)
{
	return DoPreparePrinting(pInfo);
}

void COutputBmpView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COutputBmpView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// COutputBmpView diagnostics

#ifdef _DEBUG
void COutputBmpView::AssertValid() const
{
	CView::AssertValid();
}

void COutputBmpView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COutputBmpDoc* COutputBmpView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COutputBmpDoc)));
	return (COutputBmpDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutputBmpView message handlers
