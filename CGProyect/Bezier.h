#ifndef CBEZIER_H
#define CBEZIER_H

#include <math.h>
#include "Shape.h"


class CBezier : public CShape
{
public:
	CPOINT2F m_center;
	CPOINT2F m_tangente;
	CBezier();
	virtual void OnDraw(CDC *pDC);
	virtual void Serialize(CArchive& ar);

private:
	void Draw8Points(int x, int y, POINT center, COLORREF color, CDC *pDC);
};

#endif
