#include "stdafx.h"
#include "Ellipse.h"
#include "Line.h"
#include <iostream>
#include <fstream>

CEllipse::CEllipse()
{
	m_p1.x = m_p1.y = 0;
	m_p2.x = m_p2.y = 0;
	m_id = IM_ELLIPSE;
	m_bgcolor = 0;
	m_linecolor = 0;
	m_filled = false;
}

void CEllipse::OnDraw(CBackBuffer *pDC, POINT WindowsSize)
{
	if(m_filled) OnDraw(pDC,WindowsSize, true);
	OnDraw(pDC,WindowsSize, false);
}

void CEllipse::OnDraw(CBackBuffer *pDC, POINT WindowsSize, bool filled)
{
	POINT p0, p1;
	p0.x = (int)m_p1.x;
	p0.y = (int)m_p1.y;
	p1.x = (int)m_p2.x;
	p1.y = (int)m_p2.y;
	
	POINT center;

	int draw;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 || min(p0.x, p1.x) >= WindowsSize.x || max(p0.y, p1.y) < 0 || min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;

	//If the figure must be draw
	if(draw != 0){
		int a, b, x, y, d, aa, bb, incx, incy, deltaincx, deltaincy, anty = -1;
		a			= abs((int)(p1.x - p0.x)) >> 1;
		b			= abs((int)(p1.y - p0.y)) >> 1;
		aa			= a * a;
		bb			= b * b;
		center.x	= (p1.x + p0.x) >> 1;
		center.y	= (p1.y + p0.y) >> 1;

		//Draw filled figured

		//Block 1
		x = 0;
		y = b;
		d = ((b * (b - aa)) << 2) + aa;

		incx		= (3 * bb) << 2;
		deltaincx	= bb << 3;
		incy		= (aa * (1 - b)) << 3;
		deltaincy	= aa << 3;

		anty = y;

		//Draw the 4 points of the ellipse
		if(m_filled)	EllipsePointsFilled(x,y,center, m_linecolor, pDC, draw);
		EllipsePoints(x,y,center, m_linecolor, pDC, draw);

		while (((bb * (x + 1)) << 1) < aa * ((y << 1) - 1)) {
			if (d < 0) {
				d += incx;
			}else{
				d += incx + incy;
				incy += deltaincy;
				--y;
			}
			++x;
			incx += deltaincx; 
			if(m_filled && anty != y)	EllipsePointsFilled(x,y,center, m_linecolor, pDC, draw);
			EllipsePoints(x,y,center, m_linecolor, pDC, draw);
			anty = y;
		}

	
		//Block 2
		incx		= (bb * x + bb) << 3;
		deltaincx	= bb << 3;
		incy		= (((-aa * y)<< 1) + 3 * aa) << 2;
		deltaincy	= aa << 3;
		d			= bb * (((x * x) << 2) + (x << 2) + 1)+ ((aa * y * y - (y << 1) + 1) << 2) - ((aa * bb) << 2);

		while (y>0){
			if (d < 0){
				d += incx + incy;
				incx += deltaincx;
				++x;
			}else{
				d += incy;
			}
			--y;
			incy += deltaincy;
			if(m_filled && anty != y)	EllipsePointsFilled(x,y,center, m_linecolor, pDC, draw);
			EllipsePoints(x,y,center, m_linecolor, pDC, draw);
			anty = y;
		}
	}

}


void CEllipse::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_id;
		ar << m_bgcolor;
		ar << m_linecolor;
		ar << m_filled;
		ar << m_p1.x;
		ar << m_p1.y;
		ar << m_p2.x;
		ar << m_p2.y;
	}
	else
	{
		ar >> m_bgcolor;
		ar >> m_linecolor;
		ar >> m_filled;
		ar >> m_p1.x;
		ar >> m_p1.y;
		ar >> m_p2.x;
		ar >> m_p2.y;
	}
}

void CEllipse::EllipsePoints(int x, int y, POINT center, COLORREF color, CBackBuffer *pDC, int draw){
	if(draw == 2){
		pDC->SetPixel(center.x + x,	center.y + y, color);
		pDC->SetPixel(center.x - x,	center.y + y, color);
		pDC->SetPixel(center.x - x, center.y - y, color);
		pDC->SetPixel(center.x + x, center.y - y, color);
	}else{
		pDC->SetPixelSecured(center.x + x,	center.y + y, color);
		pDC->SetPixelSecured(center.x - x,	center.y + y, color);
		pDC->SetPixelSecured(center.x - x, center.y - y, color);
		pDC->SetPixelSecured(center.x + x, center.y - y, color);
	}
}


