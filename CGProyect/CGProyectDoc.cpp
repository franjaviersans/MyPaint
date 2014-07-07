
// CGProyectDoc.cpp : implementation of the CCGProyectDoc class
//

#include "stdafx.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "CGProyect.h"
#endif

#include "CGProyectDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CCGProyectDoc

IMPLEMENT_DYNCREATE(CCGProyectDoc, CDocument)

BEGIN_MESSAGE_MAP(CCGProyectDoc, CDocument)
END_MESSAGE_MAP()


// CCGProyectDoc construction/destruction

CCGProyectDoc::CCGProyectDoc()
{
	
}

CCGProyectDoc::~CCGProyectDoc()
{

}

BOOL CCGProyectDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	m_figures.clear();
	position		= m_figures.begin();
	m_current		= -1;
	m_pressed		= m_bezier = false;
	m_triangle		= 0;
	m_selectedPoint = NULL;

	m_pFrame = (CMainFrame*) AfxGetApp()->m_pMainWnd;
	m_pToolBar = &m_pFrame->m_wndToolBar;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CCGProyectDoc serialization

void CCGProyectDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_figures.size();
		for (std::vector<CShape *>::iterator i = m_figures.begin(); i != m_figures.end(); i++)
			(*i)->Serialize(ar);
	}
	else
	{
		m_figures.clear();
		int n, id;
		ar >> n;

		for(int i=0; i < n; ++i){
			ar >> id;
			switch (id)
			{
				case IM_CIRCLE:{
					CCircle *C = new CCircle;
					C->Serialize(ar);
					m_figures.push_back(C);
					break;
				}
				case IM_LINE:{
					CLine *L = new CLine;
					L->Serialize(ar);
					m_figures.push_back(L);
					break;
				}
				case IM_ELLIPSE:{
					CEllipse *E = new CEllipse;
					E->Serialize(ar);
					m_figures.push_back(E);
					break;
				}
				case IM_TRIANGLE:{
					CTriangle *T = new CTriangle;
					T->Serialize(ar);
					m_figures.push_back(T);
					break;
				}
				case IM_BEZIER:{
					CBezier *B = new CBezier;
					B->Serialize(ar);
					m_figures.push_back(B);
					break;
				}
			}
		}
		position = m_figures.end();
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CCGProyectDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CCGProyectDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data. 
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CCGProyectDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CCGProyectDoc diagnostics

#ifdef _DEBUG
void CCGProyectDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CCGProyectDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CCGProyectDoc commands
