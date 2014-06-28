#include "stdafx.h"
#include "Circle.h"
#include "Line.h"
#include <iostream>
#include <fstream>

CCircle::CCircle()
{
	m_center.x = m_center.y = 0;
	m_tangente.x = m_tangente.y = 0;
	m_id = IM_CIRCLE;
	m_bgcolor = 0;
	m_linecolor = 0;
	m_filled = false;
}

void CCircle::OnDraw(CBackBuffer *pDC, POINT WindowsSize)
{

	POINT center, tangent;
	center.x = (int)(m_center.x * WindowsSize.x);
	center.y = (int)(m_center.y * WindowsSize.y);
	tangent.x = (int)(m_tangente.x * WindowsSize.x);
	tangent.y = (int)(m_tangente.y * WindowsSize.y);
	
	int dx = center.x - tangent.x;
	int dy = center.y - tangent.y;
	int incx, incy, delta;
	int r = (int)(0.5+sqrt( (double)dx * dx + dy * dy));

	int x,y,d;
	x = 0;
	y = r;
	d = 1-r;

	incx		= 3;
	delta		= 2;
	incy		= -2 * r +5;

	if(m_filled)Draw8PointsFilled(x, y, center, m_linecolor, pDC);
	else		Draw8Points(x, y, center, m_linecolor, pDC);

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
		if(m_filled)Draw8PointsFilled(x, y, center, m_linecolor, pDC);
		else		Draw8Points(x, y, center, m_linecolor, pDC);
	}
}

void CCircle::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_id;
		ar << m_bgcolor;
		ar << m_linecolor;
		ar << m_filled;
		ar << m_center.x;
		ar << m_center.y;
		ar << m_tangente.x;
		ar << m_tangente.y;
	}
	else
	{
		ar >> m_bgcolor;
		ar >> m_linecolor;
		ar >> m_filled;
		ar >> m_center.x;
		ar >> m_center.y;
		ar >> m_tangente.x;
		ar >> m_tangente.y;
	}
}

void CCircle::Draw8Points(int x, int y, POINT center, COLORREF color, CBackBuffer *pDC){
	pDC->SetPixel(center.x + x,	center.y + y, color);
	pDC->SetPixel(center.x - x,	center.y + y, color);
	pDC->SetPixel(center.x - x, center.y - y, color);
	pDC->SetPixel(center.x + x, center.y - y, color);
	pDC->SetPixel(center.x + y, center.y + x, color);
	pDC->SetPixel(center.x - y, center.y + x, color);
	pDC->SetPixel(center.x - y, center.y - x, color);
	pDC->SetPixel(center.x + y, center.y - x, color);
}

void CCircle::Draw8PointsFilled(int x, int y, POINT center, COLORREF color, CBackBuffer *pDC){
	pDC->FillLine(center.x + x, center.y + y, center.x - x, center.y + y, m_bgcolor);
	pDC->SetPixel(center.x + x,	center.y + y, color);
	pDC->SetPixel(center.x - x,	center.y + y, color);
	pDC->FillLine(center.x + x, center.y - y, center.x - x, center.y - y, m_bgcolor);
	pDC->SetPixel(center.x - x, center.y - y, color);
	pDC->SetPixel(center.x + x, center.y - y, color);
	pDC->FillLine(center.x + y, center.y + x, center.x - y, center.y + x, m_bgcolor);
	pDC->SetPixel(center.x + y, center.y + x, color);
	pDC->SetPixel(center.x - y, center.y + x, color);
	pDC->FillLine(center.x + y, center.y - x, center.x - y, center.y - x, m_bgcolor);
	pDC->SetPixel(center.x - y, center.y - x, color);
	pDC->SetPixel(center.x + y, center.y - x, color);
}

void CCircle::DrawSelected(CBackBuffer *pDC, POINT WindowsSize){

	POINT center, tangent;
	center.x = (int)(m_center.x * WindowsSize.x);
	center.y = (int)(m_center.y * WindowsSize.y);
	tangent.x = (int)(m_tangente.x * WindowsSize.x);
	tangent.y = (int)(m_tangente.y * WindowsSize.y);
	
	int dx = center.x - tangent.x;
	int dy = center.y - tangent.y;
	int r = (int)(0.5+sqrt( (double)dx * dx + dy * dy));

	CColor red(255,0,0);

	POINT p0, p1;
	p0.x = center.x - r;
	p0.y = center.y - r;
	p1.x = center.x - r;
	p1.y = center.y + r;
	
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF());

	p0.x = center.x - r;
	p0.y = center.y - r;
	p1.x = center.x + r;
	p1.y = center.y - r;

	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF());

	p0.x = center.x - r;
	p0.y = center.y + r;
	p1.x = center.x + r;
	p1.y = center.y + r;

	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF());

	p0.x = center.x + r;
	p0.y = center.y - r;
	p1.x = center.x + r;
	p1.y = center.y + r;

	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF());


	CColor green(0, 255, 0);

	p0.x = center.x + r;
	p0.y = center.y - r;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,green.ToCOLORREF());

	p0.x = center.x + r;
	p0.y = center.y + r;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,green.ToCOLORREF());

	p0.x = center.x - r;
	p0.y = center.y - r;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,green.ToCOLORREF());

	p0.x = center.x - r;
	p0.y = center.y + r;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,green.ToCOLORREF());


	CColor other(255, 100, 0);


	p0.x = (int)(m_center.x * WindowsSize.x);
	p0.y = (int)(m_center.y * WindowsSize.y);
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,other.ToCOLORREF());

	p0.x = (int)(m_tangente.x * WindowsSize.x);
	p0.y = (int)(m_tangente.y * WindowsSize.y);
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,other.ToCOLORREF());

}

bool CCircle::Intersect(CPOINT2F p){

	double dx = m_center.x - m_tangente.x;
	double dy = m_center.y - m_tangente.y;
	double r = sqrt( (double)dx * dx + dy * dy);


	if((m_center.x - r <= p.x && p.x <= m_center.x + r) && 
		(m_center.y - r <= p.y && p.y <= m_center.y + r))
		return true;
	else 
		return false;
}

CPOINT2F* CCircle::IntersectControlPoint(CPOINT2F p){
	double epsilon = 0.02;
	if(abs((p.x - m_center.x)) <= epsilon && abs((p.y - m_center.y)) <= epsilon)
		return &m_center;

	if(abs((p.x - m_tangente.x)) <= epsilon && abs((p.y - m_tangente.y)) <= epsilon)
		return &m_tangente;

	return NULL;
}


void CCircle::Translate(CPOINT2F p){
	m_center.x += p.x;
	m_center.y += p.y;
	m_tangente.x += p.x;
	m_tangente.y += p.y;
}

void CCircle::ChangeFillColor(COLORREF c){
	m_bgcolor = c;
}

void CCircle::ChangeLineColor(COLORREF c){
	m_linecolor = c;
}

void CCircle::ChangeFilled(){
	m_filled = !m_filled;
}