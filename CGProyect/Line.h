#ifndef CLINE_H
#define CLINE_H

#include "Shape.h"


class CLine : public CShape
{
public:
	CPOINT2F m_p1, m_p2;
	CLine();
	virtual void OnDraw(CBackBuffer *, POINT);
	virtual void Serialize(CArchive &);
	virtual void DrawSelected(CBackBuffer *, POINT);
	static void DrawLine(POINT, POINT, CBackBuffer *, COLORREF);
	static void DrawDottedLine(POINT, POINT, CBackBuffer *, COLORREF);
	virtual bool Intersect(CPOINT2F, POINT);
	virtual CPOINT2F* IntersectControlPoint(CPOINT2F, POINT);
	virtual void Translate(CPOINT2F);
	virtual void ChangeFillColor(COLORREF);
	virtual void ChangeLineColor(COLORREF);
	virtual void ChangeFilled();
};

#endif