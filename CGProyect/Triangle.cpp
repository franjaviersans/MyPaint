#include "stdafx.h"
#include "Triangle.h"
#include "Line.h"
#include <iostream>
#include <fstream>


CTriangle::CTriangle()
{
	m_p0.x = m_p0.y = 0;
	m_p1.x = m_p1.y = 0;
	m_p2.x = m_p2.y = 0;
	m_id = IM_TRIANGLE;
	m_bgcolor = 0;
	m_linecolor = 0;
	m_filled = false;
}

void CTriangle::OnDraw(CDC *pDC,POINT WindowsSize)
{

	POINT p0, p1, p2;
	p0.x = (int)(m_p0.x * WindowsSize.x);
	p0.y = (int)(m_p0.y * WindowsSize.y);
	p1.x = (int)(m_p1.x * WindowsSize.x);
	p1.y = (int)(m_p1.y * WindowsSize.y);
	p2.x = (int)(m_p2.x * WindowsSize.x);
	p2.y = (int)(m_p2.y * WindowsSize.y);


	CLine::DrawLine(p0, p1, pDC, m_linecolor);
	CLine::DrawLine(p1, p2, pDC, m_linecolor);
	CLine::DrawLine(p0, p2, pDC, m_linecolor);
}

void CTriangle::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_id;
		ar << m_p0.x;
		ar << m_p0.y;
		ar << m_p1.x;
		ar << m_p1.y;
		ar << m_p2.x;
		ar << m_p2.y;
	}
	else
	{
		ar >> m_p0.x;
		ar >> m_p0.y;
		ar >> m_p1.x;
		ar >> m_p1.y;
		ar >> m_p2.x;
		ar >> m_p2.y;
	}
}

void CTriangle::Draw8Points(int x, int y, POINT center, COLORREF color, CDC *pDC){
	pDC->SetPixel(center.x + x,	center.y + y, color);
	pDC->SetPixel(center.x - x,	center.y + y, color);
	pDC->SetPixel(center.x - x, center.y - y, color);
	pDC->SetPixel(center.x + x, center.y - y, color);
	pDC->SetPixel(center.x + y, center.y + x, color);
	pDC->SetPixel(center.x - y, center.y + x, color);
	pDC->SetPixel(center.x - y, center.y - x, color);
	pDC->SetPixel(center.x + y, center.y - x, color);
}


void CTriangle::DrawSelected(CDC *pDC, POINT WindowsSize){
	POINT p0, p1, p2;
	p0.x = (int)(m_p0.x * WindowsSize.x);
	p0.y = (int)(m_p0.y * WindowsSize.y);
	p1.x = (int)(m_p1.x * WindowsSize.x);
	p1.y = (int)(m_p1.y * WindowsSize.y);
	p2.x = (int)(m_p2.x * WindowsSize.x);
	p2.y = (int)(m_p2.y * WindowsSize.y);

	POINT pp0, pp1;
	pp0.x = min(p0.x, min(p1.x, p2.x));
	pp0.y = min(p0.y, min(p1.y, p2.y));
	pp1.x = max(p0.x, max(p1.x, p2.x));
	pp1.y = max(p0.y, max(p1.y, p2.y));
	



	//Draw filled figured
	//TODO 
	if(m_filled){
		//CBrush brushBlue(m_bgcolor);
		//CBrush* pOldBrush = pDC->SelectObject(&brushBlue);

		//pDC->SelectObject(pOldBrush);
	}



	// create and select a thick, black pen
	CPen penBlack;
	penBlack.CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&penBlack);

	// draw a thick black rectangle filled with blue
	p0.x = pp0.x;
	p0.y = pp0.y;
	p1.x = pp1.x;
	p1.y = pp0.y;

	pDC->MoveTo(p0);
	pDC->LineTo(p1);

	p0.x = pp0.x;
	p0.y = pp0.y;
	p1.x = pp0.x;
	p1.y = pp1.y;

	pDC->MoveTo(p0);
	pDC->LineTo(p1);

	p0.x = pp0.x;
	p0.y = pp1.y;
	p1.x = pp1.x;
	p1.y = pp1.y;

	pDC->MoveTo(p0);
	pDC->LineTo(p1);

	p0.x = pp1.x;
	p0.y = pp0.y;
	p1.x = pp1.x;
	p1.y = pp1.y;

	pDC->MoveTo(p0);
	pDC->LineTo(p1);

	pDC->SelectObject(pOldPen);

	// create and select a solid green brush
	CBrush brushBlue(RGB(0, 255, 0));
	CBrush* pOldBrush = pDC->SelectObject(&brushBlue);

	p0.x = pp0.x;
	p0.y = pp0.y;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5);

	p0.x = pp0.x;
	p0.y = pp1.y;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5);

	p0.x = pp1.x;
	p0.y = pp1.y;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5);

	p0.x = pp1.x;
	p0.y = pp0.y;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5);



	// put back the old objects
	pDC->SelectObject(pOldBrush);


	// create and select a solid green brush
	CBrush brushOrange(RGB(255, 100, 0));
	pOldBrush = pDC->SelectObject(&brushOrange);


	p0.x = (int)(m_p0.x * WindowsSize.x);
	p0.y = (int)(m_p0.y * WindowsSize.y);
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5);

	p0.x = (int)(m_p1.x * WindowsSize.x);
	p0.y = (int)(m_p1.y * WindowsSize.y);
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5);

	p0.x = (int)(m_p2.x * WindowsSize.x);
	p0.y = (int)(m_p2.y * WindowsSize.y);
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5);


	// put back the old objects
	pDC->SelectObject(pOldBrush);
}


bool CTriangle::Intersect(CPOINT2F p){

	CPOINT2F p0, p1;
	p0.x = min(m_p0.x, min(m_p1.x, m_p2.x));
	p0.y = min(m_p0.y, min(m_p1.y, m_p2.y));
	p1.x = max(m_p0.x, max(m_p1.x, m_p2.x));
	p1.y = max(m_p0.y, max(m_p1.y, m_p2.y));

	if((p0.x <= p.x && p.x <= p1.x) && 
		(p0.y <= p.y && p.y <= p1.y))
		return true;
	else 
		return false;
}

CPOINT2F* CTriangle::IntersectControlPoint(CPOINT2F p){
	double epsilon = 0.02;

	if(abs((p.x - m_p0.x)) <= epsilon && abs((p.y - m_p0.y)) <= epsilon)
		return &m_p0;

	if(abs((p.x - m_p1.x)) <= epsilon && abs((p.y - m_p1.y)) <= epsilon)
		return &m_p1;

	if(abs((p.x - m_p2.x)) <= epsilon && abs((p.y - m_p2.y)) <= epsilon)
		return &m_p2;

	return NULL;
}


void CTriangle::Translate(CPOINT2F p){
	m_p0.x += p.x;
	m_p0.y += p.y;
	m_p1.x += p.x;
	m_p1.y += p.y;
	m_p2.x += p.x;
	m_p2.y += p.y;
}

void CTriangle::ChangeFillColor(COLORREF c){
	m_bgcolor = c;
}

void CTriangle::ChangeLineColor(COLORREF c){
	m_linecolor = c;
}

void CTriangle::ChangeFilled(){
	m_filled = !m_filled;
}