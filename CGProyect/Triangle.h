#ifndef CTRIANGEL_H
#define CTRIANGEL_H

#include <math.h>
#include "Shape.h"
#include "Color.h"


class CTriangle : public CShape
{
public:
	CPOINT2F m_p0;
	CPOINT2F m_p1;
	CPOINT2F m_p2;
	CColor	 m_c0;
	CColor	 m_c1;
	CColor	 m_c2;
	CTriangle();
	virtual void OnDraw(CBackBuffer *, POINT);
	virtual void Serialize(CArchive& ar);
	virtual void DrawSelected(CBackBuffer *, POINT);
	virtual bool Intersect(POINT);
	virtual CPOINT2F* IntersectControlPoint(POINT);
	virtual void Translate(POINT);
	virtual void ChangeFillColor(COLORREF);
	virtual void ChangeLineColor(COLORREF);
	virtual void ChangeFilled();

private:
	void ScanLine(CBackBuffer *);
	float sign(CPOINT2F,CPOINT2F,CPOINT2F);

};

#endif
