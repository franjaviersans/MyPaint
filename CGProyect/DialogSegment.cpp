// DialogSegment.cpp : implementation file
//

#include "stdafx.h"
#include "CGProyect.h"
#include "DialogSegment.h"
#include "afxdialogex.h"
#include <fstream>
#include <iostream>


// CDialogSegment dialog

IMPLEMENT_DYNAMIC(CDialogSegment, CDialogEx)

CDialogSegment::CDialogSegment(std::vector<float> histogram, CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogSegment::IDD, pParent)
{

	float mmax = -1;

	m_vfHistogram = histogram;

	for(unsigned int i=0;i<m_vfHistogram.size();++i){
		mmax = max(m_vfHistogram[i], mmax);
	}

	for(unsigned int i=0;i<m_vfHistogram.size();++i){
		m_vfHistogram[i] /= mmax;
	}

	m_bFirstTime = true;
}

CDialogSegment::~CDialogSegment()
{
}

void CDialogSegment::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_THRESHOLD, m_drawingSegment);
	DDX_Control(pDX, IDC_SLIDER_THRESHOLD, m_sliderValue);
	DDX_Control(pDX, IDC_TEXT_THRESHOLD, m_textValue);
}


BEGIN_MESSAGE_MAP(CDialogSegment, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDialogSegment message handlers


void CDialogSegment::OnPaint()
{


	std::ofstream off("out.txt");
    std::cout.rdbuf(off.rdbuf()); //redirect std::cout to out.txt!
	


		CDC *myDC = GetDlgItem(IDC_STATIC_THRESHOLD)->GetDC();
		LPRECT lpRect;
		lpRect = new CRect();

		CWnd *pWnd = GetDlgItem(IDC_STATIC_THRESHOLD);
		pWnd->GetWindowRect(lpRect);
		ScreenToClient(lpRect); //optional step - see below


		int screen_width = lpRect->right - lpRect->left -4, screen_height = lpRect->bottom- lpRect->top - 4, offsetw = screen_width / 256;

		for(unsigned int i=0;i<m_vfHistogram.size();++i){
			myDC->Rectangle((offsetw)* i, screen_height + 1, (offsetw)*i+1, screen_height - screen_height * m_vfHistogram[i] + 1);

			std::cout<<(offsetw)* i<<"   "<<screen_height -1<<"   "<<(offsetw)*i+1<<"   "<<screen_height - screen_height * m_vfHistogram[i] + 1<<std::endl;
		}


		std::cout<<lpRect->left<<"   "<<lpRect->top<<"   "<<lpRect->right<<"   "<<lpRect->bottom<<std::endl;

		//myDC->Rectangle(0, 0, screen_width, screen_height);
		m_bFirstTime = false;
	
}
