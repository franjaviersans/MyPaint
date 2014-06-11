#ifndef CELLIPSE_H
#define CELLIPSE_H

#include <math.h>
#include "Shape.h"


class CEllipse : public CShape
{
public:
	CPOINT2F m_p1;
	CPOINT2F m_p2;
	CEllipse();
	virtual void OnDraw(CDC *pDC, POINT);
	virtual void Serialize(CArchive& ar);
	virtual void DrawSelected(CDC *, POINT);
	virtual bool Intersect(POINT);
	virtual void ChangeFillColor(COLORREF);
	virtual void ChangeLineColor(COLORREF);

private:
	void EllipsePoints(int x, int y, POINT center, COLORREF color, CDC *pDC);
};

#endif
