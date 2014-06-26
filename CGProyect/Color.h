#ifndef MYCOLOR_H
#define MYCOLOR_H

#include <math.h>
#include <iostream>

class CColor
{
public:
	float r,g,b;
	CColor(float, float, float);
	CColor();
	CColor(COLORREF);
	COLORREF ToCOLORREF();
	void setColor(float,float,float);
	void setColor(COLORREF);
	friend CColor operator +(const CColor &,const CColor &);
	friend CColor operator -(const CColor &,const CColor &);
	friend CColor operator *(const CColor &,const float &);
	friend std::ostream& operator <<(std::ostream &,const CColor &);
};

#endif