void CEllipse::EllipsePointsFilled(int x, int y, POINT center, COLORREF color, CBackBuffer *pDC, int draw){
	if(draw != 0){
		pDC->FillLine(center.x + x, center.y + y, center.x - x, center.y + y, m_bgcolor);
		pDC->FillLine(center.x + x, center.y - y, center.x - x, center.y - y, m_bgcolor);
	}
}


void CEllipse::DrawSelected(CBackBuffer *pDC, POINT WindowsSize){
	POINT pp0, pp1;
	pp0.x = (int)m_p1.x;
	pp0.y = (int)m_p1.y;
	pp1.x = (int)m_p2.x;
	pp1.y = (int)m_p2.y;

	CColor red(255,0,0);

	POINT p0, p1;
	p0.x = pp0.x;
	p0.y = pp0.y;
	p1.x = pp1.x;
	p1.y = pp0.y;

	int draw;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 || min(p0.x, p1.x) >= WindowsSize.x || max(p0.y, p1.y) < 0 || min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);

	p0.x = pp0.x;
	p0.y = pp0.y;
	p1.x = pp0.x;
	p1.y = pp1.y;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 || min(p0.x, p1.x) >= WindowsSize.x || max(p0.y, p1.y) < 0 || min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);

	p0.x = pp0.x;
	p0.y = pp1.y;
	p1.x = pp1.x;
	p1.y = pp1.y;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 || min(p0.x, p1.x) >= WindowsSize.x || max(p0.y, p1.y) < 0 || min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);

	p0.x = pp1.x;
	p0.y = pp0.y;
	p1.x = pp1.x;
	p1.y = pp1.y;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 || min(p0.x, p1.x) >= WindowsSize.x || max(p0.y, p1.y) < 0 || min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);


	CColor green(0, 255, 0);

	p0.x = pp0.x;
	p0.y = pp0.y;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,green.ToCOLORREF());

	p0.x = pp0.x;
	p0.y = pp1.y;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,green.ToCOLORREF());

	p0.x = pp1.x;
	p0.y = pp1.y;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,green.ToCOLORREF());

	p0.x = pp1.x;
	p0.y = pp0.y;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,green.ToCOLORREF());


	CColor other(255, 100, 0);

	p0.x = (int)m_p1.x;
	p0.y = (int)m_p1.y;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,other.ToCOLORREF());

	p0.x = (int)m_p2.x;
	p0.y = (int)m_p2.y;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,other.ToCOLORREF());
}

bool CEllipse::Intersect(POINT p){

	
	CPOINT2F center, axis, p0(p);
	center.x = (m_p1.x + m_p2.x)/2.0f;
	center.y = (m_p1.y + m_p2.y)/2.0f;
	axis.x = abs(m_p1.x - center.x);
	axis.y = abs(m_p1.y - center.y);

	axis.x = axis.x * axis.x;
	axis.y  = axis.y * axis.y ;
	double dx = p0.x - center.x;
	double dy = p0.y - center.y;
	dx = dx * dx;
	dy = dy * dy;
	dx = dx / axis.x + dy / axis.y;

	return	(m_filled && dx <= 1) || (!m_filled && abs(dx - 1) <= 0.2);
}

CPOINT2F* CEllipse::IntersectControlPoint(POINT p){
	double epsilon = 4;

	if(abs((p.x - m_p1.x)) <= epsilon && abs((p.y - m_p1.y)) <= epsilon)
		return &m_p1;

	if(abs((p.x - m_p2.x)) <= epsilon && abs((p.y - m_p2.y)) <= epsilon)
		return &m_p2;

	return NULL;
}

void CEllipse::Translate(POINT p){
	m_p1.x += p.x;
	m_p1.y += p.y;
	m_p2.x += p.x;
	m_p2.y += p.y;
}

void CEllipse::ChangeFillColor(COLORREF c){
	m_bgcolor = c;
}

void CEllipse::ChangeLineColor(COLORREF c){
	m_linecolor = c;
}

void CEllipse::ChangeFilled(){
	m_filled = !m_filled;
}