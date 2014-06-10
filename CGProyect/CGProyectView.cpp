
// CGProyectView.cpp : implementation of the CCGProyectView class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CGProyect.h"
#endif

#include "CGProyectDoc.h"
#include "CGProyectView.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCGProyectView

IMPLEMENT_DYNCREATE(CCGProyectView, CView)

BEGIN_MESSAGE_MAP(CCGProyectView, CView)
//	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_BUTTON_BEZIER, &CCGProyectView::OnButtonBezier)
	ON_COMMAND(ID_BUTTON_CIRCLE, &CCGProyectView::OnButtonCircle)
	ON_COMMAND(ID_BUTTON_ELLIPSE, &CCGProyectView::OnButtonEllipse)
	ON_COMMAND(ID_BUTTON_LINE, &CCGProyectView::OnButtonLine)
	ON_COMMAND(ID_BUTTON_TRIANGLE, &CCGProyectView::OnButtonTriangle)
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
//	ON_WM_NOTIFYFORMAT()
ON_WM_RBUTTONDOWN()
END_MESSAGE_MAP()

// CCGProyectView construction/destruction

CCGProyectView::CCGProyectView()
{
	// TODO: add construction code here
	m_current = IM_LINE;
	m_pressed = m_bezier = false;
	m_triangle = 0;

	CMenu *menu = new CMenu;
	menu->CreatePopupMenu();
	// Add items to the menu
	menu->AppendMenu(MF_STRING, 0, "Text");
}

CCGProyectView::~CCGProyectView()
{
}

BOOL CCGProyectView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CCGProyectView drawing

void CCGProyectView::OnDraw(CDC* pDC)
{
	CCGProyectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	for (list<CShape *>::iterator i = pDoc->m_figures.begin(); i!=pDoc->m_figures.end(); i++)
		  (*i)->OnDraw(pDC, m_WindosSize);

	// TODO: add draw code for native data here
}


// CCGProyectView diagnostics

#ifdef _DEBUG
void CCGProyectView::AssertValid() const
{
	CView::AssertValid();
}

void CCGProyectView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCGProyectDoc* CCGProyectView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCGProyectDoc)));
	return (CCGProyectDoc*)m_pDocument;
}
#endif //_DEBUG


// CCGProyectView message handlers


void CCGProyectView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	CCGProyectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	m_pressed =true;
	switch (m_current)
	{
		case IM_CIRCLE:	  {
			CCircle *C = new CCircle;
			C->m_center.x  = C->m_tangente.x = (float)point.x / m_WindosSize.x;
			C->m_center.y  = C->m_tangente.y = (float)point.y / m_WindosSize.y;
			pDoc->m_figures.push_back(C);
			break;
		}
		case IM_LINE:	  {
			CLine *L = new CLine;
			L->m_p1.x = L->m_p2.x = (float)point.x / m_WindosSize.x;
			L->m_p1.y = L->m_p2.y = (float)point.y / m_WindosSize.y;
			pDoc->m_figures.push_back(L);
			break;
		}
		case IM_ELLIPSE:  {
			CEllipse *E = new CEllipse;
			E->m_p1.x = E->m_p2.x = (float)point.x / m_WindosSize.x;
			E->m_p1.y = E->m_p2.y = (float)point.y / m_WindosSize.y;
			pDoc->m_figures.push_back(E);
			break;
		}
		case IM_TRIANGLE:{
			if(m_triangle == 1){
				list<CShape *>::reverse_iterator i = pDoc->m_figures.rbegin();
				((CTriangle *)(*i))->m_p2.x = (float)point.x / m_WindosSize.x;
				((CTriangle *)(*i))->m_p2.y = (float)point.y / m_WindosSize.y;
				m_triangle = 0;
			}else{
				CTriangle *T = new CTriangle;
				T->m_p0.x = T->m_p1.x = T->m_p2.x = (float)point.x / m_WindosSize.x;
				T->m_p0.y = T->m_p1.y = T->m_p2.y = (float)point.y / m_WindosSize.y;
				++m_triangle;
				pDoc->m_figures.push_back(T);
			}
			break;
		}

	}
	Invalidate(1);

	CView::OnLButtonDown(nFlags, point);
}


