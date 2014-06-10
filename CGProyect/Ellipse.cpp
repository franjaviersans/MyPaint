#include "stdafx.h"
#include "Ellipse.h"
#include <iostream>
#include <fstream>

CEllipse::CEllipse()
{
	m_p1.x = m_p1.y = 0;
	m_p2.x = m_p2.y = 0;
	m_id = IM_ELLIPSE;
}

void CEllipse::OnDraw(CDC *pDC, POINT WindowsSize)
{

	POINT p0, p1;
	p0.x = (int)(m_p1.x * WindowsSize.x);
	p0.y = (int)(m_p1.y * WindowsSize.y);
	p1.x = (int)(m_p2.x * WindowsSize.x);
	p1.y = (int)(m_p2.y * WindowsSize.y);
	
	POINT center;
	COLORREF color;
	color = 0;

	int a, b, x, y, d, aa, bb, incx, incy, deltaincx, deltaincy;
	a			= abs((int)(p1.x - p0.x)) >> 1;
	b			= abs((int)(p1.y - p0.y)) >> 1;
	aa			= a * a;
	bb			= b * b;
	center.x	= (p1.x + p0.x) >> 1;
	center.y	= (p1.y + p0.y) >> 1;

	//Block 1
	x = 0;
	y = b;
	d = ((b * (b - aa)) << 2) + aa;

	incx		= (3 * bb) << 2;
	deltaincx	= bb << 3;
	incy		= (aa * (1 - b)) << 3;
	deltaincy	= aa << 3;

	//Draw the 4 points of the ellipse
	EllipsePoints(x,y,center, color, pDC);
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
		EllipsePoints(x,y,center, color, pDC);
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
		EllipsePoints(x,y,center, color, pDC);
	}
}

void CEllipse::Serialize(CArchive& ar)
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

void CEllipse::EllipsePoints(int x, int y, POINT center, COLORREF color, CDC *pDC){
	pDC->SetPixel(center.x + x,	center.y + y, color);
	pDC->SetPixel(center.x - x,	center.y + y, color);
	pDC->SetPixel(center.x - x, center.y - y, color);
	pDC->SetPixel(center.x + x, center.y - y, color);
}

void CEllipse::DrawSelected(CDC *pDC, POINT WindowsSize){
	POINT pp0, pp1;
	pp0.x = (int)(m_p1.x * WindowsSize.x);
	pp0.y = (int)(m_p1.y * WindowsSize.y);
	pp1.x = (int)(m_p2.x * WindowsSize.x);
	pp1.y = (int)(m_p2.y * WindowsSize.y);

	// create and select a thick, black pen
	CPen penBlack;
	penBlack.CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&penBlack);

	// draw a thick black rectangle filled with blue

	POINT p0, p1;
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
}