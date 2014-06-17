
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
ON_WM_RBUTTONDOWN()
ON_COMMAND(ID_CHANGE_CHANGEBORDERCOLOR, &CCGProyectView::OnChangeChangebordercolor)
ON_COMMAND(ID_CHANGE_DELETEFIGURE, &CCGProyectView::OnChangeDeletefigure)
ON_COMMAND(ID_CHANGE_FILLFIGURE, &CCGProyectView::OnChangeFillfigure)
ON_COMMAND(ID_CHANGE_MOVETOBACKGROUND, &CCGProyectView::OnChangeMovetobackground)
ON_COMMAND(ID_CHANGE_MOVETOFOREGROUND, &CCGProyectView::OnChangeMovetoforeground)
ON_COMMAND(ID_CHANGE_BACKGROUNDCOLOR, &CCGProyectView::OnChangeBackgroundcolor)
ON_COMMAND(ID_FOREGROUND_KEY, &CCGProyectView::OnForegroundKey)
ON_COMMAND(ID_BACKGROUND_KEY, &CCGProyectView::OnBackgroundKey)
ON_COMMAND(ID_DESELECT_KEY, &CCGProyectView::OnDeselectKey)
ON_COMMAND(ID_DELETE_KEY, &CCGProyectView::OnDeleteKey)
ON_COMMAND(ID_CHANGE_DETELEALLFIGURES, &CCGProyectView::OnChangeDeteleallfigures)
ON_COMMAND(ID_CHANGE_UNSELECTFIGURE, &CCGProyectView::OnChangeUnselectfigure)
ON_COMMAND(ID_DELETE_ONE_KEY, &CCGProyectView::OnDeleteOneKey)
ON_COMMAND(ID_CHANGE_NEWBEZIERCURVE, &CCGProyectView::OnChangeNewbeziercurve)
ON_COMMAND(ID_CHANGE_ENTERINSERTMODE, &CCGProyectView::OnChangeEnterinsertmode)
ON_COMMAND(ID_CHANGE_ENTEREDITMODE, &CCGProyectView::OnChangeEntereditmode)
ON_COMMAND(ID_ACCELERATORKEYI, &CCGProyectView::OnAcceleratorkeyi)
ON_COMMAND(ID_ACCELERATORKEYE, &CCGProyectView::OnAcceleratorkeye)
END_MESSAGE_MAP()

// CCGProyectView construction/destruction

