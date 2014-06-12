#include "stdafx.h"
#include "Bezier.h"
#include <iostream>
#include <fstream>

CBezier::CBezier()
{
	m_center.x = m_center.y = 0;
	m_tangente.x = m_tangente.y = 0;
	m_id = IM_BEZIER;
	m_bgcolor = 0;
	m_linecolor = 0;
	m_filled = false;
}

void CBezier::OnDraw(CDC *pDC)
{

	
	/*int dx = m_center.x - m_tangente.x;
	int dy = m_center.y - m_tangente.y;
	int incx, incy, delta;
	int r = (int)(0.5+sqrt( (double)dx * dx+ dy * dy));

	//pDC->Ellipse(m_center.x-r, m_center.y-r, m_center.x+r, m_center.y+r);

	COLORREF color;
	color = 0;

	int x,y,d;
	x = 0;
	y = r;
	d = 1-r;

	incx		= 3;
	delta		= 2;
	incy		= -2 * r +5;

	Draw8Points(x, y, m_center, color, pDC);
	while (y > x){
		if (d < 0) {
			d += incx;
		}else{
			d += incx + incy;
			incy += delta;
			--y;
		}
		++x;
		incx += delta;
		Draw8Points(x, y, m_center, color, pDC);
	}*/
}

void CBezier::Serialize(CArchive& ar)
{
	/*if (ar.IsStoring())
	{
		ar << m_id;
		ar << m_center;
		ar << m_tangente;
	}
	else
	{
		ar >> m_center;
		ar >> m_tangente;
	}*/
}

void CBezier::Draw8Points(int x, int y, POINT center, COLORREF color, CDC *pDC){
	pDC->SetPixel(center.x + x,	center.y + y, color);
	pDC->SetPixel(center.x - x,	center.y + y, color);
	pDC->SetPixel(center.x - x, center.y - y, color);
	pDC->SetPixel(center.x + x, center.y - y, color);
	pDC->SetPixel(center.x + y, center.y + x, color);
	pDC->SetPixel(center.x - y, center.y + x, color);
	pDC->SetPixel(center.x - y, center.y - x, color);
	pDC->SetPixel(center.x + y, center.y - x, color);
}

bool CBezier::Intersect(POINT p){
	return true;
}

void CBezier::ChangeFillColor(COLORREF c){
	m_bgcolor = c;
}

void CBezier::ChangeLineColor(COLORREF c){
	m_linecolor = c;
}

void CBezier::ChangeFilled(){
	m_filled = !m_filled;
}