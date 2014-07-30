#ifndef MYMATRIX3_H
#define MYMATRIX3_H

#define PI 3.14159265

#include <math.h>
#include <iostream>
#include "POINT2F.h"

class CMatrix3
{
public:
	float mat[3][3];
	CMatrix3(float, float, float, float , float, float, float, float, float);
	CMatrix3(float *);
	CMatrix3();
	void PreMult(const CMatrix3 &);
	void PostMult(const CMatrix3 &);
	
	friend CMatrix3 Invert(const CMatrix3 &);
	friend CMatrix3 Transpose(const CMatrix3 &);
	friend CMatrix3 Zeros();
	friend CMatrix3 Eyes();
	friend CMatrix3 Translate2D(float,float);
	friend CMatrix3 Rotate2D(float);
	friend CMatrix3 Scale2D(float,float);
	friend CMatrix3 operator +(const CMatrix3 &,const CMatrix3 &);
	friend CMatrix3 operator -(const CMatrix3 &,const CMatrix3 &);
	friend CMatrix3 operator *(const CMatrix3 &,const CMatrix3 &);
	friend CMatrix3 operator *(const CMatrix3 &,const float &);
	friend CPOINT2F operator *(const CMatrix3 &,const CPOINT2F &);
	friend POINT operator *(const CMatrix3 &,const POINT &);
	friend bool operator ==(const CMatrix3 &,const CMatrix3 &);
	friend std::ostream& operator <<(std::ostream &,const CMatrix3 &);
};

#endif
