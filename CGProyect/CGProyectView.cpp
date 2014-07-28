
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
#include <fstream>


CBackBuffer *bb;

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
ON_WM_ERASEBKGND()
ON_WM_ACTIVATE()
ON_WM_DESTROY()
//ON_WM_CREATE()
ON_WM_CREATE()
ON_UPDATE_COMMAND_UI(ID_BUTTON_CIRCLE, &CCGProyectView::OnUpdateButtonCircle)
ON_UPDATE_COMMAND_UI(ID_BUTTON_BEZIER, &CCGProyectView::OnUpdateButtonBezier)
ON_UPDATE_COMMAND_UI(ID_BUTTON_ELLIPSE, &CCGProyectView::OnUpdateButtonEllipse)
ON_UPDATE_COMMAND_UI(ID_BUTTON_LINE, &CCGProyectView::OnUpdateButtonLine)
ON_UPDATE_COMMAND_UI(ID_BUTTON_TRIANGLE, &CCGProyectView::OnUpdateButtonTriangle)
ON_COMMAND(ID_BUTTON_CANCEL, &CCGProyectView::OnButtonCancel)
ON_COMMAND(ID_DIVIDE_BEZIER, &CCGProyectView::OnDivideBezier)
ON_COMMAND(ID_CHANGE_CHANGEPOINTCOLOR, &CCGProyectView::OnChangeChangepointcolor)
ON_UPDATE_COMMAND_UI(ID_BUTTON_IMAGE, &CCGProyectView::OnUpdateButtonImage)
ON_COMMAND(ID_BUTTON_IMAGE, &CCGProyectView::OnButtonImage)
ON_COMMAND(ID_BOX_3X3FILTER, &CCGProyectView::OnBox3x3filter)
ON_COMMAND(ID_BOX_5X5FILTER, &CCGProyectView::OnBox5x5filter)
ON_COMMAND(ID_BOX_7X7FILTER, &CCGProyectView::OnBox7x7filter)
ON_COMMAND(ID_GAUSSIAN_3X3, &CCGProyectView::OnGaussian3x3)
ON_COMMAND(ID_GAUSSIAN_5X5FILTER, &CCGProyectView::OnGaussian5x5filter)
ON_COMMAND(ID_GAUSSIAN_7X7FILTER, &CCGProyectView::OnGaussian7x7filter)
ON_COMMAND(ID_MEDIAN_3X3FILTER, &CCGProyectView::OnMedian3x3filter)
ON_COMMAND(ID_MEDIAN_5X5FILTER, &CCGProyectView::OnMedian5x5filter)
ON_COMMAND(ID_MEDIAN_7X7FILTER, &CCGProyectView::OnMedian7x7filter)
ON_COMMAND(ID_MIN_3X3FILTER, &CCGProyectView::OnMin3x3filter)
ON_COMMAND(ID_MIN_5X5FILTER, &CCGProyectView::OnMin5x5filter)
ON_COMMAND(ID_MIN_7X7FILTER, &CCGProyectView::OnMin7x7filter)
ON_COMMAND(ID_MAX_3X3FILTER, &CCGProyectView::OnMax3x3filter)
ON_COMMAND(ID_MAX_5X5FILTER, &CCGProyectView::OnMax5x5filter)
ON_COMMAND(ID_MAX_7X7FILTER, &CCGProyectView::OnMax7x7filter)
ON_COMMAND(ID_APLLYFILTER_LAPLACE, &CCGProyectView::OnApllyfilterLaplace)
ON_COMMAND(ID_APLLYFILTER_SHARPEN, &CCGProyectView::OnApllyfilterSharpen)
END_MESSAGE_MAP()

// CCGProyectView construction/destruction

