#pragma once

class CVector3
{
public:
	CVector3();
	virtual ~CVector3();
	CVector3(float x, float y, float z);
	CVector3(float x, float y, float z,int c);
	float Mag();//矢量的模
	CVector3(CVector3 &p0,   CVector3 &p1);
	CVector3 Normalize();//单位矢量
	friend CVector3 operator +(CVector3 &,   CVector3 &);//运算符重载
	friend CVector3 operator -(CVector3 &,   CVector3 &);
	friend CVector3 operator *(CVector3 &, float);
	friend CVector3 operator *(float, CVector3 &);
	friend CVector3 operator /(CVector3 &, float);
	friend CVector3 operator+=(CVector3 &, CVector3 &);
	friend CVector3 operator-=(CVector3 &, CVector3 &);
	friend CVector3 operator*=(CVector3 &, CVector3 &);
	friend CVector3 operator/=(CVector3 &, float);
	friend float Dot(CVector3 &,CVector3 &);  //矢量点积
	friend CVector3 Cross(CVector3 &,CVector3 &);//矢量叉积
	friend CVector3 RandomVec(CVector3 &,float);//矢量叉积
	friend CVector3 Reflect(CVector3&,   CVector3&);///反射向量
public:
	float x,y,z;//公有数据成员，方便外部访问
};
