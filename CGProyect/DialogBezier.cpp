// DialogBright.cpp : implementation file
//

#include "stdafx.h"
#include "CGProyect.h"
#include "DialogBezier.h"
#include "afxdialogex.h"
#include <iostream>
#include <fstream>


#define PRECISION 10000.0f

// DialogBright dialog

IMPLEMENT_DYNAMIC(CDialogBezier, CDialogEx)

CDialogBezier::CDialogBezier(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogBezier::IDD, pParent)
	, m_kBezier(0)
{

}

CDialogBezier::~CDialogBezier()
{
}


void CDialogBezier::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Slider(pDX, IDC_SLIDER_BEZIER, m_kBezier);
	DDV_MinMaxInt(pDX, m_kBezier, 0, int(PRECISION));
	DDX_Control(pDX, IDC_EDIT2, m_kValue);
}


BEGIN_MESSAGE_MAP(CDialogBezier, CDialogEx)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// DialogBright message handlers


void CDialogBezier::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	CSliderCtrl* Slide = (CSliderCtrl*)pScrollBar;
    CString text;
    int value;

    if(Slide->GetDlgCtrlID() == IDC_SLIDER_BEZIER)
    {
            value = Slide->GetPos();
            m_k = float(value)/PRECISION;
            text.Format("%.3f",m_k);
			m_kValue.SetWindowTextA(text);
    }
    Invalidate(false);

	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}


BOOL CDialogBezier::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CSliderCtrl* Slider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER_BEZIER);
    Slider->SetRange(0,int(PRECISION));
    m_k = (int)(0.5*PRECISION);
	Slider->SetPos(int(m_k));
	CString text;
	m_k = (m_k/PRECISION);
	text.Format("%.3f",m_k);
    m_kValue.SetWindowTextA(text);
    Invalidate();

    return TRUE; 

}
