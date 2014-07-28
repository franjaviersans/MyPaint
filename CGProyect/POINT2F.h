#ifndef POINT2f_H
#define POINT2f_H

#include <iostream>

class CPOINT2F
{
public:
	float x;
	float y;
	CPOINT2F(): x(0), y(0){};
	CPOINT2F(POINT p): x((float)p.x), y((float)p.y){};
	CPOINT2F(int xx, int yy): x((float)xx), y((float)yy){};
	CPOINT2F(float xx, float yy): x(xx), y(yy){};
};

#endif