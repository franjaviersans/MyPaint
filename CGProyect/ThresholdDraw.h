#pragma once


// CThresholdDraw

class CThresholdDraw : public CStatic
{
	DECLARE_DYNAMIC(CThresholdDraw)

public:
	CThresholdDraw();
	virtual ~CThresholdDraw();


protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


