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

	m_c0.setColor(255,0,0);
	m_c1.setColor(0,255,0);
	m_c2.setColor(0,0,255);

	m_id = IM_TRIANGLE;

	m_bgcolor = 0;
	m_linecolor = 0;
	m_filled = false;
}

void CTriangle::OnDraw(CBackBuffer *pDC,POINT WindowsSize)
{

	POINT p0, p1, p2;
	p0.x = (int)(m_p0.x * WindowsSize.x);
	p0.y = (int)(m_p0.y * WindowsSize.y);
	p1.x = (int)(m_p1.x * WindowsSize.x);
	p1.y = (int)(m_p1.y * WindowsSize.y);
	p2.x = (int)(m_p2.x * WindowsSize.x);
	p2.y = (int)(m_p2.y * WindowsSize.y);


	//Draw filled figured
	//TODO 
	if(m_filled) ScanLine(pDC, WindowsSize);

	CLine::DrawLine(p0, p1, pDC, m_linecolor);
	CLine::DrawLine(p1, p2, pDC, m_linecolor);
	CLine::DrawLine(p0, p2, pDC, m_linecolor);
}

void CTriangle::ScanLine(CBackBuffer *pDC, POINT WindowsSize){
	POINT p0, p1, p2;

	//Transform the coordinates to integers
	p0.x = (int)(m_p0.x * WindowsSize.x);
	p0.y = (int)(m_p0.y * WindowsSize.y);
	p1.x = (int)(m_p1.x * WindowsSize.x);
	p1.y = (int)(m_p1.y * WindowsSize.y);
	p2.x = (int)(m_p2.x * WindowsSize.x);
	p2.y = (int)(m_p2.y * WindowsSize.y);

	int y, xmin, xmax, x;
	float m1, m2, cy, cx;
	CColor colorPoint0(m_c0), colorPoint1(m_c1), colorPoint2(m_c2), colorAux(0,0,0),
			colorDif0, colorDif1, colorDif2, colorInc0, colorInc1, colorInc2;
	bool mb1 = false, mb2 = false;


	//Sort the points
	if(p2.y < p1.y){
		std::swap(p2,p1);
		std::swap(colorPoint2, colorPoint1);
	}
	if(p1.y < p0.y){
		std::swap(p0,p1);
		std::swap(colorPoint0, colorPoint1);
	}
	if(p2.y < p1.y){
		std::swap(p1,p2);
		std::swap(colorPoint1, colorPoint2);
	}


	//Break the larger line in two and interpolate its color
	cy = (p2.y - p0.y == 0)?0.5f:((float)(p1.y - p0.y)/(p2.y - p0.y));
	colorAux = colorPoint2 * cy + colorPoint0 * (1 - cy);

	cy = (p1.y - p0.y == 0)?0.5f:(1.0f/(p1.y - p0.y));
	colorDif0 = colorPoint0;
	colorInc0 = colorPoint1 - colorPoint0;

	colorDif1 = colorPoint0;
	colorInc1 = colorAux - colorPoint0;

	//Paint first half
	//Calculate the slope of p0 and p1
	if(p0.x - p1.x == 0) mb1 = true;
	else m1 = (float) (p0.y - p1.y)/(p0.x - p1.x);

	//Calculate the slope of p0 and p2
	if(p0.x - p2.x == 0) mb2 = true;
	else m2 = (float)  (p0.y - p2.y)/(p0.x - p2.x);
	

	//Go throught every y
	for(y = p0.y; y < p1.y; ++y){
		xmin = (int)((!mb1?((float) (y - p0.y) / m1):0) + p0.x);
		xmax = (int)((!mb2?((float) (y - p0.y) / m2):0) + p0.x);

		if(xmax < xmin){
			std::swap(xmin, xmax);
			colorDif2 = colorDif1;
			colorInc2 = colorDif0 - colorDif1;
		}else{
			colorDif2 = colorDif0;
			colorInc2 = colorDif1 - colorDif0;
		}

		cx = (xmax - xmin == 0)? 0.5f:(1.0f/(xmax - xmin));

		//Go throught every x
		for(x = xmin; x < xmax; ++x){
			pDC->SetPixel(x, y, colorDif2.ToCOLORREF());
			colorDif2 = colorDif2 + colorInc2 * cx;
		}

		colorDif0 = colorDif0 + colorInc0 * cy;
		colorDif1 = colorDif1 + colorInc1 * cy;
	}

	

	//Paint second half
	cy = (p2.y - p1.y == 0)? 0.5f :(1.0f/(p2.y - p1.y));
	colorDif0 = colorPoint1;
	colorInc0 = colorPoint2 - colorPoint1;

	colorDif1 = colorAux;
	colorInc1 = colorPoint2 - colorAux;

	//Calculate the slope of p0 and p1
	if(p2.x - p1.x == 0) mb1 = true;
	else m1 = (float) (p2.y - p1.y)/(p2.x - p1.x);

	//Calculate the slope of p0 and p2
	if(p2.x - p0.x == 0) mb2 = true;
	else m2 = (float)  (p2.y - p0.y)/(p2.x - p0.x);

	//Go throught every y
	for(y = p1.y; y < p2.y; ++y){
		xmin = (int)((!mb1?((float) (y - p2.y) / m1):0) + p2.x);
		xmax = (int)((!mb2?((float) (y - p2.y) / m2):0) + p2.x);

		if(xmax < xmin){
			std::swap(xmin, xmax);
			colorDif2 = colorDif1;
			colorInc2 = colorDif0 - colorDif1;
		}else{
			colorDif2 = colorDif0;
			colorInc2 = colorDif1 - colorDif0;
		}

		cx = (xmax - xmin == 0)? 0.5f: (1.0f/(xmax - xmin));

		//Go throught every x
		for(x = xmin; x < xmax; ++x){
			pDC->SetPixel(x, y, colorDif2.ToCOLORREF());

			colorDif2 = colorDif2 + colorInc2 * cx;
		}

		colorDif0 = colorDif0 + colorInc0 * cy;
		colorDif1 = colorDif1 + colorInc1 * cy;
	}

}

