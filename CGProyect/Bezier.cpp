#include "stdafx.h"
#include "Bezier.h"
#include "Line.h"
#include <iostream>
#include <fstream>

CBezier::CBezier()
{

	arr.push_back(*(new std::vector<CPOINT2F>));
	addPoint(0,0);
	addPoint(0,0);
	/*arr[0].resize(2);
	arr[0].resize(1);
	arr[0][0].x = 0;
	arr[0][0].y = 0;
	arr[0][1].x = 0;
	arr[0][1].x = 0;*/

	m_id = IM_BEZIER;
	m_bgcolor = 0;
	m_linecolor = 0;
	m_filled = false;
}

void CBezier::OnDraw(CDC *pDC, POINT WindowsSize)
{
	POINT last;

	//Algoritmo de Casteljau
	double t;
	unsigned int r,j;
	unsigned int n=arr[0].size();
	bool first = true;


	for(t=0;t<=1;t+=0.01){
		for(r=1;r<n;++r){
			for(j=0;j<n-r;++j){
				arr[r][j].x = (float)((float) (1 - t) * arr[r-1][j].x + (float)t * arr[r-1][j+1].x);
				arr[r][j].y = (float)((float) (1 - t) * arr[r-1][j].y + (float)t * arr[r-1][j+1].y);
			}
		}

		if(n-1>0){
			POINT p0;
			if(first){
				last.x = (int)(arr[n-1][0].x * WindowsSize.x);
				last.y = (int)(arr[n-1][0].y * WindowsSize.y);
				first = false;
			}
			p0.x = last.x;
			p0.y = last.y;
			last.x = (int)(arr[n-1][0].x * WindowsSize.x);
			last.y = (int)(arr[n-1][0].y * WindowsSize.y);

			//pDC->MoveTo(p0);
			//pDC->LineTo(last);
			CLine::DrawLine(p0, last, pDC, m_linecolor);
		}
	}
}

void CBezier::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_id;
		ar << arr[0].size();
		for(unsigned int i = 0;i< arr[0].size();++i){
			ar << arr[0][i].x;
			ar << arr[0][i].y;
		}
	}
	else
	{
		int n;
		float x,y;
		ar >> n;
		arr.clear();
		arr.push_back(*(new std::vector<CPOINT2F>));
		for(int i = 0; i < n;++i){
			ar >> x;
			ar >> y;
			addPoint(x,y);
		}
	}
}

void CBezier::addPoint(float x, float y){
	CPOINT2F a;
	a.x = x;
	a.y = y;

	arr[0].push_back(a);

	unsigned int n = arr[0].size();
	unsigned int i;

	while(n > arr.size()){
		arr.push_back(*(new std::vector<CPOINT2F>));
	}

	for(i=1; i<n ;++i)
		while(arr[i].size() <= n-i){
			CPOINT2F a;
			a.x = 0;
			a.y = 0;
			arr[i].push_back(a);
		}
}

void CBezier::addControlpoint(float x, float y){
	CPOINT2F a;
	a.x = 100;
	a.y = 100;

	arr[0].push_back(a);

	unsigned int n = arr[0].size() - 1;
	unsigned int i;

	for( i = n;i > 1;--i)
		arr[0][i] = arr[0][i-1];

	arr[0][i].x = arr[0][i - 1].x * (i / (n + 1)) + (1 - (i / (n + 1))) * arr[0][i + 1].x;
	arr[0][i].y = arr[0][i - 1].y * (i / (n + 1)) + (1 - (i / (n + 1))) * arr[0][i + 1].y;


	n = arr[0].size() ;

	while(n > arr.size()){
		arr.push_back(*(new std::vector<CPOINT2F>));
	}

	for(i=1; i<n ;++i)
		while(arr[i].size() <= n-i){
			CPOINT2F a;
			a.x = 0;
			a.y = 0;
			arr[i].push_back(a);
		}
}

void CBezier::DrawSelected(CDC *pDC, POINT WindowsSize){

	POINT p0, p1, minp, maxp;

	minp.x = 99999;
	minp.y = 99999;

	maxp.x = -1000;
	maxp.y = -1000;

	CBrush brushBlue(RGB(0, 255, 0));
	CBrush* pOldBrush = pDC->SelectObject(&brushBlue);
	for(unsigned int i = 0;i< arr[0].size();++i){
		p0.x = (int)(arr[0][i].x * WindowsSize.x);
		p0.y = (int)(arr[0][i].y * WindowsSize.y);

		minp.x = min(p0.x, minp.x);
		minp.y = min(p0.y, minp.y);
		maxp.x = max(p0.x, maxp.x);
		maxp.y = max(p0.y, maxp.y);
		
		pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5);
	}
	pDC->SelectObject(pOldBrush);

	// create and select a thick, black pen
	CPen penBlack;
	penBlack.CreatePen(PS_DOT, 1, RGB(255, 0, 0));
	CPen* pOldPen = pDC->SelectObject(&penBlack);

	// draw a thick black rectangle filled with blue
	p0.x = minp.x;
	p0.y = minp.y;
	p1.x = maxp.x;
	p1.y = minp.y;

	pDC->MoveTo(p0);
	pDC->LineTo(p1);

	p0.x = minp.x;
	p0.y = minp.y;
	p1.x = minp.x;
	p1.y = maxp.y;

	pDC->MoveTo(p0);
	pDC->LineTo(p1);

	p0.x = maxp.x;
	p0.y = minp.y;
	p1.x = maxp.x;
	p1.y = maxp.y;

	pDC->MoveTo(p0);
	pDC->LineTo(p1);

	p0.x = minp.x;
	p0.y = maxp.y;
	p1.x = maxp.x;
	p1.y = maxp.y;

	pDC->MoveTo(p0);
	pDC->LineTo(p1);

	pDC->SelectObject(pOldPen);

}

bool CBezier::Intersect(CPOINT2F p){
	CPOINT2F p0, p1;

	p0.x = 9999999;
	p0.y = 9999999;
	p1.x = -9999999;
	p1.y = -9999999;

	for(unsigned int i = 0;i< arr[0].size();++i){
		p0.x = min(p0.x, arr[0][i].x);
		p0.y = min(p0.y, arr[0][i].y);
		p1.x = max(p1.x, arr[0][i].x);
		p1.y = max(p1.y, arr[0][i].y);
	}

	if((p0.x <= p.x && p.x <= p1.x) && 
		(p0.y <= p.y && p.y <= p1.y))
		return true;
	else 
		return false;
}

void CBezier::Translate(CPOINT2F p){

	for(unsigned int i = 0;i< arr[0].size();++i){
		arr[0][i].x += p.x;
		arr[0][i].y += p.y;
	}
}

void CBezier::ChangeFillColor(COLORREF c){
	m_bgcolor = c;
}

void CBezier::ChangeLineColor(COLORREF c){
	m_linecolor = c;
}

void CBezier::ChangeFilled(){
	m_filled = !m_filled;
}