CCGProyectView::CCGProyectView()
{
	
	CMenu *menu = new CMenu;
	menu->CreatePopupMenu();
	// Add items to the menu
	menu->AppendMenu(MF_STRING, 0, "Text");
	bb = NULL;

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
	

	if(bb != NULL){
		//Clear Back buffer
		bb->Clear();
		

		//Display all figures
		for (std::vector<CShape *>::iterator i = pDoc->m_figures.begin(); i!=pDoc->m_figures.end(); i++)
		(*i)->OnDraw(bb, pDoc->m_WindosSize);

		//Display selected figure
		if(pDoc->position != pDoc->m_figures.end())
		(*pDoc->position)->DrawSelected(bb,pDoc->m_WindosSize);


		//Display backbuffer
		bb->Display(pDC);
	}
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

	switch (pDoc->m_current)
	{
		case IM_CIRCLE:	  {
			CCircle *C = new CCircle;
			C->m_center = point;
			C->m_tangente = point;
			pDoc->m_figures.push_back(C);
			pDoc->position = pDoc->m_figures.begin() + pDoc->m_figures.size() - 1;
			break;
		}
		case IM_LINE:	  {
			CLine *L = new CLine;
			L->m_p1 = point;
			L->m_p2 = point;
			pDoc->m_figures.push_back(L);
			pDoc->position = pDoc->m_figures.begin() + pDoc->m_figures.size() - 1;
			break;
		}
		case IM_ELLIPSE:  {
			CEllipse *E = new CEllipse;
			E->m_p1 = point;
			E->m_p2 = point;
			pDoc->m_figures.push_back(E);
			pDoc->position = pDoc->m_figures.begin() + pDoc->m_figures.size() - 1;
			break;
		}
		case IM_TRIANGLE:{
			if(pDoc->m_triangle == 1){
				std::vector<CShape *>::reverse_iterator i = pDoc->m_figures.rbegin();
				((CTriangle *)(*i))->m_p2 = point;
				pDoc->m_triangle = 0;
				pDoc->m_current = -1;
			}else{
				CTriangle *T = new CTriangle;
				T->m_p0 = point;
				T->m_p1 = point;
				T->m_p2 = point;
				++pDoc->m_triangle;
				pDoc->m_figures.push_back(T);
				pDoc->position = pDoc->m_figures.begin() + pDoc->m_figures.size() - 1;

			}
			break;
		}
		case IM_BEZIER:  {
			CBezier *B = new CBezier;
			B->arr[0][0] = point;
			B->arr[0][1] = point;
			pDoc->m_figures.push_back(B);
			pDoc->position = pDoc->m_figures.begin() + pDoc->m_figures.size() - 1;
			break;
		}
		default:{
			if ((nFlags & MK_CONTROL) && pDoc->position != pDoc->m_figures.end()){
				::SetCursor(::LoadCursor(0, IDC_HAND));

				pDoc->m_initialPoint = point;
			 
			}else if ((nFlags & MK_SHIFT) && pDoc->position != pDoc->m_figures.end()){
			
				//Select a control point of the selected figure
				pDoc->m_selectedPoint = NULL;
				pDoc->m_selectedPoint = (*pDoc->position)->IntersectControlPoint(point);
				if(pDoc->m_selectedPoint != NULL){
					::SetCursor(::LoadCursor(0, IDC_SIZEALL));
					break;
				}
			}else{
				pDoc->position = pDoc->m_figures.end();

				for (std::vector<CShape *>::iterator i = pDoc->m_figures.begin(); i!=pDoc->m_figures.end(); i++){
					if((*i)->Intersect(point)){
						pDoc->position = i;
					}
				}
			}
			break;
		}
	}
	Invalidate();

	CView::OnLButtonDown(nFlags, point);
}


