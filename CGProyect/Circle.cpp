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
	// 0 Don't draw, 1 draw secured, 2 draw normal
	int draw;
	POINT center, tangent;
	center.x = (int)m_center.x;
	center.y = (int)m_center.y;
	tangent.x = (int)m_tangente.x;
	tangent.y = (int)m_tangente.y;
	
	int dx = center.x - tangent.x;
	int dy = center.y - tangent.y;
	int r = (int)(0.5+sqrt( (double)dx * dx + dy * dy));

	//Check if the figure is inside the drawing area
	if(center.x + r < 0 || center.x - r >= WindowsSize.x || center.y + r < 0 || center.y - r >= WindowsSize.y)
		draw = 0;
	else if(center.x - r >= 0 && center.x + r < WindowsSize.x && center.y - r >= 0 && center.y + r < WindowsSize.y) draw = 2;
	else draw = 1;

	//If the figure must be draw
	if(draw != 0){
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

		if(m_filled)Draw8PointsFilled(x, y, center, m_linecolor, pDC, draw);
		else		Draw8Points(x, y, center, m_linecolor, pDC, draw);

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
			if(m_filled)Draw8PointsFilled(x, y, center, m_linecolor, pDC, draw);
			else		Draw8Points(x, y, center, m_linecolor, pDC, draw);
		}
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

void CCircle::Draw8Points(int x, int y, POINT center, COLORREF color, CBackBuffer *pDC, int draw){
	if(draw == 2){
		pDC->SetPixel(center.x + x,	center.y + y, color);
		pDC->SetPixel(center.x - x,	center.y + y, color);
		pDC->SetPixel(center.x - x, center.y - y, color);
		pDC->SetPixel(center.x + x, center.y - y, color);
		pDC->SetPixel(center.x + y, center.y + x, color);
		pDC->SetPixel(center.x - y, center.y + x, color);
		pDC->SetPixel(center.x - y, center.y - x, color);
		pDC->SetPixel(center.x + y, center.y - x, color);
	}else{
		pDC->SetPixelSecured(center.x + x,	center.y + y, color);
		pDC->SetPixelSecured(center.x - x,	center.y + y, color);
		pDC->SetPixelSecured(center.x - x, center.y - y, color);
		pDC->SetPixelSecured(center.x + x, center.y - y, color);
		pDC->SetPixelSecured(center.x + y, center.y + x, color);
		pDC->SetPixelSecured(center.x - y, center.y + x, color);
		pDC->SetPixelSecured(center.x - y, center.y - x, color);
		pDC->SetPixelSecured(center.x + y, center.y - x, color);
	}
}

void CCircle::Draw8PointsFilled(int x, int y, POINT center, COLORREF color, CBackBuffer *pDC, int draw){
	if(draw ==  2){
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
	}else{
		pDC->FillLine(center.x + x, center.y + y, center.x - x, center.y + y, m_bgcolor);
		pDC->SetPixelSecured(center.x + x,	center.y + y, color);
		pDC->SetPixelSecured(center.x - x,	center.y + y, color);
		pDC->FillLine(center.x + x, center.y - y, center.x - x, center.y - y, m_bgcolor);
		pDC->SetPixelSecured(center.x - x, center.y - y, color);
		pDC->SetPixelSecured(center.x + x, center.y - y, color);
		pDC->FillLine(center.x + y, center.y + x, center.x - y, center.y + x, m_bgcolor);
		pDC->SetPixelSecured(center.x + y, center.y + x, color);
		pDC->SetPixelSecured(center.x - y, center.y + x, color);
		pDC->FillLine(center.x + y, center.y - x, center.x - y, center.y - x, m_bgcolor);
		pDC->SetPixelSecured(center.x - y, center.y - x, color);
		pDC->SetPixelSecured(center.x + y, center.y - x, color);
	}
}

void CCircle::DrawSelected(CBackBuffer *pDC, POINT WindowsSize){

	POINT center, tangent;
	center.x = (int)m_center.x;
	center.y = (int)m_center.y;
	tangent.x = (int)m_tangente.x;
	tangent.y = (int)m_tangente.y;
	
	int dx = center.x - tangent.x;
	int dy = center.y - tangent.y;
	int r = (int)(0.5+sqrt( (double)dx * dx + dy * dy));
	int draw;

	CColor red(255,0,0);

	POINT p0, p1;
	p0.x = center.x - r;
	p0.y = center.y - r;
	p1.x = center.x - r;
	p1.y = center.y + r;
	
	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 || min(p0.x, p1.x) >= WindowsSize.x || max(p0.y, p1.y) < 0 || min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);

	p0.x = center.x - r;
	p0.y = center.y - r;
	p1.x = center.x + r;
	p1.y = center.y - r;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 || min(p0.x, p1.x) >= WindowsSize.x || max(p0.y, p1.y) < 0 || min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);

	p0.x = center.x - r;
	p0.y = center.y + r;
	p1.x = center.x + r;
	p1.y = center.y + r;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 || min(p0.x, p1.x) >= WindowsSize.x || max(p0.y, p1.y) < 0 || min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);

	p0.x = center.x + r;
	p0.y = center.y - r;
	p1.x = center.x + r;
	p1.y = center.y + r;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 || min(p0.x, p1.x) >= WindowsSize.x || max(p0.y, p1.y) < 0 || min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);


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


	p0.x = (int)m_center.x;
	p0.y = (int)m_center.y;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,other.ToCOLORREF());

	p0.x = (int)m_tangente.x;
	p0.y = (int)m_tangente.y;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,other.ToCOLORREF());

}

bool CCircle::Intersect(POINT p){
	
	POINT center, tangent, p0;
	center.x = (int)m_center.x;
	center.y = (int)m_center.y;
	tangent.x = (int)m_tangente.x;
	tangent.y = (int)m_tangente.y;
	p0.x = p.x;
	p0.y = p.y;

	double dx = center.x - tangent.x;
	double dy = center.y - tangent.y;
	double rr = dx * dx + dy * dy;
	dx = center.x - p0.x;
	dy = center.y - p0.y;
	double dd = dx * dx + dy * dy;

	return	(m_filled && dd < rr) || (!m_filled && abs(sqrt(dd) - sqrt(rr)) <= 2);
}

CPOINT2F* CCircle::IntersectControlPoint(POINT p){

	double epsilon = 4;
	
	if(abs((p.x - m_center.x)) <= epsilon && abs((p.y - m_center.y)) <= epsilon)
		return &m_center;

	if(abs((p.x - m_tangente.x)) <= epsilon && abs((p.y - m_tangente.y)) <= epsilon)
		return &m_tangente;

	return NULL;
}


void CCircle::Translate(POINT p){
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