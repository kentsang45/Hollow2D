
// Editor2DView.h : interface of the CEditor2DView class
//

#pragma once


class CEditor2DView : public CView
{
protected: // create from serialization only
	CEditor2DView() noexcept;
	DECLARE_DYNCREATE(CEditor2DView)

// Attributes
public:
	CEditor2DDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CEditor2DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
public:
	virtual void OnInitialUpdate();
	afx_msg void OnDestroy();



};

#ifndef _DEBUG  // debug version in Editor2DView.cpp
inline CEditor2DDoc* CEditor2DView::GetDocument() const
   { return reinterpret_cast<CEditor2DDoc*>(m_pDocument); }
#endif

