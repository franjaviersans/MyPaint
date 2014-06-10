#include "stdafx.h"
#include "Circle.h"
#include <iostream>
#include <fstream>

CCircle::CCircle()
{
	m_center.x = m_center.y = 0;
	m_tangente.x = m_tangente.y = 0;
	m_id = IM_CIRCLE;
}

void CCircle::OnDraw(CDC *pDC, POINT WindowsSize)
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

	//pDC->Ellipse(center.x - r, center.y - r, center.x + r, center.y + r);

	COLORREF color;
	color = 0;

	int x,y,d;
	x = 0;
	y = r;
	d = 1-r;

	incx		= 3;
	delta		= 2;
	incy		= -2 * r +5;

	Draw8Points(x, y, center, color, pDC);
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
		Draw8Points(x, y, center, color, pDC);
	}
}

void CCircle::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_id;
		ar << m_center.x;
		ar << m_center.y;
		ar << m_tangente.x;
		ar << m_tangente.y;
	}
	else
	{
		ar >> m_center.x;
		ar >> m_center.y;
		ar >> m_tangente.x;
		ar >> m_tangente.y;
	}
}

void CCircle::Draw8Points(int x, int y, POINT center, COLORREF color, CDC *pDC){
	pDC->SetPixel(center.x + x,	center.y + y, color);
	pDC->SetPixel(center.x - x,	center.y + y, color);
	pDC->SetPixel(center.x - x, center.y - y, color);
	pDC->SetPixel(center.x + x, center.y - y, color);
	pDC->SetPixel(center.x + y, center.y + x, color);
	pDC->SetPixel(center.x - y, center.y + x, color);
	pDC->SetPixel(center.x - y, center.y - x, color);
	pDC->SetPixel(center.x + y, center.y - x, color);
}

void CCircle::DrawSelected(CDC *pDC, POINT WindowsSize){

	POINT center, tangent;
	center.x = (int)(m_center.x * WindowsSize.x);
	center.y = (int)(m_center.y * WindowsSize.y);
	tangent.x = (int)(m_tangente.x * WindowsSize.x);
	tangent.y = (int)(m_tangente.y * WindowsSize.y);
	
	int dx = center.x - tangent.x;
	int dy = center.y - tangent.y;
	int r = (int)(0.5+sqrt( (double)dx * dx + dy * dy));



	// create and select a thick, black pen
	CPen penBlack;
	penBlack.CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&penBlack);

	// draw a thick black rectangle filled with blue

	POINT p0, p1;
	p0.x = center.x - r;
	p0.y	= center.y - r;
	p1.x = center.x - r;
	p1.y = center.y + r;

	pDC->MoveTo(p0);
	pDC->LineTo(p1);

	p0.x = center.x - r;
	p0.y	= center.y - r;
	p1.x = center.x + r;
	p1.y = center.y - r;

	pDC->MoveTo(p0);
	pDC->LineTo(p1);

	p0.x = center.x - r;
	p0.y	= center.y + r;
	p1.x = center.x + r;
	p1.y = center.y + r;

	pDC->MoveTo(p0);
	pDC->LineTo(p1);

	p0.x = center.x + r;
	p0.y = center.y - r;
	p1.x = center.x + r;
	p1.y = center.y + r;

	pDC->MoveTo(p0);
	pDC->LineTo(p1);

	pDC->SelectObject(pOldPen);

	// create and select a solid green brush
	CBrush brushBlue(RGB(0, 255, 0));
	CBrush* pOldBrush = pDC->SelectObject(&brushBlue);

	p0.x = center.x + r;
	p0.y = center.y - r;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5);

	p0.x = center.x + r;
	p0.y = center.y + r;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5);

	p0.x = center.x - r;
	p0.y = center.y - r;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5);

	p0.x = center.x - r;
	p0.y = center.y + r;
	pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5);


	// put back the old objects
	pDC->SelectObject(pOldBrush);
	
}
