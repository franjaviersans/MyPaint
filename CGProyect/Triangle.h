#ifndef CTRIANGEL_H
#define CTRIANGEL_H

#include <math.h>
#include "Shape.h"


class CTriangle : public CShape
{
public:
	CPOINT2F m_p0;
	CPOINT2F m_p1;
	CPOINT2F m_p2;
	CTriangle();
	virtual void OnDraw(CDC *, POINT);
	virtual void Serialize(CArchive& ar);
	virtual void DrawSelected(CDC *, POINT);

private:
	void Draw8Points(int x, int y, POINT center, COLORREF color, CDC *pDC);
};

#endif
