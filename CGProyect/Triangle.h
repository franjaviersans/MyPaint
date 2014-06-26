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
	virtual void OnDraw(CDC *, POINT);
	virtual void Serialize(CArchive& ar);
	virtual void DrawSelected(CDC *, POINT);
	virtual bool Intersect(CPOINT2F);
	virtual CPOINT2F* IntersectControlPoint(CPOINT2F);
	virtual void Translate(CPOINT2F);
	virtual void ChangeFillColor(COLORREF);
	virtual void ChangeLineColor(COLORREF);
	virtual void ChangeFilled();

private:
	void ScanLine(CDC *, POINT);

};

#endif
