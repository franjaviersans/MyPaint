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

void CBezier::OnDraw(CBackBuffer *pDC, POINT WindowsSize)
{
	POINT last;

	//Algoritmo de Casteljau
	double t;
	unsigned int r,j;
	unsigned int n=arr[0].size();
	bool first = true;


	for(t=0;t<=5;t+=0.01){

		if(t >= 1) t = 1;
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

			CLine::DrawLine(p0, last, pDC, m_linecolor, 1);
		}

		if(t == 1) break;
	}
}

void CBezier::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << m_id;
		ar << m_bgcolor;
		ar << m_linecolor;
		ar << m_filled;
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
		ar >> m_bgcolor;
		ar >> m_linecolor;
		ar >> m_filled;
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

void CBezier::addControlpoint(){
	unsigned int i;
	unsigned int n = arr[0].size();

	CPOINT2F a;
	a.x = 100;
	a.y = 100;

	n = arr[0].size();
	arr[0].push_back(a);

	for(i = n; i > 0 ; --i){
		arr[0][i].x = arr[0][i - 1].x * ((float)i / n) + arr[0][i].x * (1.0f - ((float)i / n));
		arr[0][i].y = arr[0][i - 1].y * ((float)i / n) + arr[0][i].y * (1.0f - ((float)i / n));
	}

	n = arr[0].size();

	while(n > arr.size())
		arr.push_back(*(new std::vector<CPOINT2F>));

	for(i=1; i<n ;++i)
		while(arr[i].size() <= n-i){
			CPOINT2F a;
			a.x = 0;
			a.y = 0;
			arr[i].push_back(a);
		}
}

void CBezier::DrawSelected(CBackBuffer *pDC, POINT WindowsSize){

	POINT p0, p1, minp, maxp;

	minp.x = 99999;
	minp.y = 99999;

	maxp.x = -1000;
	maxp.y = -1000;

	CColor green(0, 255, 0);

	for(unsigned int i = 0;i< arr[0].size();++i){
		p0.x = (int)(arr[0][i].x * WindowsSize.x);
		p0.y = (int)(arr[0][i].y * WindowsSize.y);

		minp.x = min(p0.x, minp.x);
		minp.y = min(p0.y, minp.y);
		maxp.x = max(p0.x, maxp.x);
		maxp.y = max(p0.y, maxp.y);
		
		pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,green.ToCOLORREF());
	}

	int draw;

	CColor red(255,0,0);

	p0.x = minp.x;
	p0.y = minp.y;
	p1.x = maxp.x;
	p1.y = minp.y;
	
	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 && min(p0.x, p1.x) >= WindowsSize.x && max(p0.y, p1.y) < 0 && min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);

	p0.x = minp.x;
	p0.y = minp.y;
	p1.x = minp.x;
	p1.y = maxp.y;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 && min(p0.x, p1.x) >= WindowsSize.x && max(p0.y, p1.y) < 0 && min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);

	p0.x = maxp.x;
	p0.y = minp.y;
	p1.x = maxp.x;
	p1.y = maxp.y;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 && min(p0.x, p1.x) >= WindowsSize.x && max(p0.y, p1.y) < 0 && min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);

	p0.x = minp.x;
	p0.y = maxp.y;
	p1.x = maxp.x;
	p1.y = maxp.y;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 && min(p0.x, p1.x) >= WindowsSize.x && max(p0.y, p1.y) < 0 && min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);


	CColor other(255, 100, 0);

	for(unsigned int i = 0;i< arr[0].size();++i){
		p0.x = (int)(arr[0][i].x * WindowsSize.x);
		p0.y = (int)(arr[0][i].y * WindowsSize.y);
		
		pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,other.ToCOLORREF());
	}
}

bool CBezier::Intersect(CPOINT2F p, POINT WindowsSize){
	double epsilon = (WindowsSize.x > WindowsSize.y)? 2.0/WindowsSize.x : 2.0/WindowsSize.y;
	//TODO: Interseccion super compleja
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

CPOINT2F* CBezier::IntersectControlPoint(CPOINT2F p, POINT WindowsSize){
	double epsilon = (WindowsSize.x > WindowsSize.y)? 4.0/WindowsSize.x : 4.0/WindowsSize.y;

	for(unsigned int i = 0;i< arr[0].size();++i){
		if(abs((p.x - arr[0][i].x)) <= epsilon && abs((p.y - arr[0][i].y)) <= epsilon)
			return &arr[0][i];
	}

	return NULL;
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