#ifndef IMAGE_H
#define IMAGE_H

#include <math.h>
#include <vector>
#include "Shape.h"
#include "Matrix3.h"
#include "Filters.h"

class CMyImage : public CShape
{
private:
	CMatrix3 m_Model;
	CMatrix3 m_View;
	CMatrix3 m_Base;
	CMatrix3 m_Traslate;
	CMatrix3 m_Rotate;
	CMatrix3 m_Scale;
	CMatrix3 m_Center;
	CFilters m_Filter;
	float *m_ImageData;
	float *m_Original;
	int m_iWidth;
	int m_iHeight;
	int m_iMin;
	int m_iMax;
	int m_iBytesPerLine;


public:
	CPOINT2F m_p1;
	CPOINT2F m_p2;
	CPOINT2F m_p3;
	CPOINT2F m_p4;
		
	CMyImage();
	~CMyImage();
	virtual void OnDraw(CBackBuffer *, POINT);
	void OnDraw(CBackBuffer *, POINT, CMatrix3);
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
	void ModifyPoint(POINT, CPOINT2F *, bool shift = false);
	void RotateFigure(POINT, POINT);
	int getWidth();
	int getHeight();
	std::vector<float> getHistogram();
	void segmentImage(int, int);
	void reset();
	void changeBrightness(int);
	void changeContrast(int);

private:
	void ScanLine(CBackBuffer *pDC, int draw, CPOINT2F pp0, CPOINT2F pp1, CPOINT2F pp2, CMatrix3 inv);
	CMatrix3 GetModelView();
};

#endif
