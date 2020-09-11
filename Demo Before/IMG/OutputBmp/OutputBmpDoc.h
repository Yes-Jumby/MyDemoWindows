// OutputBmpDoc.h : interface of the COutputBmpDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTPUTBMPDOC_H__975D2373_B278_4283_A593_8C971D999650__INCLUDED_)
#define AFX_OUTPUTBMPDOC_H__975D2373_B278_4283_A593_8C971D999650__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COutputBmpDoc : public CDocument
{
protected: // create from serialization only
	COutputBmpDoc();
	DECLARE_DYNCREATE(COutputBmpDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputBmpDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutputBmpDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COutputBmpDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTBMPDOC_H__975D2373_B278_4283_A593_8C971D999650__INCLUDED_)
