#include "stdafx.h"
#include "Line.h"
#include <iostream>

CLine::CLine()
{
	m_p1.x	= m_p1.y = 0;
	m_p2.x	= m_p2.y = 0;
	m_id	= 	IM_LINE;
	m_bgcolor = 0;
	m_linecolor = 0;
	m_filled = false;
}

void CLine::DrawLine(POINT p0, POINT p1, CBackBuffer *pDC, COLORREF color, int draw){
	if(draw != 0){
		bool invert = false;
		int dx, dy, x, y, d, IncD1, IncD2, inc1 = 1, inc2 = 0;

		if(abs(p1.x - p0.x) < abs(p1.y - p0.y)){
			std::swap(p0.x,p0.y);
			std::swap(p1.x,p1.y);
			invert = true;
		}

		if(p1.x <= p0.x)
			std::swap(p1, p0);

		dx = p1.x - p0.x;
		dy = p1.y - p0.y;

		if(dy <= 0){
			dx = -dx;
			IncD2	= - (dy << 1);
			IncD1	= (dx - dy) << 1;
			inc2	= -1;
			inc1	= 0;
		}else{
			d		= dx - (dy << 1);
			IncD1	= - (dy << 1);
			IncD2	= (dx - dy) << 1;
		}

		d	= dx - (dy << 1);
		x	= p0.x;
		y	= p0.y;
	
		//Normal draw
		if(draw == 2)
			if(!invert) pDC->SetPixel(x, y, color);
			else		pDC->SetPixel(y, x, color);
		else //Secure draw
			if(!invert) pDC->SetPixelSecured(x, y, color);
			else		pDC->SetPixelSecured(y, x, color);

		while(x < p1.x){
			if(d <= 0){
				d += IncD2;
				y += inc1;
			}else{
				d += IncD1;
				y += inc2;
			}
			++x;

			//Normal draw
			if(draw == 2)
				if(!invert) pDC->SetPixel(x, y, color);
				else		pDC->SetPixel(y, x, color);
			else //Secure draw
				if(!invert) pDC->SetPixelSecured(x, y, color);
				else		pDC->SetPixelSecured(y, x, color);
		}
	}
}

void CLine::DrawDottedLine(POINT p0, POINT p1, CBackBuffer *pDC, COLORREF color, int draw){
	if(draw != 0){
		boolean mask[] = {true,true,true,false,false,false,true,true,true,false,false,false};
		int masksize = 12, maskind = 0;

		bool invert = false;
		int dx, dy, x, y, d, IncD1, IncD2, inc1 = 1, inc2 = 0;

		if(abs(p1.x - p0.x) < abs(p1.y - p0.y)){
			std::swap(p0.x,p0.y);
			std::swap(p1.x,p1.y);
			invert = true;
		}

		if(p1.x <= p0.x)
			std::swap(p1, p0);

		dx = p1.x - p0.x;
		dy = p1.y - p0.y;

		if(dy <= 0){
			dx = -dx;
			IncD2	= - (dy << 1);
			IncD1	= (dx - dy) << 1;
			inc2	= -1;
			inc1	= 0;
		}else{
			d		= dx - (dy << 1);
			IncD1	= - (dy << 1);
			IncD2	= (dx - dy) << 1;
		}

		d	= dx - (dy << 1);
		x	= p0.x;
		y	= p0.y;
	
		//Normal draw
		if(draw == 2)
			if(!invert) pDC->SetPixel(x, y, color);
			else		pDC->SetPixel(y, x, color);
		else //Secure draw
			if(!invert) pDC->SetPixelSecured(x, y, color);
			else		pDC->SetPixelSecured(y, x, color);

		while(x < p1.x){
			if(d <= 0){
				d += IncD2;
				y += inc1;
			}else{
				d += IncD1;
				y += inc2;
			}
			++x;

			if(mask[maskind]){
				//Normal draw
				if(draw == 2)
					if(!invert) pDC->SetPixel(x, y, color);
					else		pDC->SetPixel(y, x, color);
				else //Secure draw
					if(!invert) pDC->SetPixelSecured(x, y, color);
					else		pDC->SetPixelSecured(y, x, color);
			}
			maskind = (maskind++) % masksize;
		}
	}
}


void CLine::OnDraw(CBackBuffer *pDC, POINT WindowsSize)
{
	
	POINT p0, p1;
	p0.x = (int)m_p1.x;
	p0.y = (int)m_p1.y;
	p1.x = (int)m_p2.x;
	p1.y = (int)m_p2.y;

	int draw;

	//Check if the figure is inside the drawing area
	if(max(p0.x,p1.x) < 0 || min(p0.x,p1.x) >= WindowsSize.x || max(p0.y,p1.y) < 0 || min(p0.y,p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawLine(p0, p1, pDC, m_linecolor, draw);
}

void CLine::Serialize(CArchive& ar)
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

void CLine::DrawSelected(CBackBuffer *pDC, POINT WindowsSize){
	POINT p0, p1;
	p0.x = (int)m_p1.x;
	p0.y = (int)m_p1.y;
	p1.x = (int)m_p2.x;
	p1.y = (int)m_p2.y;


	CColor other(255, 100, 0);

	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,other.ToCOLORREF());
	pDC->Rectangle(p1.x - 5, p1.y - 5, p1.x + 5, p1.y + 5,other.ToCOLORREF());
}

bool CLine::Intersect(POINT p){
	double epsilon = 4;

	CPOINT2F p1, p0;
	p0.x = min(m_p2.x, m_p1.x);
	p0.y = min(m_p2.y, m_p1.y);
	p1.x = max(m_p2.x, m_p1.x);
	p1.y = max(m_p2.y, m_p1.y);

	float dx = m_p2.x - m_p1.x, dy = m_p2.y - m_p1.y;

	return (abs((p.x - m_p1.x) * dy - (p.y - m_p1.y) * dx) / sqrt(dx * dx + dy * dy)  <= epsilon)
			&& (p0.x <= p.x && p.x <= p1.x) 
			&& (p0.y <= p.y && p.y <= p1.y);
}

CPOINT2F* CLine::IntersectControlPoint(POINT p){
	double epsilon = 4;

	if(abs(p.x - m_p1.x) <= epsilon && abs(p.y - m_p1.y) <= epsilon)
		return &m_p1;

	if(abs(p.x - m_p2.x) <= epsilon && abs(p.y - m_p2.y) <= epsilon)
		return &m_p2;

	return NULL;
}

void CLine::Translate(POINT p){
	m_p1.x += p.x;
	m_p1.y += p.y;
	m_p2.x += p.x;
	m_p2.y += p.y;
}

void CLine::ChangeFillColor(COLORREF c){
	m_bgcolor = c;
}

void CLine::ChangeLineColor(COLORREF c){
	m_linecolor = c;
}

void CLine::ChangeFilled(){
	m_filled = !m_filled;
}