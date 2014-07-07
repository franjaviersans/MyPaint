#ifndef CCIRCLE_H
#define CCIRCLE_H

#include <math.h>
#include "Shape.h"


class CCircle : public CShape
{
public:
	CPOINT2F m_center;
	CPOINT2F m_tangente;
	CCircle();
	virtual void OnDraw(CBackBuffer *, POINT);
	virtual void Serialize(CArchive& ar);
	virtual void DrawSelected(CBackBuffer *, POINT);
	virtual bool Intersect(CPOINT2F, POINT);
	virtual CPOINT2F* IntersectControlPoint(CPOINT2F, POINT);
	virtual void Translate(CPOINT2F);
	virtual void ChangeFillColor(COLORREF);
	virtual void ChangeLineColor(COLORREF);
	virtual void ChangeFilled();

private:
	void Draw8Points(int x, int y, POINT center, COLORREF color, CBackBuffer *pDC, int);
	void Draw8PointsFilled(int x, int y, POINT center, COLORREF color, CBackBuffer *pDC, int);
};

#endif
