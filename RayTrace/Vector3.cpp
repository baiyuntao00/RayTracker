#include "stdafx.h"
#include "Vector3.h"
#include "math.h"

CVector3::CVector3()//z轴正向
{
	x = 0.0;
	y = 0.0;
	z = 1.0;
}

CVector3::~CVector3()
{

}
CVector3::CVector3(float x,float y ,float z)//z轴正向
{
	this->x = x;
	this->y = y;
	this->z = z;
}
CVector3::CVector3(float x, float y, float z,int c)//
{
	this->x = x/255;
	this->y = y/255;
	this->z = z/255;
}
CVector3::CVector3(  CVector3 &p0,   CVector3 &p1)
{
	x = p1.x - p0.x;
	y = p1.y - p0.y;
	z = p1.z - p0.z;
}
float CVector3::Mag()//矢量的模
{
	return sqrt(x*x + y*y + z*z);
}

CVector3 CVector3::Normalize()//归一化到单位矢量
{
	CVector3 vector;
	float Mag = sqrt(x*x + y*y + z*z);
	if (fabs(Mag)<1e-6)
		Mag = 1.0;
	vector.x = x / Mag;
	vector.y = y / Mag;
	vector.z = z / Mag;
	return vector;
}

CVector3 operator +(  CVector3 &v0,   CVector3 &v1)//矢量的和
{
	CVector3 vector;
	vector.x = v0.x + v1.x;
	vector.y = v0.y + v1.y;
	vector.z = v0.z + v1.z;
	return vector;
}

CVector3 operator -(  CVector3 &v0,   CVector3 &v1)//矢量的差
{
	CVector3 vector;
	vector.x = v0.x - v1.x;
	vector.y = v0.y - v1.y;
	vector.z = v0.z - v1.z;
	return vector;
}

CVector3 operator *(  CVector3 &v, float k)//矢量与常量的积
{
	CVector3 vector;
	vector.x = v.x*k;
	vector.y = v.y*k;
	vector.z = v.z*k;
	return vector;
}

CVector3 operator *(float k,   CVector3 &v)//常量与矢量的积
{
	CVector3 vector;
	vector.x = v.x*k;
	vector.y = v.y*k;
	vector.z = v.z*k;
	return vector;
}

CVector3 operator /(  CVector3 &v, float k)//矢量数除
{
	if (fabs(k)<1e-6)
		k = 1.0;
	CVector3 vector;
	vector.x = v.x / k;
	vector.y = v.y / k;
	vector.z = v.z / k;
	return vector;
}

CVector3 operator +=(CVector3 &v0, CVector3 &v1)//+=运算符重载
{
	v0.x = v0.x + v1.x;
	v0.y = v0.y + v1.y;
	v0.z = v0.z + v1.z;
	return v1;
}

CVector3 operator -=(CVector3 &v0, CVector3 &v1)//-=运算符重载
{
	v0.x = v0.x - v1.x;
	v0.y = v0.y - v1.y;
	v0.z = v0.z - v1.z;
	return v0;
}

CVector3 operator *=(CVector3 &v0, CVector3 &v1)//*=运算符重载
{
	v0.x = v0.x*v1.x;
	v0.y = v0.y*v1.y;
	v0.z = v0.z*v1.z;
	return v0;
}

CVector3 operator /=(CVector3 &v, float k)///=运算符重载
{
	v.x = v.x / k;
	v.y = v.y / k;
	v.z = v.z / k;
	return v;
}

float Dot(  CVector3 &v0,   CVector3 &v1)//矢量的点积
{
	return(v0.x*v1.x + v0.y*v1.y + v0.z*v1.z); 
}

CVector3 Cross(  CVector3 &v0,   CVector3 &v1)//矢量的叉积
{
	CVector3 vector;
	vector.x = v0.y*v1.z - v0.z*v1.y;
	vector.y = v0.z*v1.x - v0.x*v1.z;
	vector.z = v0.x*v1.y - v0.y*v1.x;
	return vector;
}
CVector3 Reflect(  CVector3& v,   CVector3& n)
{
	CVector3 vp;
	return (v - 2 * Dot(v, n)*n);
}
CVector3 RandomVec(CVector3 & p1,float du)
{
	CVector3 p;
	do {
		p = 2.0*CVector3((rand() % (100) / (float)(100)),
			(rand() % (100) / (float)(100)),
			(rand() % (100) / (float)(100)))
			- CVector3(1, 1, 1);
	} while (p.Mag() >= 1.0);
	return p1 + du*p;
}


