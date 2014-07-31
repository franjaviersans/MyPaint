// BezierSlider.cpp : implementation file
//

#include "stdafx.h"
#include "CGProyect.h"
#include "BezierSlider.h"
#include "afxdialogex.h"


// BezierSlider dialog

IMPLEMENT_DYNAMIC(BezierSlider, CDialogEx)

BezierSlider::BezierSlider(CWnd* pParent /*=NULL*/)
	: CDialogEx(BezierSlider::IDD, pParent)
{

}

BezierSlider::~BezierSlider()
{
}

void BezierSlider::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(BezierSlider, CDialogEx)
END_MESSAGE_MAP()


// BezierSlider message handlers


/*void CFactorK::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
        CSliderCtrl* Slide = (CSliderCtrl*)pScrollBar;
        CString text;
        int value;

        if(Slide->GetDlgCtrlID() == IDC_SLIDER)
        {
                value = Slide->GetPos();
                k = (float)value/100.f;
                text.Format("%.2f",k);
                SetDlgItemText(IDC_FACTORK,text);

        }
        Invalidate(false);
        CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

BOOL CFactorK::OnInitDialog()
{
        CDialog::OnInitDialog();
        CString text;

        CSliderCtrl* Slider = (CSliderCtrl*)GetDlgItem(IDC_SLIDER);
        Slider->SetRange(0,100);
        Slider->SetPos((int)(k*100));
        k = (float)Slider->GetPos();
        text.Format("%.2f",(k/100.f));
        SetDlgItemText(IDC_FACTORK,text);
        Invalidate(false);

        return TRUE;  // return TRUE unless you set the focus to a control
                      // EXCEPTION: OCX Property Pages should return FALSE
}*/