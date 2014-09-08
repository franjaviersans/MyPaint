#pragma once


// BezierSlider dialog

class BezierSlider : public CDialogEx
{
	DECLARE_DYNAMIC(BezierSlider)

public:
	BezierSlider(CWnd* pParent = NULL);   // standard constructor
	virtual ~BezierSlider();

// Dialog Data
	enum { IDD = IDD_DIALOG_BEZIER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
