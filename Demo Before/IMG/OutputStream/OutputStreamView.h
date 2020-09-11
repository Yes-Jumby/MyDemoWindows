// OutputStreamView.h : interface of the COutputStreamView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTPUTSTREAMVIEW_H__B76D0BE5_2441_43CA_815E_66B304BAD9B6__INCLUDED_)
#define AFX_OUTPUTSTREAMVIEW_H__B76D0BE5_2441_43CA_815E_66B304BAD9B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COutputStreamView : public CView
{
protected: // create from serialization only
	COutputStreamView();
	DECLARE_DYNCREATE(COutputStreamView)

// Attributes
public:
	COutputStreamDoc* GetDocument();
	char *m_pBmpData;
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputStreamView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	void OutputStream(char *pStream);
	virtual ~COutputStreamView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COutputStreamView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OutputStreamView.cpp
inline COutputStreamDoc* COutputStreamView::GetDocument()
   { return (COutputStreamDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTSTREAMVIEW_H__B76D0BE5_2441_43CA_815E_66B304BAD9B6__INCLUDED_)
