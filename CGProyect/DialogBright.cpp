// DialogBright.cpp : implementation file
//

#include "stdafx.h"
#include "CGProyect.h"
#include "DialogBright.h"
#include "afxdialogex.h"


// CDialogBright dialog

IMPLEMENT_DYNAMIC(CDialogBright, CDialogEx)

CDialogBright::CDialogBright(CMyImage * image, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogBright::IDD, pParent)
	, m_iContrast(0)
	, m_iBright(0)
{
	m_bFirstTime = true;
	m_bb = NULL;
	m_image = image;
}

CDialogBright::~CDialogBright()
{
	if(m_bb != NULL)
		m_bb->Destroy();
}

void CDialogBright::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_BRIGHT, m_drawingArea);
	DDX_Slider(pDX, IDC_SLIDER_CONTRAST, m_iContrast);
	DDX_Slider(pDX, IDC_SLIDER_LIGHT, m_iBright);
	DDX_Control(pDX, IDC_EDIT2, m_brightValue);
	DDX_Control(pDX, IDC_EDIT3, m_contrastValue);
}


BEGIN_MESSAGE_MAP(CDialogBright, CDialogEx)
	ON_WM_DRAWITEM()
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CDialogBright message handlers

void CDialogBright::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	if(m_bFirstTime){
		//Init back buffer
		CWnd *pWnd = GetDlgItem(IDC_STATIC_BRIGHT);
		m_myCDC = pWnd->GetDC();

		LPRECT lpRect;
		lpRect = new CRect();

		pWnd->GetWindowRect(lpRect);
		ScreenToClient(lpRect); //optional step - see below

		m_iScreenWidth = lpRect->right - lpRect->left -4;
		m_iScreenHeight = lpRect->bottom- lpRect->top - 4;

		//Create the backbuffer
		if(m_bb == NULL)	m_bb = new CBackBuffer();
		else			m_bb->Destroy();
	
		m_WindowSize.x = m_iScreenWidth;
		m_WindowSize.y = m_iScreenHeight;
		m_bb->ChangeSize(m_iScreenWidth, m_iScreenHeight, GetDC());


		//Translation
		float a, fat1, fat2;

		fat1 = (m_WindowSize.x * 3.f/4.f)/ (m_WindowSize.y * 3.f/4.f);
		fat2 = float(m_image->getWidth()) / m_image->getHeight();

		if(fat2 >= fat1)	a = (m_WindowSize.x * 3.f/4.f) / m_image->getWidth();
		else				a = (m_WindowSize.y * 3.f/4.f) / m_image->getHeight();


		m_mTransform = Translate2D(m_WindowSize.x/2.0f, m_WindowSize.y/2.0f) * Scale2D(a, a);

		m_bFirstTime = false;
	}


	if(m_bb != NULL){
		//Clear Back buffer
		m_bb->Clear();
		
		//Draw bars!!!!!
		CColor c(0,0,0);

		m_image->OnDraw(m_bb, m_WindowSize, m_mTransform);

		//Display backbuffer
		m_bb->Display(m_myCDC);
	}

	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


BOOL CDialogBright::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CSliderCtrl* Slider1 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_CONTRAST);
	CSliderCtrl* Slider2 = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_LIGHT);
    Slider1->SetRange(0,510);
	Slider1->SetPos(510/2);
	Slider2->SetRange(0,510);
	Slider2->SetPos(510/2);
	m_iContrast = 0;
	m_iBright = 0;
	CString text;

	text.Format("%d",m_iContrast);
	m_contrastValue.SetWindowTextA(text);

	text.Format("%d",m_iBright);
    m_brightValue.SetWindowTextA(text);
    Invalidate();

	return TRUE;
}


void CDialogBright::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSliderCtrl* Slide = (CSliderCtrl*)pScrollBar;
    CString text;

    if(Slide->GetDlgCtrlID() == IDC_SLIDER_CONTRAST)
    {	
		m_iContrast = Slide->GetPos() - 255;
        text.Format("%d",m_iContrast);
		m_contrastValue.SetWindowTextA(text);
		m_image->changeContrast(m_iContrast);
    }

	if(Slide->GetDlgCtrlID() == IDC_SLIDER_LIGHT)
    {
		m_iBright = Slide->GetPos() - 255;
        text.Format("%d",m_iBright);
		m_brightValue.SetWindowTextA(text);
		m_image->changeLight(m_iBright);
	}
    Invalidate(false);

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}
