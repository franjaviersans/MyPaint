#include "stdafx.h"
#include "Matrix3.h"



CMatrix3::CMatrix3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22){
	mat[0][0] = m00;
	mat[0][1] = m01;
	mat[0][2] = m02;
	mat[1][0] = m10;
	mat[1][1] = m11;
	mat[1][2] = m12;
	mat[2][0] = m20;
	mat[2][1] = m21;
	mat[2][2] = m22;
}

CMatrix3::CMatrix3(float *arr){
	memcpy(mat, arr, sizeof(float)*3*3);
}
	
CMatrix3::CMatrix3(){
	mat[0][0] = mat[0][1] = mat[0][2] = mat[1][0] = mat[1][1] = mat[1][2] = mat[2][0] = mat[2][1] = mat[2][2] = 0.f;
}


void CMatrix3::PreMult(const CMatrix3 &b){
	*this = b * *this; 
}

void CMatrix3::PostMult(const CMatrix3 &b){
	*this = *this * b;
}

void CMatrix3::Serialize(CArchive& ar){

	
	if (ar.IsStoring())
	{

		ar << mat[0][0];
		ar << mat[0][1];
		ar << mat[0][2];
		ar << mat[1][0];
		ar << mat[1][1];
		ar << mat[1][2];
		ar << mat[2][0];
		ar << mat[2][1];
		ar << mat[2][2];
	}
	else
	{
		ar >> mat[0][0];
		ar >> mat[0][1];
		ar >> mat[0][2];
		ar >> mat[1][0];
		ar >> mat[1][1];
		ar >> mat[1][2];
		ar >> mat[2][0];
		ar >> mat[2][1];
		ar >> mat[2][2];
	}
}

CMatrix3 Invert(const CMatrix3 &b){
	float d1 = (b.mat[1][1] * b.mat[2][2]  - b.mat[1][2] * b.mat[2][1]),d2 = (b.mat[1][0] * b.mat[2][2]  - b.mat[1][2] * b.mat[2][0]), d3 = (b.mat[1][0] * b.mat[2][1]  - b.mat[1][1] * b.mat[2][0]);
	float d =	b.mat[0][0] * d1 - b.mat[0][1] * d2 + b.mat[0][2] * d3;
	return CMatrix3(	d1/d,	-((b.mat[0][1] * b.mat[2][2]) - (b.mat[0][2] * b.mat[2][1]))/d,		((b.mat[0][1] * b.mat[1][2]) - (b.mat[0][2] * b.mat[1][1]))/d,
					-d2/d,	((b.mat[0][0] * b.mat[2][2]) - (b.mat[0][2] * b.mat[2][0]))/d,		-((b.mat[0][0] * b.mat[1][2]) - (b.mat[0][2] * b.mat[1][0]))/d,
					d3/d,	-((b.mat[0][0] * b.mat[2][1]) - (b.mat[0][1] * b.mat[2][0]))/d,		((b.mat[0][0] * b.mat[1][1]) - (b.mat[0][1] * b.mat[1][0]))/d);



}

CMatrix3 Transpose(const CMatrix3 &b){
	return CMatrix3(	b.mat[0][0], b.mat[1][0], b.mat[2][0],
					b.mat[0][1], b.mat[1][1], b.mat[2][1],
					b.mat[0][2], b.mat[1][2], b.mat[2][2]);
}

CMatrix3 Zeros(){
	return CMatrix3(	0, 0, 0,
						0, 0, 0,
						0, 0, 0);
}

CMatrix3 Eyes(){
	return CMatrix3(	1, 0, 0,
						0, 1, 0,
						0, 0, 1);
}

CMatrix3 Translate2D(float dx,float dy){
	CMatrix3 traslate = Eyes();
	traslate.mat[0][2] = dx; 
	traslate.mat[1][2] = dy;

	return traslate;
}

CMatrix3 Rotate2D(float ang){
	CMatrix3 rot = Eyes();
	rot.mat[0][0] = cos(ang); 
	rot.mat[0][1] = -sin(ang);
	rot.mat[1][0] = sin(ang); 
	rot.mat[1][1] = cos(ang);

	return rot;
}

CMatrix3 Scale2D(float sx,float sy){
	CMatrix3 s = Eyes();
	s.mat[0][0] = sx; 
	s.mat[1][1] = sy;

	return s;
}

