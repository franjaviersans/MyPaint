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

void CLine::DrawLine(POINT p0, POINT p1, CDC *pDC, COLORREF color){
	//pDC->MoveTo(m_p1);
	//pDC->LineTo(m_p2);

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
	
	if(!invert) pDC->SetPixel(x, y, color);
	else		pDC->SetPixel(y, x, color);

	while(x < p1.x){
		if(d <= 0){
			d += IncD2;
			y += inc1;
		}else{
			d += IncD1;
			y += inc2;
		}
		++x;

		if(!invert) pDC->SetPixel(x, y, color);
		else pDC->SetPixel(y, x, color);
	}
}


void CLine::OnDraw(CDC *pDC, POINT WindowsSize)
{
	
	POINT p0, p1;
	p0.x = (int)(m_p1.x * WindowsSize.x);
	p0.y = (int)(m_p1.y * WindowsSize.y);
	p1.x = (int)(m_p2.x * WindowsSize.x);
	p1.y = (int)(m_p2.y * WindowsSize.y);

	CLine::DrawLine(p0, p1, pDC, m_linecolor);
}

void CLine::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_id;
		ar << m_p1.x;
		ar << m_p1.y;
		ar << m_p2.x;
		ar << m_p2.y;
	}
	else
	{
		ar >> m_p1.x;
		ar >> m_p1.y;
		ar >> m_p2.x;
		ar >> m_p2.y;
	}
}

void CLine::DrawSelected(CDC *pDC, POINT WindowsSize){
	POINT p0, p1;
	p0.x = (int)(m_p1.x * WindowsSize.x);
	p0.y = (int)(m_p1.y * WindowsSize.y);
	p1.x = (int)(m_p2.x * WindowsSize.x);
	p1.y = (int)(m_p2.y * WindowsSize.y);


	// create and select a solid green brush
	CBrush brushOrange(RGB(255, 100, 0));
	CBrush* pOldBrush = pDC->SelectObject(&brushOrange);

	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5);
	pDC->Rectangle(p1.x - 5, p1.y - 5, p1.x + 5, p1.y + 5);

	// put back the old objects
	pDC->SelectObject(pOldBrush);

}

bool CLine::Intersect(CPOINT2F p){
	double epsilon = 0.02;
	if(abs((p.x - m_p1.x) * (m_p2.y - m_p1.y)  - (p.y - m_p1.y) * (m_p2.x - m_p1.x)) <= epsilon 
		&& ((m_p1.x <= p.x && p.x <= m_p2.x) || (m_p2.x <= p.x && p.x <= m_p1.x)) 
		&& ((m_p1.y <= p.y && p.y <= m_p2.y) || (m_p2.y <= p.y && p.y <= m_p1.y)))
		return true;
	else
		return false;
}

CPOINT2F* CLine::IntersectControlPoint(CPOINT2F p){
	double epsilon = 0.02;
	if(abs((p.x - m_p1.x)) <= epsilon && abs((p.y - m_p1.y)) <= epsilon)
		return &m_p1;

	if(abs((p.x - m_p2.x)) <= epsilon && abs((p.y - m_p2.y)) <= epsilon)
		return &m_p2;

	return NULL;
}

void CLine::Translate(CPOINT2F p){
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