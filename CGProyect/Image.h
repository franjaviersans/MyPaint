#ifndef IMAGE_H
#define IMAGE_H

#include <math.h>
#include "Shape.h"


class CMyImage : public CShape
{
public:
	CPOINT2F m_p1;
	CPOINT2F m_p2;
	CMyImage();
	virtual void OnDraw(CBackBuffer *, POINT);
	virtual void Serialize(CArchive& );
	virtual void DrawSelected(CBackBuffer *, POINT);
	virtual bool Intersect(POINT);
	virtual CPOINT2F* IntersectControlPoint(POINT);
	virtual void Translate(POINT);
	virtual void ChangeFillColor(COLORREF);
	virtual void ChangeLineColor(COLORREF);
	virtual void ChangeFilled();

};

#endif
