#ifndef IMAGE_H
#define IMAGE_H

#include <math.h>
#include "Shape.h"
#include "Matrix3.h"
#include "Filters.h"

class CMyImage : public CShape
{
private:
	CMatrix3 m_Model;
	CMatrix3 m_View;
	CFilters m_Filter;
	float *m_ImageData;
	float *m_Original;
	int m_iWidth;
	int m_iHeight;
	int m_iBytesPerLine;


public:
	CPOINT2F m_p1;
	CPOINT2F m_p2;
	CPOINT2F m_p3;
	CPOINT2F m_p4;
		
	CMyImage();
	~CMyImage();
	virtual void OnDraw(CBackBuffer *, POINT);
	virtual void Serialize(CArchive& );
	virtual void DrawSelected(CBackBuffer *, POINT);
	virtual bool Intersect(POINT);
	virtual CPOINT2F* IntersectControlPoint(POINT);
	virtual void Translate(POINT);
	virtual void ChangeFillColor(COLORREF);
	virtual void ChangeLineColor(COLORREF);
	virtual void ChangeFilled();
	bool SetBitmap(CString strBitmap);
	void ApplyFilter(int type, int dim = 3);
};

#endif
