#pragma once
#include "afxwin.h"
#include "BackBuffer.h"
#include "contrastdraw.h"
#include "Image.h"


// CDialogBright dialog

class CDialogBright : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogBright)

public:
	CDialogBright(CMyImage * image, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogBright();

// Dialog Data
	enum { IDD = IDD_DIALOG_BRIGHT };

private:
	bool m_bFirstTime;
	CDC *m_myCDC;
	int m_iScreenWidth, m_iScreenHeight;
	CBackBuffer *m_bb;
	CMyImage *m_image;
	POINT m_WindosSize;
	CMatrix3 m_mTransform;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CContrastDraw m_drawingArea;
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	int m_iContrast;
	int m_iBright;
	CEdit m_brightValue;
	CEdit m_contrastValue;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
};