CCGProyectView::CCGProyectView()
{
	
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
	for (std::vector<CShape *>::iterator i = pDoc->m_figures.begin(); i!=pDoc->m_figures.end(); i++)
		(*i)->OnDraw(pDC, pDoc->m_WindosSize);


	if(pDoc->position != pDoc->m_figures.end())
		(*pDoc->position)->DrawSelected(pDC,pDoc->m_WindosSize);

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
	CCGProyectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	pDoc->m_pressed =true;

	if(pDoc->m_insertmode){
		switch (pDoc->m_current)
		{
			case IM_CIRCLE:	  {
				CCircle *C = new CCircle;
				C->m_center.x  = C->m_tangente.x = (float)point.x / pDoc->m_WindosSize.x;
				C->m_center.y  = C->m_tangente.y = (float)point.y / pDoc->m_WindosSize.y;
				pDoc->m_figures.push_back(C);
				pDoc->position = pDoc->m_figures.begin() + pDoc->m_figures.size() - 1;
				break;
			}
			case IM_LINE:	  {
				CLine *L = new CLine;
				L->m_p1.x = L->m_p2.x = (float)point.x / pDoc->m_WindosSize.x;
				L->m_p1.y = L->m_p2.y = (float)point.y / pDoc->m_WindosSize.y;
				pDoc->m_figures.push_back(L);
				pDoc->position = pDoc->m_figures.begin() + pDoc->m_figures.size() - 1;
				break;
			}
			case IM_ELLIPSE:  {
				CEllipse *E = new CEllipse;
				E->m_p1.x = E->m_p2.x = (float)point.x / pDoc->m_WindosSize.x;
				E->m_p1.y = E->m_p2.y = (float)point.y / pDoc->m_WindosSize.y;
				pDoc->m_figures.push_back(E);
				pDoc->position = pDoc->m_figures.begin() + pDoc->m_figures.size() - 1;
				break;
			}
			case IM_TRIANGLE:{
				if(pDoc->m_triangle == 1){
					std::vector<CShape *>::reverse_iterator i = pDoc->m_figures.rbegin();
					((CTriangle *)(*i))->m_p2.x = (float)point.x / pDoc->m_WindosSize.x;
					((CTriangle *)(*i))->m_p2.y = (float)point.y / pDoc->m_WindosSize.y;
					pDoc->m_triangle = 0;
				}else{
					CTriangle *T = new CTriangle;
					T->m_p0.x = T->m_p1.x = T->m_p2.x = (float)point.x / pDoc->m_WindosSize.x;
					T->m_p0.y = T->m_p1.y = T->m_p2.y = (float)point.y / pDoc->m_WindosSize.y;
					++pDoc->m_triangle;
					pDoc->m_figures.push_back(T);
					pDoc->position = pDoc->m_figures.begin() + pDoc->m_figures.size() - 1;
				}
				break;
			}
			case IM_BEZIER:  {
				CBezier *B = new CBezier;
				B->arr[0][0].x = B->arr[0][1].x = (float)point.x / pDoc->m_WindosSize.x;
				B->arr[0][0].y = B->arr[0][1].y = (float)point.y / pDoc->m_WindosSize.y;
				pDoc->m_figures.push_back(B);
				pDoc->position = pDoc->m_figures.begin() + pDoc->m_figures.size() - 1;
				break;
			}

		}
		Invalidate(1);
	}else{
		if ((nFlags & MK_CONTROL) && pDoc->position != pDoc->m_figures.end()){
			 pDoc->m_initialPoint = point;
		}else{
			CPOINT2F p;
			p.x = (float)point.x / pDoc->m_WindosSize.x;
			p.y = (float)point.y / pDoc->m_WindosSize.y;

			bool found = false;

			if(pDoc->position != pDoc->m_figures.end()){
				
			}

			if(!found){
				for (std::vector<CShape *>::iterator i = pDoc->m_figures.begin(); i!=pDoc->m_figures.end(); i++){
					if((*i)->Intersect(p)){
						pDoc->position = i;
					}
				}
			}
		}

		Invalidate(1);
		/*if(pDoc->position != pDoc->m_figures.end())
			(*pDoc->position)->DrawSelected(pDC,pDoc->m_WindosSize);*/
	}

	CView::OnLButtonDown(nFlags, point);
}


void CCGProyectView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CCGProyectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if(pDoc->m_insertmode){
		if ((nFlags & MK_LBUTTON) && pDoc->m_pressed)
		{
			std::vector<CShape *>::reverse_iterator i = pDoc->m_figures.rbegin();
			switch (pDoc->m_current)
			{
				case IM_CIRCLE:	{
					((CCircle*)(*i))->m_tangente.x = (float)point.x / pDoc->m_WindosSize.x;
					((CCircle*)(*i))->m_tangente.y = (float)point.y / pDoc->m_WindosSize.y;
					break;
				}
				case IM_LINE:	{
					((CLine *)(*i))->m_p2.x = (float)point.x / pDoc->m_WindosSize.x;
					((CLine *)(*i))->m_p2.y = (float)point.y / pDoc->m_WindosSize.y;
					break;
				}
				case IM_ELLIPSE:{
					((CEllipse *)(*i))->m_p2.x = (float)point.x / pDoc->m_WindosSize.x;
					((CEllipse *)(*i))->m_p2.y = (float)point.y / pDoc->m_WindosSize.y;
					break;
				}
				case IM_TRIANGLE:{
					if(pDoc->m_triangle == 1){
						((CTriangle *)(*i))->m_p1.x = ((CTriangle *)(*i))->m_p2.x = (float)point.x / pDoc->m_WindosSize.x;
						((CTriangle *)(*i))->m_p1.y = ((CTriangle *)(*i))->m_p2.y = (float)point.y / pDoc->m_WindosSize.y;
					}
					break;
				}
				case IM_BEZIER:  {
					((CBezier *)(*i))->arr[0][1].x = (float)point.x / pDoc->m_WindosSize.x;
					((CBezier *)(*i))->arr[0][1].y = (float)point.y / pDoc->m_WindosSize.y;
					break;
				}
			}
			Invalidate(1);
		}
		
	}else{
		if ((nFlags & MK_CONTROL) && (nFlags & MK_LBUTTON)  && pDoc->position != pDoc->m_figures.end()){
			
			CPOINT2F p;

			 p.x = (float)(point.x - pDoc->m_initialPoint.x) / pDoc->m_WindosSize.x;
			 p.y = (float)(point.y - pDoc->m_initialPoint.y) / pDoc->m_WindosSize.y;

			 (*pDoc->position)->Translate(p);

			 pDoc->m_initialPoint = point;
			 Invalidate(1);
		}
	}

	pDoc->m_pressed = false;

	
	CView::OnLButtonUp(nFlags, point);
}


