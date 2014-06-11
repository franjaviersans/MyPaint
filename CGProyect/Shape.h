#ifndef CSHPAE_H
#define CSHAPE_H

#pragma once

#include <afx.h>
#include <afxwin.h>

#include <algorithm>

enum
{
	IM_LINE,
	IM_CIRCLE,
	IM_ELLIPSE,
	IM_BEZIER,
	IM_TRIANGLE
};

class CPOINT2F
{
public:
	float x;
	float y;
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

public:
	virtual void OnDraw(CDC *, POINT) = 0;
    virtual void Serialize(CArchive& ar) = 0;
	virtual void DrawSelected(CDC *, POINT) = 0;
	virtual bool Intersect(POINT) = 0;
	virtual void ChangeFillColor(COLORREF) = 0;
	virtual void ChangeLineColor(COLORREF) = 0;
};

#endif