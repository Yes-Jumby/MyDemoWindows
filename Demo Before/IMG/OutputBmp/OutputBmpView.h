// OutputBmpView.h : interface of the COutputBmpView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTPUTBMPVIEW_H__62611039_F6E9_4669_A6CA_1222EDF1474D__INCLUDED_)
#define AFX_OUTPUTBMPVIEW_H__62611039_F6E9_4669_A6CA_1222EDF1474D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COutputBmpView : public CView
{
protected: // create from serialization only
	COutputBmpView();
	DECLARE_DYNCREATE(COutputBmpView)

// Attributes
public:
	COutputBmpDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputBmpView)
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
	virtual ~COutputBmpView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COutputBmpView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OutputBmpView.cpp
inline COutputBmpDoc* COutputBmpView::GetDocument()
   { return (COutputBmpDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTBMPVIEW_H__62611039_F6E9_4669_A6CA_1222EDF1474D__INCLUDED_)
