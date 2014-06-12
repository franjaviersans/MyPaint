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
	virtual void OnDraw(CDC *, POINT);
	virtual void Serialize(CArchive& ar);
	virtual void DrawSelected(CDC *, POINT);
	virtual bool Intersect(POINT);
	virtual void ChangeFillColor(COLORREF);
	virtual void ChangeLineColor(COLORREF);
	virtual void ChangeFilled();

private:
	void Draw8Points(int x, int y, POINT center, COLORREF color, CDC *pDC);
};

#endif