CMatrix3 operator +(const CMatrix3 &a,const CMatrix3 &b){
	return CMatrix3( a.mat[0][0] + b.mat[0][0], a.mat[0][1] + b.mat[0][1], a.mat[0][2] + b.mat[0][2],
					a.mat[1][0] + b.mat[1][0], a.mat[1][1] + b.mat[1][1], a.mat[1][2] + b.mat[1][2],
					a.mat[2][0] + b.mat[2][0], a.mat[2][1] + b.mat[2][1], a.mat[2][2] + b.mat[2][2]);
}
	
CMatrix3 operator -(const CMatrix3 &a,const CMatrix3 &b){
	return CMatrix3( a.mat[0][0] - b.mat[0][0], a.mat[0][1] - b.mat[0][1], a.mat[0][2] - b.mat[0][2],
					a.mat[1][0] - b.mat[1][0], a.mat[1][1] - b.mat[1][1], a.mat[1][2] - b.mat[1][2],
					a.mat[2][0] - b.mat[2][0], a.mat[2][1] - b.mat[2][1], a.mat[2][2] - b.mat[2][2]);
}

CMatrix3 operator *(const CMatrix3 &a,const CMatrix3 &b){
	return CMatrix3( a.mat[0][0] * b.mat[0][0] + a.mat[0][1] * b.mat[1][0] + a.mat[0][2] * b.mat[2][0], 
					a.mat[0][0] * b.mat[0][1] + a.mat[0][1] * b.mat[1][1] + a.mat[0][2] * b.mat[2][1], 
					a.mat[0][0] * b.mat[0][2] + a.mat[0][1] * b.mat[1][2] + a.mat[0][2] * b.mat[2][2],
					a.mat[1][0] * b.mat[0][0] + a.mat[1][1] * b.mat[1][0] + a.mat[1][2] * b.mat[2][0], 
					a.mat[1][0] * b.mat[0][1] + a.mat[1][1] * b.mat[1][1] + a.mat[1][2] * b.mat[2][1], 
					a.mat[1][0] * b.mat[0][2] + a.mat[1][1] * b.mat[1][2] + a.mat[1][2] * b.mat[2][2],
					a.mat[2][0] * b.mat[0][0] + a.mat[2][1] * b.mat[1][0] + a.mat[2][2] * b.mat[2][0], 
					a.mat[2][0] * b.mat[0][1] + a.mat[2][1] * b.mat[1][1] + a.mat[2][2] * b.mat[2][1], 
					a.mat[2][0] * b.mat[0][2] + a.mat[2][1] * b.mat[1][2] + a.mat[2][2] * b.mat[2][2]);
}

CMatrix3 operator *(const CMatrix3 &a,const float &b){
	return CMatrix3( a.mat[0][0] * b, a.mat[0][1] * b, a.mat[0][2] * b,
					a.mat[1][0] * b, a.mat[1][1] * b, a.mat[1][2] * b,
					a.mat[2][0] * b, a.mat[2][1] * b, a.mat[2][2] * b);
}

CPOINT2F operator *(const CMatrix3 &a,const CPOINT2F &p){
	return CPOINT2F(a.mat[0][0] * p.x + a.mat[0][1] * p.y + a.mat[0][2] * 1.0f,
					a.mat[1][0] * p.x + a.mat[1][1] * p.y + a.mat[1][2] * 1.0f);
}

bool operator ==(const CMatrix3 &a,const CMatrix3 &b){
	return	a.mat[0][0] == b.mat[0][0] && a.mat[1][0] == b.mat[1][0] && a.mat[2][0] == b.mat[2][0] &&
			a.mat[0][1] == b.mat[0][1] && a.mat[1][1] == b.mat[1][1] && a.mat[2][1] == b.mat[2][1] &&
			a.mat[0][2] == b.mat[0][2] && a.mat[1][2] == b.mat[1][2] && a.mat[2][2] == b.mat[2][2]; 
}

std::ostream& operator <<(std::ostream &o,const CMatrix3 &p)
{
	o<<p.mat[0][0]<<" "<<p.mat[0][1]<<" "<<p.mat[0][2]<<std::endl;
	o<<p.mat[1][0]<<" "<<p.mat[1][1]<<" "<<p.mat[1][2]<<std::endl;
	o<<p.mat[2][0]<<" "<<p.mat[2][1]<<" "<<p.mat[2][2]<<std::endl;
	return o;
}