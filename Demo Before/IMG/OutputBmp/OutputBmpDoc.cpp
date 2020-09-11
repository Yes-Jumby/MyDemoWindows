// OutputBmpDoc.cpp : implementation of the COutputBmpDoc class
//

#include "stdafx.h"
#include "OutputBmp.h"

#include "OutputBmpDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputBmpDoc

IMPLEMENT_DYNCREATE(COutputBmpDoc, CDocument)

BEGIN_MESSAGE_MAP(COutputBmpDoc, CDocument)
	//{{AFX_MSG_MAP(COutputBmpDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputBmpDoc construction/destruction

COutputBmpDoc::COutputBmpDoc()
{
	// TODO: add one-time construction code here

}

COutputBmpDoc::~COutputBmpDoc()
{
}

BOOL COutputBmpDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COutputBmpDoc serialization

void COutputBmpDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// COutputBmpDoc diagnostics

#ifdef _DEBUG
void COutputBmpDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COutputBmpDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutputBmpDoc commands
