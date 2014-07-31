#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include "BackBuffer.h"
#include <vector>
#include "thresholddraw.h"
#include "contrastdraw.h"
#include "Image.h"

// CDialogSegment dialog

class CDialogSegment : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSegment)

public:
	CDialogSegment(CMyImage * image, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogSegment();

// Dialog Data
	enum { IDD = IDD_DIALOG_SEGMENT };


private:
	std::vector<float> m_vfHistogram;
	bool m_bFirstTime;
	CDC *m_myCDC, *m_miniImage;
	CMyImage *m_image;
	int m_iScreenWidth, m_iScreenHeight;
	float m_fOffset;
	CBackBuffer *m_bb, *m_bbMini;
	CEdit m_textValue;
	int m_sliderValue;
	CThresholdDraw m_drawingThreshold;
	CContrastDraw m_dMiniImage;
	POINT m_WindowSize;
	CMatrix3 m_mTransform;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	int m_iThreshold;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	
	
};
