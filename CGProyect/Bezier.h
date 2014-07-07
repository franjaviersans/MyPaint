#ifndef CBEZIER_H
#define CBEZIER_H

#include <math.h>
#include <vector>
#include "Shape.h"


class CBezier : public CShape
{
public:
	std::vector< std::vector< CPOINT2F > > arr;
	CBezier();
	virtual void OnDraw(CBackBuffer *pDC, POINT WindowsSize);
	virtual void Serialize(CArchive& ar);
	virtual void DrawSelected(CBackBuffer *, POINT);
	virtual bool Intersect(CPOINT2F, POINT);
	virtual CPOINT2F* IntersectControlPoint(CPOINT2F, POINT);
	virtual void Translate(CPOINT2F);
	virtual void ChangeFillColor(COLORREF);
	virtual void ChangeLineColor(COLORREF);
	virtual void ChangeFilled();
	void addPoint(float x, float y);
	void addControlpoint();
};

#endif
