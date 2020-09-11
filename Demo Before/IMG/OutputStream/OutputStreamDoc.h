// OutputStreamDoc.h : interface of the COutputStreamDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OUTPUTSTREAMDOC_H__12810145_2BCE_444D_AF01_114D24A8B5D6__INCLUDED_)
#define AFX_OUTPUTSTREAMDOC_H__12810145_2BCE_444D_AF01_114D24A8B5D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class COutputStreamDoc : public CDocument
{
protected: // create from serialization only
	COutputStreamDoc();
	DECLARE_DYNCREATE(COutputStreamDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COutputStreamDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COutputStreamDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COutputStreamDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OUTPUTSTREAMDOC_H__12810145_2BCE_444D_AF01_114D24A8B5D6__INCLUDED_)