void CTriangle::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_id;
		ar << m_bgcolor;
		ar << m_linecolor;
		ar << m_filled;
		ar << m_p0.x;
		ar << m_p0.y;
		ar << m_p1.x;
		ar << m_p1.y;
		ar << m_p2.x;
		ar << m_p2.y;
		m_c0.Serialize(ar);
		m_c1.Serialize(ar);
		m_c2.Serialize(ar);
	}
	else
	{
		ar >> m_bgcolor;
		ar >> m_linecolor;
		ar >> m_filled;
		ar >> m_p0.x;
		ar >> m_p0.y;
		ar >> m_p1.x;
		ar >> m_p1.y;
		ar >> m_p2.x;
		ar >> m_p2.y;
		m_c0.Serialize(ar);
		m_c1.Serialize(ar);
		m_c2.Serialize(ar);
	}
}

void CTriangle::DrawSelected(CBackBuffer *pDC, POINT WindowsSize){
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
	


	// create and select a thick, black pen
	CColor red(255,0,0);

	// draw a thick black rectangle filled with blue
	p0.x = pp0.x;
	p0.y = pp0.y;
	p1.x = pp1.x;
	p1.y = pp0.y;

	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF());;

	p0.x = pp0.x;
	p0.y = pp0.y;
	p1.x = pp0.x;
	p1.y = pp1.y;

	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF());;

	p0.x = pp0.x;
	p0.y = pp1.y;
	p1.x = pp1.x;
	p1.y = pp1.y;

	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF());

	p0.x = pp1.x;
	p0.y = pp0.y;
	p1.x = pp1.x;
	p1.y = pp1.y;

	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF());


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


	p0.x = (int)(m_p0.x * WindowsSize.x);
	p0.y = (int)(m_p0.y * WindowsSize.y);
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,other.ToCOLORREF());

	p0.x = (int)(m_p1.x * WindowsSize.x);
	p0.y = (int)(m_p1.y * WindowsSize.y);
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,other.ToCOLORREF());

	p0.x = (int)(m_p2.x * WindowsSize.x);
	p0.y = (int)(m_p2.y * WindowsSize.y);
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,other.ToCOLORREF());

}