void CCGProyectView::OnLButtonUp(UINT nFlags, CPoint point)
{
	CCGProyectDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	if (pDoc->m_pressed)
	{
		std::vector<CShape *>::reverse_iterator i = pDoc->m_figures.rbegin();
		switch (pDoc->m_current)
		{
			case IM_CIRCLE:	{
				((CCircle*)(*i))->m_tangente = point;
				//((CButton*)GetDlgItem(ID_BUTTON_CIRCLE))->SetCheck(false);
			//	((CMainFrame*)AfxGetMainWnd())->m_wndToolBar.CheckDlgButton(ID_BUTTON_CIRCLE,false);
				pDoc->m_current = -1;
				break;
			}
			case IM_LINE:	{
				((CLine *)(*i))->m_p2 = point;
				pDoc->m_current = -1;
				break;
			}
			case IM_ELLIPSE:{
				((CEllipse *)(*i))->m_p2 = point;
				pDoc->m_current = -1;
				break;
			}
			case IM_TRIANGLE:{
				if(pDoc->m_triangle == 1){
					((CTriangle *)(*i))->m_p1 = point;
					((CTriangle *)(*i))->m_p2 = point;
				}
				break;
			}
			case IM_BEZIER:  {
				((CBezier *)(*i))->arr[0][1] = point;
				pDoc->m_current = -1;

				break;
			}
			default:{
				if ((nFlags & MK_CONTROL) && (nFlags & MK_LBUTTON)  && pDoc->position != pDoc->m_figures.end()){
					//::SetCursor(::LoadCursor(0, IDC_ARROW));
					POINT p;

					p.x = (point.x - pDoc->m_initialPoint.x) ;
					p.y = (point.y - pDoc->m_initialPoint.y) ;

					(*pDoc->position)->Translate(p);

					pDoc->m_initialPoint = point;
				}else if ((nFlags & MK_SHIFT) && (nFlags & MK_LBUTTON) && pDoc->m_selectedPoint != NULL){
					pDoc->m_selectedPoint->x = (float)point.x ;
					pDoc->m_selectedPoint->y = (float)point.y ;
				}
			break;
			}
		}
		Invalidate();
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
	

	if ((nFlags & MK_LBUTTON) && pDoc->m_pressed)
	{
		std::vector<CShape *>::reverse_iterator i = pDoc->m_figures.rbegin();
		switch (pDoc->m_current)
		{
			case IM_CIRCLE:	{
				((CCircle*)(*i))->m_tangente = point;
				break;
			}
			case IM_LINE:	{
				((CLine *)(*i))->m_p2 = point;
				break;
			}
			case IM_ELLIPSE:{
				((CEllipse *)(*i))->m_p2 = point;
				break;
			}
			case IM_TRIANGLE:{
				if(pDoc->m_triangle == 1){
					((CTriangle *)(*i))->m_p1 = point;
				}
				break;
			}
			case IM_BEZIER:  {
				((CBezier *)(*i))->arr[0][1] = point;
				break;
			}		 
			default:{
				if ((nFlags & MK_CONTROL) && (nFlags & MK_LBUTTON)  && pDoc->position != pDoc->m_figures.end()){
					::SetCursor(::LoadCursor(0, IDC_HAND));

					POINT p;

					p.x = (point.x - pDoc->m_initialPoint.x) ;
					p.y = (point.y - pDoc->m_initialPoint.y) ;

					(*pDoc->position)->Translate(p);

						pDoc->m_initialPoint = point;
						Invalidate();
				}else if ((nFlags & MK_SHIFT) && (nFlags & MK_LBUTTON) && pDoc->m_selectedPoint != NULL){
					::SetCursor(::LoadCursor(0, IDC_SIZEALL));

					pDoc->m_selectedPoint->x = (float)point.x ;
					pDoc->m_selectedPoint->y = (float)point.y ;
					Invalidate();
				}
				break;
			}
		}
		Invalidate();
	}

	CView::OnMouseMove(nFlags, point);

}

//Create a Bezier Curve
void CCGProyectView::OnButtonBezier()
{
	CCGProyectDoc* pDoc = GetDocument();
	pDoc->m_current = IM_BEZIER;
}

//Create a Circle
void CCGProyectView::OnButtonCircle()
{
	CCGProyectDoc* pDoc = GetDocument();
	pDoc->m_current = IM_CIRCLE;
}

//Create an Ellipse
void CCGProyectView::OnButtonEllipse()
{
	CCGProyectDoc* pDoc = GetDocument();
	pDoc->m_current = IM_ELLIPSE;
}

//Create a Line
void CCGProyectView::OnButtonLine()
{
	CCGProyectDoc* pDoc = GetDocument();
	pDoc->m_current = IM_LINE;
}

//Create a Trinagle
void CCGProyectView::OnButtonTriangle()
{
	CCGProyectDoc* pDoc = GetDocument();
	pDoc->m_triangle = 0;
	pDoc->m_current = IM_TRIANGLE;
}

//Create a canvas for an image
void CCGProyectView::OnButtonImage()
{
	CCGProyectDoc* pDoc = GetDocument();
	pDoc->m_current = IM_IMAGE;

	
	//Create a Dialog to search for an image
	CFileDialog dlg(true,NULL,NULL,NULL,_T("BMP Files (*.bmp)|*.bmp||"));

	if(dlg.DoModal() == IDOK)
	{
		//Create an image
		CMyImage *I = new CMyImage;
		CString filename;

		filename = dlg.GetPathName(); // return full path and filename
		
		//Set the image to the  class
		if(I->SetBitmap(filename)){

			//Put it in the vector of figures
			pDoc->m_figures.push_back(I);
			pDoc->position = pDoc->m_figures.begin() + pDoc->m_figures.size() - 1;
			Invalidate();
		}else {
			delete I;
		}
	}

	pDoc->m_current = -1;
}


void CCGProyectView::OnContextMenu(CWnd * pWnd, CPoint point)
{
	CCGProyectDoc* pDoc = GetDocument();
	
	CMenu menu;

	if(pDoc->position != pDoc->m_figures.end() && (*pDoc->position)->GetID() == IM_BEZIER)			menu.LoadMenu(IDR_MENU2);
	else if(pDoc->position != pDoc->m_figures.end() && (*pDoc->position)->GetID() == IM_IMAGE)		menu.LoadMenu(IDR_MENU_IMAGE);
	else if(pDoc->position != pDoc->m_figures.end() && (*pDoc->position)->GetID() == IM_TRIANGLE){ 

		CPoint q = point;
		ScreenToClient(&q);

		pDoc->m_selectedPoint = NULL;
		pDoc->m_selectedPoint = (*pDoc->position)->IntersectControlPoint(q);
		
		if(pDoc->m_selectedPoint != NULL)															menu.LoadMenu(IDR_MENU4);	
		else																						menu.LoadMenu(IDR_MENU2);
	}else																							menu.LoadMenu(IDR_MENU1);

    CMenu *pSub = menu.GetSubMenu(0);
    // Modify menu items here if necessary (e.g. gray out items)
    int nCmd = pSub->TrackPopupMenuEx(
        TPM_LEFTALIGN | TPM_LEFTBUTTON,
        point.x, point.y, this, NULL);

	Invalidate();
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
			Invalidate();
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
			Invalidate();
		}
	}
}

