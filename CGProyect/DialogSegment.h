#pragma once
#include "afxwin.h"
#include "afxcmn.h"
#include <vector>

// CDialogSegment dialog

class CDialogSegment : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogSegment)

public:
	CDialogSegment(std::vector<float> histogram, CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogSegment();

// Dialog Data
	enum { IDD = IDD_DIALOG_SEGMENT };


private:
	std::vector<float> m_vfHistogram;
	bool m_bFirstTime;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_drawingSegment;
	CSliderCtrl m_sliderValue;
	CEdit m_textValue;
	afx_msg void OnPaint();
};
