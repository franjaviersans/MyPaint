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
	virtual bool Intersect(CPOINT2F);
	virtual CPOINT2F* IntersectControlPoint(CPOINT2F);
	virtual void Translate(CPOINT2F);
	virtual void ChangeFillColor(COLORREF);
	virtual void ChangeLineColor(COLORREF);
	virtual void ChangeFilled();
};

#endif