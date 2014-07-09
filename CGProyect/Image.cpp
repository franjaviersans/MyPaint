#include "stdafx.h"
#include "Image.h"
#include "Line.h"
#include <iostream>
#include <fstream>

CMyImage::CMyImage()
{
	m_p1.x = m_p1.y = 0;
	m_p2.x = m_p2.y = 0;
	m_id = IM_IMAGE;
	m_bgcolor = 0;
	m_linecolor = 0;
	m_filled = false;
}

void CMyImage::OnDraw(CBackBuffer *pDC, POINT WindowsSize)
{
	
}

void CMyImage::Serialize(CArchive& ar)
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

void CMyImage::DrawSelected(CBackBuffer *pDC, POINT WindowsSize){
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
	if(max(p0.x, p1.x) < 0 && min(p0.x, p1.x) >= WindowsSize.x && max(p0.y, p1.y) < 0 && min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);

	p0.x = pp0.x;
	p0.y = pp0.y;
	p1.x = pp0.x;
	p1.y = pp1.y;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 && min(p0.x, p1.x) >= WindowsSize.x && max(p0.y, p1.y) < 0 && min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);

	p0.x = pp0.x;
	p0.y = pp1.y;
	p1.x = pp1.x;
	p1.y = pp1.y;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 && min(p0.x, p1.x) >= WindowsSize.x && max(p0.y, p1.y) < 0 && min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);

	p0.x = pp1.x;
	p0.y = pp0.y;
	p1.x = pp1.x;
	p1.y = pp1.y;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 && min(p0.x, p1.x) >= WindowsSize.x && max(p0.y, p1.y) < 0 && min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
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

bool CMyImage::Intersect(POINT p){

	
	return false;
	/*CPOINT2F center, axis, p0(p);
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

	return	(m_filled && dx <= 1) || (!m_filled && abs(dx - 1) <= 0.2);*/
}

CPOINT2F* CMyImage::IntersectControlPoint(POINT p){
	double epsilon = 4;

	if(abs((p.x - m_p1.x)) <= epsilon && abs((p.y - m_p1.y)) <= epsilon)
		return &m_p1;

	if(abs((p.x - m_p2.x)) <= epsilon && abs((p.y - m_p2.y)) <= epsilon)
		return &m_p2;

	return NULL;
}

void CMyImage::Translate(POINT p){
	m_p1.x += p.x;
	m_p1.y += p.y;
	m_p2.x += p.x;
	m_p2.y += p.y;
}

void CMyImage::ChangeFillColor(COLORREF c){
}

void CMyImage::ChangeLineColor(COLORREF c){
}

void CMyImage::ChangeFilled(){
}