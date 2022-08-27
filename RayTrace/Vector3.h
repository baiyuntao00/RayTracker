#pragma once

class CVector3
{
public:
	CVector3();
	virtual ~CVector3();
	CVector3(float x, float y, float z);
	CVector3(float x, float y, float z,int c);
	float Mag();//ʸ����ģ
	CVector3(CVector3 &p0,   CVector3 &p1);
	CVector3 Normalize();//��λʸ��
	friend CVector3 operator +(CVector3 &,   CVector3 &);//���������
	friend CVector3 operator -(CVector3 &,   CVector3 &);
	friend CVector3 operator *(CVector3 &, float);
	friend CVector3 operator *(float, CVector3 &);
	friend CVector3 operator /(CVector3 &, float);
	friend CVector3 operator+=(CVector3 &, CVector3 &);
	friend CVector3 operator-=(CVector3 &, CVector3 &);
	friend CVector3 operator*=(CVector3 &, CVector3 &);
	friend CVector3 operator/=(CVector3 &, float);
	friend float Dot(CVector3 &,CVector3 &);  //ʸ�����
	friend CVector3 Cross(CVector3 &,CVector3 &);//ʸ�����
	friend CVector3 RandomVec(CVector3 &,float);//ʸ�����
	friend CVector3 Reflect(CVector3&,   CVector3&);///��������
public:
	float x,y,z;//�������ݳ�Ա�������ⲿ����
};
