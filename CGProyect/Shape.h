#ifndef CSHPAE_H
#define CSHAPE_H

#pragma once

#include <afx.h>
#include <afxwin.h>
#include <algorithm>

#include "BackBuffer.h"

enum
{
	IM_LINE,
	IM_CIRCLE,
	IM_ELLIPSE,
	IM_BEZIER,
	IM_TRIANGLE,
	IM_IMAGE
};

class CPOINT2F
{
public:
	float x;
	float y;
	CPOINT2F(): x(0), y(0){};
	CPOINT2F(POINT p): x((float)p.x), y((float)p.y){};
	CPOINT2F(int xx, int yy): x((float)xx), y((float)yy){};
};

	/*std::ofstream off("out.txt");
    std::cout.rdbuf(off.rdbuf()); //redirect std::cout to out.txt!
	std::cout<< r << "   "<< m_center.x<<"   "<<m_center.y<<"  "<<m_tangente.x<<"   "<<m_tangente.y<<std::endl;
	std::cout<< dx * dx << "   "<< (m_center.x - m_tangente.x)<<"   "<<
		dy * dy<<"  "<<(m_center.y - m_tangente.y)<<"   "<<sqrt( (double)dx * dx+ dy * dy)<<std::endl;*/


class CShape
{
protected:
	int m_id;
	COLORREF m_bgcolor;
	COLORREF m_linecolor;
	bool m_filled;

public:
	virtual void OnDraw(CBackBuffer *, POINT) = 0;
    virtual void Serialize(CArchive& ar) = 0;
	virtual void DrawSelected(CBackBuffer *, POINT) = 0;
	virtual bool Intersect(POINT) = 0;
	virtual CPOINT2F* IntersectControlPoint(POINT) = 0; 
	virtual void Translate(POINT) = 0;
	virtual void ChangeFillColor(COLORREF) = 0;
	virtual void ChangeLineColor(COLORREF) = 0;
	virtual void ChangeFilled() = 0;
	int GetID(){
		return m_id;
	}
};

#endif