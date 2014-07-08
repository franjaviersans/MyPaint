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
	virtual void OnDraw(CBackBuffer *, POINT);
	virtual void Serialize(CArchive& );
	virtual void DrawSelected(CBackBuffer *, POINT);
	virtual bool Intersect(POINT);
	virtual CPOINT2F* IntersectControlPoint(POINT);
	virtual void Translate(POINT);
	virtual void ChangeFillColor(COLORREF);
	virtual void ChangeLineColor(COLORREF);
	virtual void ChangeFilled();
	void addPoint(int x, int y);
	void addControlpoint();
};

#endif