//Delete only one figure
void CCGProyectView::OnChangeDeletefigure()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		pDoc->position = pDoc->m_figures.erase(pDoc->position);
		Invalidate();
	}
}

//Change if a figure is filled
void CCGProyectView::OnChangeFillfigure()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		(*pDoc->position)->ChangeFilled();
		Invalidate();
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
			Invalidate();
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
			Invalidate();
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
			Invalidate();
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
			Invalidate();
		}
	}
}

//U Key
void CCGProyectView::OnDeselectKey()
{
	CCGProyectDoc* pDoc = GetDocument();
	pDoc->position = pDoc->m_figures.end();
	Invalidate();
}

//Control + delete
void CCGProyectView::OnDeleteKey()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(!pDoc->m_figures.empty()){
		pDoc->m_figures.clear();
		pDoc->position = pDoc->m_figures.begin();
		Invalidate();
	}
}

//Delete all figures
void CCGProyectView::OnChangeDeteleallfigures()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(!pDoc->m_figures.empty()){
		pDoc->m_figures.clear();
		pDoc->position = pDoc->m_figures.begin();
		Invalidate();
	}
}

//Unselect a figure
void CCGProyectView::OnChangeUnselectfigure()
{
	CCGProyectDoc* pDoc = GetDocument();
	pDoc->position = pDoc->m_figures.end();
	Invalidate();
}

//Delete only one figure
void CCGProyectView::OnDeleteOneKey()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		pDoc->position = pDoc->m_figures.erase(pDoc->position);
		Invalidate();
	}
}


//Elevate the degree of the bezier curve
void CCGProyectView::OnChangeNewbeziercurve()
{

	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_BEZIER){
			((CBezier*)(*pDoc->position))->addControlpoint();
		}
	}
}

