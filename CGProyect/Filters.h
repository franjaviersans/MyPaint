#ifndef FILTER_H
#define FILTER_H

#include <math.h>
#include <iostream>

enum
{
	IM_MIN,
	IM_MAX,
	IM_BOX,
	IM_GAUSSIAN,
	IM_MEDIAN,
	IM_LAPLACE,
	IM_SHARPEN
};

class CFilters
{
public:
	float r,g,b;
	CFilters();
	void Min(float *, float *, int, int, int);
	void Max(float *, float *, int, int, int);
	void Gaussian(float *, float *, int, int, int);
	void Box(float *, float *, int, int, int);
	void Median(float *, float *, int, int, int);
	void Laplace(float *, float *, int, int);
	void Sharpen(float *, float *, int, int);

};

#endif
