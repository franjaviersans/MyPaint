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
	virtual void OnDraw(CBackBuffer *, POINT);
	virtual void Serialize(CArchive& ar);
	virtual void DrawSelected(CBackBuffer *, POINT);
	virtual bool Intersect(CPOINT2F);
	virtual CPOINT2F* IntersectControlPoint(CPOINT2F);
	virtual void Translate(CPOINT2F);
	virtual void ChangeFillColor(COLORREF);
	virtual void ChangeLineColor(COLORREF);
	virtual void ChangeFilled();

private:
	void EllipsePoints(int x, int y, POINT center, COLORREF color, CBackBuffer *pDC);
	void EllipsePointsFilled(int x, int y, POINT center, COLORREF color, CBackBuffer *pDC);
};

#endif
