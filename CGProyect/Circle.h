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
	virtual bool Intersect(POINT);
	virtual CPOINT2F* IntersectControlPoint(POINT);
	virtual void Translate(POINT);
	virtual void ChangeFillColor(COLORREF);
	virtual void ChangeLineColor(COLORREF);
	virtual void ChangeFilled();

private:
	void Draw8Points(int, int, POINT, COLORREF, CBackBuffer *, int);
	void Draw8PointsFilled(int, int, POINT, COLORREF, CBackBuffer *, int,int,int);
};

#endif
