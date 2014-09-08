#pragma once


// CContrastDraw

class CContrastDraw : public CStatic
{
	DECLARE_DYNAMIC(CContrastDraw)

public:
	CContrastDraw();
	virtual ~CContrastDraw();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual void DrawItem(LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};


