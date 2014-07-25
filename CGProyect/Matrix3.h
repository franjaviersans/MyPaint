#ifndef MYMATRIX3_H
#define MYMATRIX3_H

#include <math.h>
#include <iostream>

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
	friend CMatrix3 operator +(const CMatrix3 &,const CMatrix3 &);
	friend CMatrix3 operator -(const CMatrix3 &,const CMatrix3 &);
	friend CMatrix3 operator *(const CMatrix3 &,const CMatrix3 &);
	friend CMatrix3 operator *(const CMatrix3 &,const float &);
	friend bool operator ==(const CMatrix3 &,const CMatrix3 &);
	friend std::ostream& operator <<(std::ostream &,const CMatrix3 &);
};

#endif