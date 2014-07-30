// DialogBright.cpp : implementation file
//

#include "stdafx.h"
#include "CGProyect.h"
#include "DialogBright.h"
#include "afxdialogex.h"


// CDialogBright dialog

IMPLEMENT_DYNAMIC(CDialogBright, CDialogEx)

CDialogBright::CDialogBright(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDialogBright::IDD, pParent)
{

}

CDialogBright::~CDialogBright()
{
}

void CDialogBright::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_BRIGHT, m_drawingArea);
}


BEGIN_MESSAGE_MAP(CDialogBright, CDialogEx)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDialogBright message handlers


void CDialogBright::OnPaint()
{

	CDC *myDC = GetDlgItem(IDC_STATIC_BRIGHT)->GetDC();
	myDC->Rectangle(10, 10, 20, 20);


}
