#include "stdafx.h"
#include "Bezier.h"
#include "Line.h"
#include <iostream>
#include <fstream>

CBezier::CBezier()
{
	std::vector< CPOINT2F > va;
	arr.push_back(va);
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

CBezier::CBezier(std::vector< CPOINT2F > &copy){
	std::vector< CPOINT2F > va;
	arr.push_back(va);
	addPoint(0,0);
	addPoint(0,0);

	//Allocate the space
	arr[0].resize(copy.size());


	unsigned int n = copy.size();
	unsigned int i;

	//Copy the data
	for(i=0;i<n;++i)
		arr[0][i] = copy[i];

	//Create Matrix
	while(n > arr.size()){
		arr.push_back(va);
	}

	for(i=1; i<n ;++i)
		while(arr[i].size() <= n-i){
			CPOINT2F a(0,0);
			arr[i].push_back(a);
		}

	m_id = IM_BEZIER;
	m_bgcolor = 0;
	m_linecolor = 0;
	m_filled = false;
}

CBezier::~CBezier(){
	unsigned int n=arr[0].size();
	unsigned int r;
	for(r=0;r<n;++r){
		arr[r].clear();
	}
	arr.clear();
}

void CBezier::OnDraw(CBackBuffer *pDC, POINT WindowsSize)
{
	POINT last;

	//Algoritmo de Casteljau
	double t;
	unsigned int r,j;
	unsigned int n=arr[0].size();
	bool first = true;


	for(t=0;t<=1.1;t+=0.01){

		if(t >= 1) t = 1;
		for(r=1;r<n;++r){
			for(j=0;j<n-r;++j){
				arr[r][j].x = ((float) (1 - t) * arr[r-1][j].x + (float)t * arr[r-1][j+1].x);
				arr[r][j].y = ((float) (1 - t) * arr[r-1][j].y + (float)t * arr[r-1][j+1].y);
			}
		}

		if(n-1>0){
			POINT p0;
			if(first){
				last.x = (int)(arr[n-1][0].x  + 0.5);
				last.y = (int)(arr[n-1][0].y + 0.5);
				first = false;
			}
			p0.x = last.x;
			p0.y = last.y;
			last.x = (int)(arr[n-1][0].x + 0.5);
			last.y = (int)(arr[n-1][0].y + 0.5);

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
		int n,x,y;
		ar >> m_bgcolor;
		ar >> m_linecolor;
		ar >> m_filled;
		ar >> n;
		arr.clear();
		std::vector<CPOINT2F> va;
		arr.push_back(va);
		for(int i = 0; i < n;++i){
			ar >> x;
			ar >> y;
			addPoint(x,y);
		}
	}
}

void CBezier::addPoint(int x, int y){
	CPOINT2F a(x,y);

	arr[0].push_back(a);

	unsigned int n = arr[0].size();
	unsigned int i;

	std::vector<CPOINT2F> va;
	while(n > arr.size()){
		arr.push_back(va);
	}

	for(i=1; i<n ;++i)
		while(arr[i].size() <= n-i){
			CPOINT2F a(0,0);
			arr[i].push_back(a);
		}
}

void CBezier::addControlpoint(){
	unsigned int i;
	unsigned int n = arr[0].size();

	CPOINT2F a(100,100);
	
	n = arr[0].size();
	arr[0].push_back(a);

	for(i = n; i > 0 ; --i){
		arr[0][i].x = (arr[0][i - 1].x * ((float)i / n) + arr[0][i].x * (1.0f - ((float)i / n)));
		arr[0][i].y = (arr[0][i - 1].y * ((float)i / n) + arr[0][i].y * (1.0f - ((float)i / n)));
	}

	n = arr[0].size();
	std::vector<CPOINT2F> va;

	while(n > arr.size())
		arr.push_back(va);

	for(i=1; i<n ;++i)
		while(arr[i].size() <= n-i){
			CPOINT2F a(0,0);
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
		p0.x = (int)arr[0][i].x;
		p0.y = (int)arr[0][i].y;

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
	if(max(p0.x, p1.x) < 0 || min(p0.x, p1.x) >= WindowsSize.x || max(p0.y, p1.y) < 0 || min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);

	p0.x = minp.x;
	p0.y = minp.y;
	p1.x = minp.x;
	p1.y = maxp.y;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 || min(p0.x, p1.x) >= WindowsSize.x || max(p0.y, p1.y) < 0 || min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);

	p0.x = maxp.x;
	p0.y = minp.y;
	p1.x = maxp.x;
	p1.y = maxp.y;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 || min(p0.x, p1.x) >= WindowsSize.x || max(p0.y, p1.y) < 0 || min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);

	p0.x = minp.x;
	p0.y = maxp.y;
	p1.x = maxp.x;
	p1.y = maxp.y;

	//Check if the figure is inside the drawing area
	if(max(p0.x, p1.x) < 0 || min(p0.x, p1.x) >= WindowsSize.x || max(p0.y, p1.y) < 0 || min(p0.y, p1.y) >= WindowsSize.y) draw = 0;
	else if(p0.x >= 0 && p0.x < WindowsSize.x && p0.y >= 0 && p0.y < WindowsSize.y && p1.x >= 0 && p1.x < WindowsSize.x && p1.y >= 0 && p1.y < WindowsSize.y) draw = 2;
	else draw = 1;
	CLine::DrawDottedLine(p0, p1, pDC, red.ToCOLORREF(), draw);


	CColor other(255, 100, 0);

	for(unsigned int i = 0;i< arr[0].size();++i){
		p0.x = (int)arr[0][i].x;
		p0.y = (int)arr[0][i].y;
		
		pDC->Rectangle(p0.x - 5, p0.y - 5, p0.x + 5, p0.y + 5,other.ToCOLORREF());
	}
}

bool CBezier::Intersect(POINT p){
	/*double epsilon = 4;
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
		return false;*/

	float ep = 4;

	return IntersectBezier(&arr[0],&p,ep);

}

bool CBezier::IntersectBezier(std::vector< CPOINT2F > *controlPoints, POINT *p, float epsilon){
	
   	if(controlPoints->size() == 0) return false;

	std::vector<CPOINT2F> *f = new std::vector<CPOINT2F>(),*s = new std::vector<CPOINT2F>();

	//Obtain the two halves
	Divide(controlPoints,f,s,0.5);

	//Check with the first half
	CPOINT2F p0(9999999, 9999999), p1(-9999999,-9999999);

	bool result = false;
	
	for(unsigned int i = 0;i< f->size();++i){
		p0.x = min(p0.x, (*f)[i].x);
		p0.y = min(p0.y, (*f)[i].y);
		p1.x = max(p1.x, (*f)[i].x);
		p1.y = max(p1.y, (*f)[i].y);
	}
	
	if(p0.x - epsilon <= p->x && p->x <= p1.x + epsilon && p0.y - epsilon <= p->y && p->y <= p1.y + epsilon){
		if(p1.x - p0.x <= epsilon && p1.y - p0.y <= epsilon) result = true;
		if(!result && IntersectBezier(f, p, epsilon)) result = true;
	}

	if(!result){
		//Check with the first half
		p0.x = 9999999;
		p0.y = 9999999;
		p1.x = -9999999;
		p1.y = -9999999;

		for(unsigned int i = 0;i< s->size();++i){
			p0.x = min(p0.x, (*s)[i].x);
			p0.y = min(p0.y, (*s)[i].y);
			p1.x = max(p1.x, (*s)[i].x);
			p1.y = max(p1.y, (*s)[i].y);
		}

		//Check with the second half
		if(p0.x - epsilon <= p->x && p->x <= p1.x + epsilon && p0.y - epsilon <= p->y && p->y <= p1.y + epsilon){
			if(p1.x - p0.x <= epsilon && p1.y - p0.y <= epsilon) result = true;
			if(IntersectBezier(s, p, epsilon)) result =  true;
		}	
	}

	f->clear();
	s->clear();

	delete s;
	delete f;

	return result;
}

CPOINT2F* CBezier::IntersectControlPoint(POINT p){
	double epsilon = 4;

	for(unsigned int i = 0;i< arr[0].size();++i){
		if(abs((p.x - arr[0][i].x)) <= epsilon && abs((p.y - arr[0][i].y)) <= epsilon)
			return &arr[0][i];
	}

	return NULL;
}

void CBezier::Translate(POINT p){

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


/**
* Function to subdivide a bezier curve
*
*/
void CBezier::Divide(std::vector< CPOINT2F > &firsthalf, std::vector< CPOINT2F > &secondhalf, float t){

	int n = arr[0].size(), r, j;

	//Form the poligon
	for(r=1;r<n;++r){
		for(j=0;j<n-r;++j){
			arr[r][j].x = ((float) (1 - t) * arr[r-1][j].x + (float) t * arr[r-1][j+1].x);
			arr[r][j].y = ((float) (1 - t) * arr[r-1][j].y + (float) t * arr[r-1][j+1].y);
		}
	}

	//Form first half
	for(r=0;r<n;++r) firsthalf.push_back(arr[r][0]);
		
	for(r=n-1;r>=0;--r) secondhalf.push_back(arr[r][n-1-r]);

}


/**
* Function to subdivide a bezier curve from a given vector of points
*
*/
void CBezier::Divide(std::vector< CPOINT2F > *arr, std::vector< CPOINT2F > *firsthalf, std::vector< CPOINT2F > *secondhalf, float t){

	//Create an array to store all the control points
	std::vector< std::vector< CPOINT2F > > auxiliar;
	std::vector< CPOINT2F > half, va;

	int n = (int)arr->size(), j;
	int r;

	auxiliar.push_back(va);

	for(unsigned int k=0;k<arr->size();++k)
		auxiliar[0].push_back((*arr)[k]);

	//Create the array
	while(n > (int)auxiliar.size())
		auxiliar.push_back(va);

	for(r=1; r<n ;++r)
		while((int)auxiliar[r].size() <= n-r){
			CPOINT2F a(0,0);
			auxiliar[r].push_back(a);
		}

	//Form the poligon
	for(r=1;r<n;++r){
		for(j=0;j<n-r;++j){
			auxiliar[r][j].x = ((float) (1 - t) * auxiliar[r-1][j].x + (float) t * auxiliar[r-1][j+1].x);
			auxiliar[r][j].y = ((float) (1 - t) * auxiliar[r-1][j].y + (float) t * auxiliar[r-1][j+1].y);
		}
	}

	//Form first half
	for(r=0;r<n;++r) firsthalf->push_back(auxiliar[r][0]);
		
	for(r=n-1;r>=0;--r) secondhalf->push_back(auxiliar[r][n-1-r]);

	//Clear memory
	for(r=0; r<n ;++r)
		auxiliar[r].clear();

	auxiliar.clear();

}