// OutputStreamDoc.cpp : implementation of the COutputStreamDoc class
//

#include "stdafx.h"
#include "OutputStream.h"

#include "OutputStreamDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COutputStreamDoc

IMPLEMENT_DYNCREATE(COutputStreamDoc, CDocument)

BEGIN_MESSAGE_MAP(COutputStreamDoc, CDocument)
	//{{AFX_MSG_MAP(COutputStreamDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputStreamDoc construction/destruction

COutputStreamDoc::COutputStreamDoc()
{
	// TODO: add one-time construction code here

}

COutputStreamDoc::~COutputStreamDoc()
{
}

BOOL COutputStreamDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COutputStreamDoc serialization

void COutputStreamDoc::Serialize(CArchive& ar)
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
// COutputStreamDoc diagnostics

#ifdef _DEBUG
void COutputStreamDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COutputStreamDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COutputStreamDoc commands
