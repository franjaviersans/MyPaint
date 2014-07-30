#pragma once
#include "afxwin.h"


// CDialogBright dialog

class CDialogBright : public CDialogEx
{
	DECLARE_DYNAMIC(CDialogBright)

public:
	CDialogBright(CWnd* pParent = NULL);   // standard constructor
	virtual ~CDialogBright();

// Dialog Data
	enum { IDD = IDD_DIALOG_BRIGHT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CStatic m_drawingArea;
	afx_msg void OnPaint();
};
