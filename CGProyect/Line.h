#ifndef CLINE_H
#define CLINE_H

#include "Shape.h"


class CLine : public CShape
{
public:
	CPOINT2F m_p1, m_p2;
	CLine();
	virtual void OnDraw(CDC *, POINT);
	virtual void Serialize(CArchive &);
	virtual void DrawSelected(CDC *, POINT);
	static void DrawLine(POINT, POINT, CDC *, COLORREF);
	virtual bool Intersect(POINT);
	virtual void ChangeFillColor(COLORREF);
	virtual void ChangeLineColor(COLORREF);
	virtual void ChangeFilled();
};

#endif