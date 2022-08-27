#include "stdafx.h"
#include "Transform.h"
#include "math.h"
#define PI 3.1415926
#define RADIAN(a) a*PI/180.0

Transform::Transform()
{
}


Transform::~Transform()
{
}
CVector3 ZoomTran(CVector3 oldp, float zoom)
{
	return oldp / zoom;
}
CVector3 MoveTran(CVector3 oldp, float x,float y,float z)
{
	CVector3 newp = oldp;
	newp.x = oldp.x + x;
	newp.y = oldp.y + y;
	newp.z = oldp.z + z;
	return newp;
}
CVector3 Transform::RotateTran(char a, CVector3 oldp, float angle)
{
	CVector3 newp = oldp;
	CVector3 temp;
	float alfa = RADIAN(angle);
	/////围绕模型中心x旋转
	if (a == 'x')
	{
		CVector3 axle(newp.x, (maxp.y - minp.y) / 2, (maxp.z - minp.z) / 2);
		temp = oldp - axle;
		Matrix m2(4, 4);
		m2.mat[0][0] = 1, m2.mat[0][1] = 0, m2.mat[0][2] = 0, m2.mat[0][3] = 0;
		m2.mat[1][0] = 0, m2.mat[1][1] = cos(alfa),  m2.mat[1][2] = sin(alfa), m2.mat[1][3] = 0;
		m2.mat[2][0] = 0, m2.mat[2][1] = -sin(alfa), m2.mat[2][2] = cos(alfa), m2.mat[2][3] = 0;
		m2.mat[3][0] = 0, m2.mat[3][1] = 0, m2.mat[3][2] = 0, m2.mat[3][3] = 1;
		Matrix m1(1, 4);
		m1.mat[0][0] = temp.x, m1.mat[0][1] = temp.y, m1.mat[0][2] = temp.z, m1.mat[0][3] = 1;
		Matrix newm = m1*m2;
		newp.x = newm.mat[0][0], newp.y = newm.mat[0][1], newp.z = newm.mat[0][2];
		newp = newp + axle;
		return newp;
	}
	if (a == 'y')
	{
		CVector3 axle((maxp.x - minp.x) / 2, newp.y, (maxp.z - minp.z) / 2);
		temp = oldp - axle;
		Matrix m2(4, 4);
		m2.mat[0][0] = cos(alfa), m2.mat[0][1] = 0, m2.mat[0][2] = -sin(alfa), m2.mat[0][3] = 0;
		m2.mat[1][0] = 0, m2.mat[1][1] = 1, m2.mat[1][2] = 0, m2.mat[1][3] = 0;
		m2.mat[2][0] = sin(alfa), m2.mat[2][1] =0, m2.mat[2][2] = cos(alfa), m2.mat[2][3] = 0;
		m2.mat[3][0] = 0, m2.mat[3][1] = 0, m2.mat[3][2] = 0, m2.mat[3][3] = 1;
		Matrix m1(1, 4);
		m1.mat[0][0] = temp.x, m1.mat[0][1] = temp.y, m1.mat[0][2] = temp.z, m1.mat[0][3] = 1;
		Matrix newm = m1*m2;
		newp.x = newm.mat[0][0], newp.y = newm.mat[0][1], newp.z = newm.mat[0][2];
		newp = newp + axle;
		return newp;
	}
	if (a == 'z')
	{
		CVector3 axle((maxp.x - minp.x) / 2, (maxp.y - minp.y) / 2, newp.z);
		temp = oldp - axle;
		Matrix m2(4, 4);
		m2.mat[0][0] = cos(alfa), m2.mat[0][1] = sin(alfa), m2.mat[0][2] = 0, m2.mat[0][3] = 0;
		m2.mat[1][0] = -sin(alfa), m2.mat[1][1] = cos(alfa), m2.mat[1][2] = 0, m2.mat[1][3] = 0;
		m2.mat[2][0] = 0, m2.mat[2][1] = 0, m2.mat[2][2] = 1, m2.mat[2][3] = 0;
		m2.mat[3][0] = 0, m2.mat[3][1] = 0, m2.mat[3][2] = 0, m2.mat[3][3] = 1;
		Matrix m1(1, 4);
		m1.mat[0][0] = temp.x, m1.mat[0][1] = temp.y, m1.mat[0][2] = temp.z, m1.mat[0][3] = 1;
		Matrix newm = m1*m2;
		newp.x = newm.mat[0][0], newp.y = newm.mat[0][1], newp.z = newm.mat[0][2];
		newp = newp + axle;
		return newp;
	}
}