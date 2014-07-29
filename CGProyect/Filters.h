#ifndef FILTER_H
#define FILTER_H

#include <math.h>
#include <iostream>

enum
{
	IM_MIN = 0,
	IM_MAX = 1,
	IM_BOX = 2,
	IM_GAUSSIAN = 3,
	IM_MEDIAN = 4,
	IM_LAPLACE = 5,
	IM_SHARPEN = 6
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