BOOL CCGProyectView::OnEraseBkgnd(CDC* pDC)
{

	return true;//CView::OnEraseBkgnd(pDC);
}

//On window resize
void CCGProyectView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CCGProyectDoc* pDoc = GetDocument();
	pDoc->m_WindosSize.x = cx;
	pDoc->m_WindosSize.y = cy;

	if(bb == NULL)	bb = new CBackBuffer();
	else			bb->Destroy();
	

	bb->ChangeSize(cx, cy, GetDC());

	Invalidate();
}

void CCGProyectView::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CView::OnActivate(nState, pWndOther, bMinimized);
}


void CCGProyectView::OnDestroy()
{
	CView::OnDestroy();
	if(bb != NULL){
		bb->Destroy();
	}
}


int CCGProyectView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

		return 0;
}

//Set the circle button checked
void CCGProyectView::OnUpdateButtonCircle(CCmdUI *pCmdUI)
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->m_current == IM_CIRCLE){
		pCmdUI->SetCheck(true);
	}else{
		pCmdUI->SetCheck(false);
	}
}

//Set the Circle button checked
void CCGProyectView::OnUpdateButtonBezier(CCmdUI *pCmdUI)
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->m_current == IM_BEZIER){
		pCmdUI->SetCheck(true);
	}else{
		pCmdUI->SetCheck(false);
	}
}

//Set the Ellipse button checked
void CCGProyectView::OnUpdateButtonEllipse(CCmdUI *pCmdUI)
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->m_current == IM_ELLIPSE){
		pCmdUI->SetCheck(true);
	}else{
		pCmdUI->SetCheck(false);
	}
}

//Set the Line button checked
void CCGProyectView::OnUpdateButtonLine(CCmdUI *pCmdUI)
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->m_current == IM_LINE){
		pCmdUI->SetCheck(true); 
	}else{
		pCmdUI->SetCheck(false);
	}
}

//Set the Triangle button checked
void CCGProyectView::OnUpdateButtonTriangle(CCmdUI *pCmdUI)
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->m_current == IM_TRIANGLE){
		pCmdUI->SetCheck(true);
	}else{
		pCmdUI->SetCheck(false);
	}
}

//Set the Image button checked
void CCGProyectView::OnUpdateButtonImage(CCmdUI *pCmdUI)
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->m_current == IM_IMAGE){
		pCmdUI->SetCheck(true);
	}else{
		pCmdUI->SetCheck(false);
	}
}


//Cancel the insertion of buttons
void CCGProyectView::OnButtonCancel()
{
	CCGProyectDoc* pDoc = GetDocument();
	pDoc->m_current = -1;
}

//Subdivide Bezier Curve
void CCGProyectView::OnDivideBezier()
{

	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_BEZIER){
			std::vector< CPOINT2F > firsthalf, secondhalf;
			((CBezier*)(*pDoc->position))->Divide(firsthalf, secondhalf, 0.5);


			CBezier *B = new CBezier(firsthalf);
			pDoc->m_figures.push_back(B);

			B = new CBezier(secondhalf);
			pDoc->m_figures.push_back(B);
			

			firsthalf.clear();
			secondhalf.clear();	
			pDoc->position = pDoc->m_figures.begin() + pDoc->m_figures.size() - 1;
		}
	}
}

//Change the color of a point in a triangle
void CCGProyectView::OnChangeChangepointcolor()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_TRIANGLE && pDoc->m_selectedPoint != NULL){
			COLORREF color;
			CColorDialog dlg; 
			if (dlg.DoModal() == IDOK){
				color = dlg.GetColor(); 
				((CTriangle*)(*pDoc->position))->setColor(pDoc->m_selectedPoint, color);
				Invalidate();
			}
		}
	}		
}


//Apply 3x3 box filter 
void CCGProyectView::OnBox3x3filter()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_IMAGE){
			((CMyImage*)(*pDoc->position))->ApplyFilter(IM_BOX, 3);
			Invalidate();
		}
	}
}