void CCGProyectView::OnMouseMove(UINT nFlags, CPoint point)
{
	CCGProyectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	if(pDoc->m_insertmode){
		if ((nFlags & MK_LBUTTON) && pDoc->m_pressed)
		{
			std::vector<CShape *>::reverse_iterator i = pDoc->m_figures.rbegin();
			switch (pDoc->m_current)
			{
				case IM_CIRCLE:	{
					((CCircle*)(*i))->m_tangente.x = (float)point.x / pDoc->m_WindosSize.x;
					((CCircle*)(*i))->m_tangente.y = (float)point.y / pDoc->m_WindosSize.y;
					break;
				}
				case IM_LINE:	{
					((CLine *)(*i))->m_p2.x = (float)point.x / pDoc->m_WindosSize.x;
					((CLine *)(*i))->m_p2.y = (float)point.y / pDoc->m_WindosSize.y;
					break;
				}
				case IM_ELLIPSE:{
					((CEllipse *)(*i))->m_p2.x = (float)point.x / pDoc->m_WindosSize.x;
					((CEllipse *)(*i))->m_p2.y = (float)point.y / pDoc->m_WindosSize.y;
					break;
				}
				case IM_TRIANGLE:{
					if(pDoc->m_triangle == 1){
						((CTriangle *)(*i))->m_p1.x = ((CTriangle *)(*i))->m_p2.x = (float)point.x / pDoc->m_WindosSize.x;
						((CTriangle *)(*i))->m_p1.y = ((CTriangle *)(*i))->m_p2.y = (float)point.y / pDoc->m_WindosSize.y;
					}
					break;
				}
				case IM_BEZIER:  {
					((CBezier *)(*i))->arr[0][1].x = (float)point.x / pDoc->m_WindosSize.x;
					((CBezier *)(*i))->arr[0][1].y = (float)point.y / pDoc->m_WindosSize.y;
					break;
				}
			}
			Invalidate(1);
		}
	}else{
		if ((nFlags & MK_CONTROL) && (nFlags & MK_LBUTTON)  && pDoc->position != pDoc->m_figures.end()){
			
			CPOINT2F p;

			 p.x = (float)(point.x - pDoc->m_initialPoint.x) / pDoc->m_WindosSize.x;
			 p.y = (float)(point.y - pDoc->m_initialPoint.y) / pDoc->m_WindosSize.y;

			 (*pDoc->position)->Translate(p);

			 pDoc->m_initialPoint = point;
			 Invalidate(1);
		}

	}

	

	CView::OnMouseMove(nFlags, point);

}


void CCGProyectView::OnButtonBezier()
{
	CCGProyectDoc* pDoc = GetDocument();
	pDoc->m_current = IM_BEZIER;
}


void CCGProyectView::OnButtonCircle()
{
	CCGProyectDoc* pDoc = GetDocument();
	pDoc->m_current = IM_CIRCLE;
}


void CCGProyectView::OnButtonEllipse()
{
	CCGProyectDoc* pDoc = GetDocument();
	pDoc->m_current = IM_ELLIPSE;
}


void CCGProyectView::OnButtonLine()
{
	CCGProyectDoc* pDoc = GetDocument();
	pDoc->m_current = IM_LINE;
}


void CCGProyectView::OnButtonTriangle()
{
	CCGProyectDoc* pDoc = GetDocument();
	pDoc->m_triangle = 0;
	pDoc->m_current = IM_TRIANGLE;
}


void CCGProyectView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CCGProyectDoc* pDoc = GetDocument();
	pDoc->m_WindosSize.x = cx;
	pDoc->m_WindosSize.y = cy;
}

void CCGProyectView::OnContextMenu(CWnd * pWnd, CPoint point)
{
	CCGProyectDoc* pDoc = GetDocument();
	
	CMenu menu;
	if(pDoc->m_insertmode){
		menu.LoadMenu(IDR_MENU3);
	}else{
		if(pDoc->position != pDoc->m_figures.end() && (*pDoc->position)->GetID() == IM_BEZIER)	menu.LoadMenu(IDR_MENU2);
		else																					menu.LoadMenu(IDR_MENU1);
	}
    CMenu *pSub = menu.GetSubMenu(0);
    // Modify menu items here if necessary (e.g. gray out items)
    int nCmd = pSub->TrackPopupMenuEx(
        TPM_LEFTALIGN | TPM_LEFTBUTTON,
        point.x, point.y, this, NULL);

	//m_lastClick = point;

}


