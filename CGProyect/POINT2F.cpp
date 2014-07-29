#include "stdafx.h"
#include "POINT2F.h"


// Sobrecarga del operador + para la clase Pareja
CPOINT2F operator +(const CPOINT2F &p1,const CPOINT2F &p2)
{
  return CPOINT2F(p1.x + p2.x, p1.y + p2.y);
}

CPOINT2F operator -(const CPOINT2F &p1,const CPOINT2F &p2)
{
  return CPOINT2F(p1.x - p2.x, p1.y - p2.y);
}

CPOINT2F operator *(const CPOINT2F &p1,const float &c)
{
  return CPOINT2F(p1.x * c, p1.y * c);
}

std::ostream& operator <<(std::ostream &o,const CPOINT2F &p)
{
	o<<p.x<<" "<<p.y;
	return o;
}