//Apply 5x5 box filter 
void CCGProyectView::OnBox5x5filter()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_IMAGE){
			((CMyImage*)(*pDoc->position))->ApplyFilter(IM_BOX, 5);
			Invalidate();
		}
	}
}

//Apply 7x7 box filter 
void CCGProyectView::OnBox7x7filter()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_IMAGE){
			((CMyImage*)(*pDoc->position))->ApplyFilter(IM_BOX, 7);
			Invalidate();
		}
	}
}

//Apply 3x3 Gaussian filter 
void CCGProyectView::OnGaussian3x3()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_IMAGE){
			((CMyImage*)(*pDoc->position))->ApplyFilter(IM_GAUSSIAN, 3);
			Invalidate();
		}
	}
}

//Apply 5x5 Gaussian filter 
void CCGProyectView::OnGaussian5x5filter()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_IMAGE){
			((CMyImage*)(*pDoc->position))->ApplyFilter(IM_GAUSSIAN, 5);
			Invalidate();
		}
	}
}

//Apply 7x7 Gaussian filter 
void CCGProyectView::OnGaussian7x7filter()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_IMAGE){
			((CMyImage*)(*pDoc->position))->ApplyFilter(IM_GAUSSIAN, 7);
			Invalidate();
		}
	}
}

//Apply 3x3 media filter 
void CCGProyectView::OnMedian3x3filter()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_IMAGE){
			((CMyImage*)(*pDoc->position))->ApplyFilter(IM_MEDIAN, 3);
			Invalidate();
		}
	}
}

//Apply 5x5 median filter 
void CCGProyectView::OnMedian5x5filter()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_IMAGE){
			((CMyImage*)(*pDoc->position))->ApplyFilter(IM_MEDIAN, 5);
			Invalidate();
		}
	}
}

//Apply 7x7 median filter 
void CCGProyectView::OnMedian7x7filter()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_IMAGE){
			((CMyImage*)(*pDoc->position))->ApplyFilter(IM_MEDIAN, 7);
			Invalidate();
		}
	}
}

//Apply 3x3 min filter 
void CCGProyectView::OnMin3x3filter()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_IMAGE){
			((CMyImage*)(*pDoc->position))->ApplyFilter(IM_MIN, 3);
			Invalidate();
		}
	}
}

//Apply 5x5 min filter 
void CCGProyectView::OnMin5x5filter()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_IMAGE){
			((CMyImage*)(*pDoc->position))->ApplyFilter(IM_MIN, 5);
			Invalidate();
		}
	}
}

//Apply 7x7 min filter 
void CCGProyectView::OnMin7x7filter()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_IMAGE){
			((CMyImage*)(*pDoc->position))->ApplyFilter(IM_MIN, 7);
			Invalidate();
		}
	}
}

//Apply 3x3 max filter 
void CCGProyectView::OnMax3x3filter()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_IMAGE){
			((CMyImage*)(*pDoc->position))->ApplyFilter(IM_MAX, 3);
			Invalidate();
		}
	}
}

//Apply 5x5 max filter 
void CCGProyectView::OnMax5x5filter()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_IMAGE){
			((CMyImage*)(*pDoc->position))->ApplyFilter(IM_MAX, 5);
			Invalidate();
		}
	}
}

//Apply 7x7 max filter 
void CCGProyectView::OnMax7x7filter()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_IMAGE){
			((CMyImage*)(*pDoc->position))->ApplyFilter(IM_MAX, 7);
			Invalidate();
		}
	}
}

//Apply 3x3 Laplace filter 
void CCGProyectView::OnApllyfilterLaplace()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_IMAGE){
			((CMyImage*)(*pDoc->position))->ApplyFilter(IM_LAPLACE);
			Invalidate();
		}
	}
}

//Apply 3x3 sharpen filter 
void CCGProyectView::OnApllyfilterSharpen()
{
	CCGProyectDoc* pDoc = GetDocument();
	if(pDoc->position != pDoc->m_figures.end()){
		if((*pDoc->position)->GetID() == IM_IMAGE){
			((CMyImage*)(*pDoc->position))->ApplyFilter(IM_SHARPEN);
			Invalidate();
		}
	}
}