float CTriangle::sign(CPOINT2F p1,CPOINT2F p2,CPOINT2F p3){
		return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y); 
}

bool CTriangle::Intersect(CPOINT2F p, POINT WindowsSize){
	double epsilon = (WindowsSize.x > WindowsSize.y)? 2.0/WindowsSize.x : 2.0/WindowsSize.y;
	
	double	sign1, sign2, sign3;
	
	if(!m_filled){
		sign1 = abs((p.x - m_p1.x) * (m_p2.y - m_p1.y)  - (p.y - m_p1.y) * (m_p2.x - m_p1.x));
		sign2 = abs((p.x - m_p0.x) * (m_p1.y - m_p0.y)  - (p.y - m_p0.y) * (m_p1.x - m_p0.x));
		sign3 = abs((p.x - m_p2.x) * (m_p0.y - m_p2.y)  - (p.y - m_p2.y) * (m_p0.x - m_p2.x));

		//Intersect with first line
		CPOINT2F p0, p1;
		p0.x = min(m_p1.x, m_p2.x);
		p0.y = min(m_p1.y, m_p2.y);
		p1.x = max(m_p1.x, m_p2.x);
		p1.y = max(m_p1.y, m_p2.y);

		if( sign1 <= epsilon 
			&& ((p0.x <= p.x && p.x <= p1.x) || (p0.x <= p.x && p.x <= p1.x)) 
			&& ((p0.y <= p.y && p.y <= p1.y) || (p0.y <= p.y && p.y <= p1.y)))
			return true;
		
		p0.x = min(m_p1.x, m_p0.x);
		p0.y = min(m_p1.y, m_p0.y);
		p1.x = max(m_p1.x, m_p0.x);
		p1.y = max(m_p1.y, m_p0.y);

		//Intersect with second line
		if( sign2 <= epsilon 
			&& ((p0.x <= p.x && p.x <= p1.x) || (p0.x <= p.x && p.x <= p1.x)) 
			&& ((p0.y <= p.y && p.y <= p1.y) || (p0.y <= p.y && p.y <= p1.y)))
			return true;

		p0.x = min(m_p0.x, m_p2.x);
		p0.y = min(m_p0.y, m_p2.y);
		p1.x = max(m_p0.x, m_p2.x);
		p1.y = max(m_p0.y, m_p2.y);
		
		//Intersect with third line
		if( sign3 <= epsilon 
			&& ((p0.x <= p.x && p.x <= p1.x) || (p0.x <= p.x && p.x <= p1.x)) 
			&& ((p0.y <= p.y && p.y <= p1.y) || (p0.y <= p.y && p.y <= p1.y)))
			return true;

		return false;
	}else {
		sign1 = sign(p, m_p0, m_p1);
		sign2 = sign(p, m_p1, m_p2);
		sign3 = sign(p, m_p2, m_p0);

		//Check if the point is inside triangle
		bool	b1 = sign1 < 0.0f,
				b2 = sign2 < 0.0f,
				b3 = sign3 < 0.0f;
		return ((b1 == b2) && (b2 == b3));
	}
}

CPOINT2F* CTriangle::IntersectControlPoint(CPOINT2F p, POINT WindowsSize){
	double epsilon = (WindowsSize.x > WindowsSize.y)? 4.0/WindowsSize.x : 4.0/WindowsSize.y;

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