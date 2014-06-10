
// CGProyectView.h : interface of the CCGProyectView class
//

#pragma once



class CCGProyectView : public CView
{
protected: // create from serialization only
	CCGProyectView();
	DECLARE_DYNCREATE(CCGProyectView)

// Attributes
public:
	CCGProyectDoc* GetDocument() const;
	int m_current, m_selected;
	POINT m_WindosSize;
	bool m_pressed, m_bezier;
	int m_triangle;
	COLORREF m_Color;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CCGProyectView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnButtonBezier();
	afx_msg void OnButtonCircle();
	afx_msg void OnButtonEllipse();
	afx_msg void OnButtonLine();
	afx_msg void OnButtonTriangle();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in CGProyectView.cpp
inline CCGProyectDoc* CCGProyectView::GetDocument() const
   { return reinterpret_cast<CCGProyectDoc*>(m_pDocument); }
#endif

