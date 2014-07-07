
// CGProyectDoc.h : interface of the CCGProyectDoc class
//


#pragma once

#include <vector>
#include <iostream>

#include "Circle.h"
#include "Ellipse.h"
#include "Line.h"
#include "Triangle.h"
#include "Bezier.h"
#include "CGProyect.h"
#include "MainFrm.h"

class CCGProyectDoc : public CDocument
{
protected: // create from serialization only
	CCGProyectDoc();
	DECLARE_DYNCREATE(CCGProyectDoc)

// Attributes
public:

// Operations
public:
	std::vector<CShape *> m_figures;
	int m_current;
	POINT m_WindosSize, m_initialPoint;
	bool m_pressed, m_bezier;
	CPOINT2F* m_selectedPoint;
	std::vector<CShape *>::iterator position;
	int m_triangle;
	CToolBar* m_pToolBar;
	CMainFrame* m_pFrame;

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CCGProyectDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