void CCGProyectView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
		CCGProyectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if ((nFlags & MK_LBUTTON) && m_pressed)
	{
		list<CShape *>::reverse_iterator i = pDoc->m_figures.rbegin();
		switch (m_current)
		{
			case IM_CIRCLE:	{
				((CCircle*)(*i))->m_tangente.x = (float)point.x / m_WindosSize.x;
				((CCircle*)(*i))->m_tangente.y = (float)point.y / m_WindosSize.y;
				break;
			}
			case IM_LINE:	{
				((CLine *)(*i))->m_p2.x = (float)point.x / m_WindosSize.x;
				((CLine *)(*i))->m_p2.y = (float)point.y / m_WindosSize.y;
				break;
			}
			case IM_ELLIPSE:{
				((CEllipse *)(*i))->m_p2.x = (float)point.x / m_WindosSize.x;
				((CEllipse *)(*i))->m_p2.y = (float)point.y / m_WindosSize.y;
				break;
			}
			case IM_TRIANGLE:{
				if(m_triangle == 1){
					((CTriangle *)(*i))->m_p1.x = ((CTriangle *)(*i))->m_p2.x = (float)point.x / m_WindosSize.x;
					((CTriangle *)(*i))->m_p1.y = ((CTriangle *)(*i))->m_p2.y = (float)point.y / m_WindosSize.y;
				}
				break;
			}
		}
		Invalidate(1);
	}
	m_pressed = false;
	CView::OnLButtonUp(nFlags, point);
}


void CCGProyectView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	// TODO: Agregue aquí su código de controlador de mensajes o llame al valor predeterminado
	CCGProyectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if ((nFlags & MK_LBUTTON) && m_pressed)
	{
		list<CShape *>::reverse_iterator i = pDoc->m_figures.rbegin();
		switch (m_current)
		{
			case IM_CIRCLE:	{
				((CCircle*)(*i))->m_tangente.x = (float)point.x / m_WindosSize.x;
				((CCircle*)(*i))->m_tangente.y = (float)point.y / m_WindosSize.y;
				break;
			}
			case IM_LINE:	{
				((CLine *)(*i))->m_p2.x = (float)point.x / m_WindosSize.x;
				((CLine *)(*i))->m_p2.y = (float)point.y / m_WindosSize.y;
				break;
			}
			case IM_ELLIPSE:{
				((CEllipse *)(*i))->m_p2.x = (float)point.x / m_WindosSize.x;
				((CEllipse *)(*i))->m_p2.y = (float)point.y / m_WindosSize.y;
				break;
			}
			case IM_TRIANGLE:{
				if(m_triangle == 1){
					((CTriangle *)(*i))->m_p1.x = ((CTriangle *)(*i))->m_p2.x = (float)point.x / m_WindosSize.x;
					((CTriangle *)(*i))->m_p1.y = ((CTriangle *)(*i))->m_p2.y = (float)point.y / m_WindosSize.y;
				}
				break;
			}
		}
		InvalidateRect(NULL, 1);
	}
	CView::OnMouseMove(nFlags, point);

}


void CCGProyectView::OnButtonBezier()
{
	m_current = IM_BEZIER;
	if(m_triangle == 1){
		GetDocument()->m_figures.pop_back(); 
		Invalidate(1);
	}
}


void CCGProyectView::OnButtonCircle()
{
	m_current = IM_CIRCLE;
	if(m_triangle == 1){
		GetDocument()->m_figures.pop_back(); 
		Invalidate(1);
	}
}


void CCGProyectView::OnButtonEllipse()
{
	m_current = IM_ELLIPSE;
	if(m_triangle == 1){
		GetDocument()->m_figures.pop_back(); 
		Invalidate(1);
	}
}


void CCGProyectView::OnButtonLine()
{
	m_current = IM_LINE;
	if(m_triangle == 1){
		GetDocument()->m_figures.pop_back(); 
		Invalidate(1);
	} 
}


void CCGProyectView::OnButtonTriangle()
{
	m_triangle = 0;
	m_current = IM_TRIANGLE;
}


void CCGProyectView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	m_WindosSize.x = cx;
	m_WindosSize.y = cy;
}

void CCGProyectView::OnContextMenu(CWnd* /*pWnd*/, CPoint point)
{
	CMenu menu;
	menu.LoadMenu(IDR_MAINFRAME);
    CMenu *pSub = menu.GetSubMenu(0);
    // Modify menu items here if necessary (e.g. gray out items)
    int nCmd = pSub->TrackPopupMenu(
        TPM_LEFTALIGN | TPM_RIGHTBUTTON | TPM_VERPOSANIMATION | TPM_RETURNCMD | TPM_NONOTIFY,
        point.x, point.y, AfxGetMainWnd(), NULL);
    if (nCmd)
        SendMessage(WM_COMMAND, nCmd);
}


void CCGProyectView::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CView::OnRButtonDown(nFlags, point);
}



/*
CColorDialog dlg; 
	if (dlg.DoModal() == IDOK) 
	{ 
		COLORREF color = dlg.GetColor(); 

	}
	*/