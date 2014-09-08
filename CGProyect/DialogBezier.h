#pragma once
#include "afxwin.h"


// DialogBright dialog

class CDialogBezier : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogBezier)

public:
	CDialogBezier(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogBezier();

// Dialog Data
	enum { IDD = IDD_DIALOG_BEZIER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	float m_k;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
private:
	CEdit m_kValue;
	int m_kBezier;
public:
	virtual BOOL OnInitDialog();
};
