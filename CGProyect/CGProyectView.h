
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
	afx_msg void OnChangeChangebordercolor();
	afx_msg void OnChangeDeletefigure();
	afx_msg void OnChangeDeselectfigure();
	afx_msg void OnChangeFillfigure();
	afx_msg void OnChangeMovetobackground();
	afx_msg void OnChangeMovetoforeground();
	afx_msg void OnChangeBackgroundcolor();
	afx_msg void OnForegroundKey();
	afx_msg void OnBackgroundKey();
	afx_msg void OnDeselectKey();
	afx_msg void OnDeleteKey();
	afx_msg void OnChangeDeteleallfigures();
	afx_msg void OnChangeUnselectfigure();
	afx_msg void OnDeleteOneKey();
	afx_msg void OnChangeNewbeziercurve();
	afx_msg void OnChangeEnterinsertmode();
	afx_msg void OnChangeEntereditmode();
	afx_msg void OnAccelerator32810();
	afx_msg void OnAcceleratorheyi();
	afx_msg void OnAcceleratorkeyi();
	afx_msg void OnAcceleratorkeye();
	afx_msg void OnChangeChangetriangle();
	afx_msg void OnChagectp0();
	afx_msg void OnChagectp1();
	afx_msg void OnChagectp2();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	afx_msg void OnDestroy();
//	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnUpdateButtonCircle(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonBezier(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonEllipse(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonLine(CCmdUI *pCmdUI);
	afx_msg void OnUpdateButtonTriangle(CCmdUI *pCmdUI);
	afx_msg void OnButtonCancel();
	afx_msg void OnDivideBezier();
	afx_msg void OnChangeChangepointcolor();
	afx_msg void OnUpdateButtonImage(CCmdUI *pCmdUI);
	afx_msg void OnButtonImage();
};

#ifndef _DEBUG  // debug version in CGProyectView.cpp
inline CCGProyectDoc* CCGProyectView::GetDocument() const
   { return reinterpret_cast<CCGProyectDoc*>(m_pDocument); }
#endif

