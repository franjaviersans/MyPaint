#include "stdafx.h"
#include "Color.h"


CColor::CColor()
{
	r = 0;
	g = 0;
	b = 0;
}



CColor::CColor(float nr, float ng, float nb)
{
	r = nr;
	g = ng;
	b = nb;
}

CColor::CColor(COLORREF cf)
{
	r = GetRValue(cf);
	g = GetGValue(cf);
	b = GetBValue(cf);
}


void CColor::setColor(float nr, float ng, float nb)
{
	r = nr;
	g = ng;
	b = nb;
}

void CColor::setColor(COLORREF cf)
{
	r = GetRValue(cf);
	g = GetGValue(cf);
	b = GetBValue(cf);
}


COLORREF CColor::ToCOLORREF()
{
	return RGB(r,g,b);
}

void CColor::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		ar << r;
		ar << g;
		ar << b;
	}
	else
	{
		ar >> r;
		ar >> g;
		ar >> b;
	}
}

// Sobrecarga del operador + para la clase Pareja
CColor operator +(const CColor &p1,const CColor &p2)
{
  return CColor(p1.r + p2.r, p1.g + p2.g, p1.b + p2.b);
}

CColor operator -(const CColor &p1,const CColor &p2)
{
  return CColor(p1.r - p2.r, p1.g - p2.g, p1.b - p2.b);
}

CColor operator *(const CColor &p1,const float &c)
{
  return CColor(p1.r * c, p1.g * c, p1.b * c);
}

std::ostream& operator <<(std::ostream &o,const CColor &p)
{
	o<<p.r<<" "<<p.g<<" "<<p.b;
	return o;
}