void CCGProyectView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CView::OnRButtonDown(nFlags, point);
}

//Change the border color
void CCGProyectView::OnChangeChangebordercolor()
{

	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		COLORREF color;
		CColorDialog dlg; 
		if (dlg.DoModal() == IDOK){
			color = dlg.GetColor(); 
			(*pDoc->position)->ChangeLineColor(color);
			Invalidate(1);
		}
	}
}

//Change background color
void CCGProyectView::OnChangeBackgroundcolor()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		COLORREF color;
		CColorDialog dlg; 
		if (dlg.DoModal() == IDOK){
			color = dlg.GetColor(); 
			(*pDoc->position)->ChangeFillColor(color);
			Invalidate(1);
		}
	}
}

//Delete only one figure
void CCGProyectView::OnChangeDeletefigure()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		pDoc->position = pDoc->m_figures.erase(pDoc->position);
		Invalidate(1);
	}
}

//Change if a figure is filled
void CCGProyectView::OnChangeFillfigure()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		(*pDoc->position)->ChangeFilled();
		Invalidate(1);
	}
}

//Move a figure to background
void CCGProyectView::OnChangeMovetobackground()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		std::vector<CShape *>::iterator it = pDoc->position;
		if(it != pDoc->m_figures.begin()){
			std::swap(*pDoc->position, *(--it));
			pDoc->position = it;
			Invalidate(1);
		}
	}
}

//Move a figure to foreground
void CCGProyectView::OnChangeMovetoforeground()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		std::vector<CShape *>::iterator it = pDoc->position;
		if(++it != pDoc->m_figures.end()){
			std::swap(*pDoc->position, *(it));
			pDoc->position = it;
			Invalidate(1);
		}
	}
}


//F Key
void CCGProyectView::OnForegroundKey()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		std::vector<CShape *>::iterator it = pDoc->position;
		if(++it != pDoc->m_figures.end()){
			std::swap(*pDoc->position, *(it));
			pDoc->position = it;
			Invalidate(1);
		}
	}
}

//B Key
void CCGProyectView::OnBackgroundKey()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		std::vector<CShape *>::iterator it = pDoc->position;
		if(it != pDoc->m_figures.begin()){
			std::swap(*pDoc->position, *(--it));
			pDoc->position = it;
			Invalidate(1);
		}
	}
}

//U Key
void CCGProyectView::OnDeselectKey()
{
	CCGProyectDoc* pDoc = GetDocument();
	pDoc->position = pDoc->m_figures.end();
	Invalidate(1);
}

//Control + delete
void CCGProyectView::OnDeleteKey()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(!pDoc->m_figures.empty()){
		pDoc->m_figures.clear();
		pDoc->position = pDoc->m_figures.begin();
		Invalidate(1);
	}
}

//Delete all figures
void CCGProyectView::OnChangeDeteleallfigures()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(!pDoc->m_figures.empty()){
		pDoc->m_figures.clear();
		pDoc->position = pDoc->m_figures.begin();
		Invalidate(1);
	}
}

//Unselect a figure
void CCGProyectView::OnChangeUnselectfigure()
{
	CCGProyectDoc* pDoc = GetDocument();
	pDoc->position = pDoc->m_figures.end();
	Invalidate(1);
}

//Delete only one figure
void CCGProyectView::OnDeleteOneKey()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		pDoc->position = pDoc->m_figures.erase(pDoc->position);
		Invalidate(1);
	}
}


//Elevate the degree of the bezier curve
void CCGProyectView::OnChangeNewbeziercurve()
{

	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_BEZIER){
			((CBezier*)(*pDoc->position))->addControlpoint(0,0);
		}
	}
}


void CCGProyectView::OnChangeEnterinsertmode()
{
	CCGProyectDoc* pDoc = GetDocument();
	pDoc->m_insertmode = true;
}


void CCGProyectView::OnChangeEntereditmode()
{
	CCGProyectDoc* pDoc = GetDocument();
	pDoc->m_insertmode = false;
}

//I Key
void CCGProyectView::OnAcceleratorkeyi()
{
	CCGProyectDoc* pDoc = GetDocument();
	pDoc->m_insertmode = true;
}

//E Key
void CCGProyectView::OnAcceleratorkeye()
{
	CCGProyectDoc* pDoc = GetDocument();
	pDoc->m_insertmode = false;
}
