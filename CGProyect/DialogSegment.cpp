// DialogSegment.cpp : implementation file
//

#include "stdafx.h"
#include "CGProyect.h"
#include "DialogSegment.h"
#include "afxdialogex.h"
#include "Color.h"
#include <fstream>
#include <iostream>


// CDialogSegment dialog

IMPLEMENT_DYNAMIC(CDialogSegment, CDialogEx)

CDialogSegment::CDialogSegment(CMyImage * image, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogSegment::IDD, pParent)
	, m_sliderValue(0)
{

	float mmax = -1;

	m_image = image;

	m_vfHistogram = m_image->getHistogram();

	for(unsigned int i=0;i<m_vfHistogram.size();++i){
		mmax = max(m_vfHistogram[i], mmax);
	}

	for(unsigned int i=0;i<m_vfHistogram.size();++i){
		m_vfHistogram[i] /= mmax;
	}

	m_iThreshold = 0;

	m_bFirstTime = true;
	m_bb = NULL;
	m_bbMini = NULL;
}

CDialogSegment::~CDialogSegment()
{
	if(m_bb != NULL)
		m_bb->Destroy();

	if(m_bbMini != NULL)
		m_bbMini->Destroy();
}

void CDialogSegment::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	//  DDX_Control(pDX, IDC_STATIC_THRESHOLD, m_drawingSegment);
	DDX_Slider(pDX, IDC_SLIDER_THRESHOLD, m_sliderValue);
	DDV_MinMaxInt(pDX, m_sliderValue, 0, 255);
	DDX_Control(pDX, IDC_TEXT_THRESHOLD, m_textValue);
	DDX_Control(pDX, IDC_STATIC_THRESHOLD, m_drawingThreshold);
	DDX_Control(pDX, IDC_STATIC_MINI_IMAGE, m_dMiniImage);
}


BEGIN_MESSAGE_MAP(CDialogSegment, CDialogEx)
	ON_WM_HSCROLL()
ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CDialogSegment message handlers

void CDialogSegment::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSliderCtrl* Slide = (CSliderCtrl*)pScrollBar;
    CString text;

    if(Slide->GetDlgCtrlID() == IDC_SLIDER_THRESHOLD)
    {
		
		m_iThreshold = Slide->GetPos();
        text.Format("%d",m_iThreshold);
		m_textValue.SetWindowTextA(text);
		m_textValue.Invalidate();

		m_image->segmentImage(m_iThreshold);
    }
    Invalidate(false);

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL CDialogSegment::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CSliderCtrl* Slider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_THRESHOLD);
    Slider->SetRange(0,255);
	Slider->SetPos(127);
	m_iThreshold = 127;
	CString text;
	text.Format("%d",m_iThreshold);
    m_textValue.SetWindowTextA(text);

	m_image->segmentImage(127);

    Invalidate();

    return TRUE; 
}

void CDialogSegment::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default

	if(m_bFirstTime){
		//Init back buffer
		m_myCDC = GetDlgItem(IDC_STATIC_THRESHOLD)->GetDC();
		LPRECT lpRect;
		lpRect = new CRect();

		CWnd *pWnd = GetDlgItem(IDC_STATIC_THRESHOLD);
		pWnd->GetWindowRect(lpRect);
		ScreenToClient(lpRect); //optional step - see below

		m_iScreenWidth = lpRect->right - lpRect->left -4;
		m_iScreenHeight = lpRect->bottom- lpRect->top - 4;

		m_fOffset = m_iScreenWidth / 256.0f;

		//Create the backbuffer
		if(m_bb == NULL)	m_bb = new CBackBuffer();
		else			m_bb->Destroy();
	

		m_bb->ChangeSize(m_iScreenWidth, m_iScreenHeight, GetDC());


		//Init mini image
		m_miniImage = GetDlgItem(IDC_STATIC_MINI_IMAGE)->GetDC();
		lpRect = new CRect();

		pWnd = GetDlgItem(IDC_STATIC_MINI_IMAGE);
		pWnd->GetWindowRect(lpRect);
		ScreenToClient(lpRect); //optional step - see below

		m_WindowSize.x = lpRect->right - lpRect->left -4;
		m_WindowSize.y = lpRect->bottom- lpRect->top - 4;

		//Create the second backbuffer
		if(m_bbMini == NULL)	m_bbMini = new CBackBuffer();
		else			m_bbMini->Destroy();
	
		m_bbMini->ChangeSize(m_WindowSize.x, m_WindowSize.y, GetDC());
		
		m_mTransform = Translate2D(m_WindowSize.x/2.0f, m_WindowSize.y/2.0f);
		
		m_bFirstTime = false;
	}


	if(m_bb != NULL){
		//Clear Back buffer
		m_bb->Clear();
		
		//Draw bars!!!!!
		CColor c(0,0,0);

		for(unsigned int i=0;i<m_vfHistogram.size();++i)
			m_bb->Rectangle(int((m_fOffset) * i), int(m_iScreenHeight - m_iScreenHeight * m_vfHistogram[i]), int((m_fOffset) * (i+1)), m_iScreenHeight, c.ToCOLORREF());

		c.setColor(255,0,0);

		m_bb->Rectangle(int((m_fOffset) * m_iThreshold), 0, int((m_fOffset) * (m_iThreshold + 1)), m_iScreenHeight, c.ToCOLORREF());

		//Display backbuffer
		m_bb->Display(m_myCDC);
	}	


	if(m_bbMini != NULL){
		//Clear Back buffer
		m_bbMini->Clear();

		m_image->OnDraw(m_bbMini, m_WindowSize, m_mTransform);

		//Display backbuffer
		m_bbMini->Display(m_miniImage);
	}	


	

	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
