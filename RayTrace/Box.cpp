#include "stdafx.h"
#include "Box.h"
#include <iostream>
#include <algorithm> 
using namespace std;

float GetfloatMax(float a, float b, float c){ return max(a, b)>c ? max(a, b) : c; }
float GetfloatMin(float a, float b, float c){ return min(a, b)<c ? min(a, b) : c; }
Box::Box(CVector3 p0, CVector3 p1, CVector3 p2)
{
	vex_ru.x = GetfloatMax(p0.x, p1.x, p2.x);
	vex_ld.x = GetfloatMin(p0.x, p1.x, p2.x);
	vex_ru.y = GetfloatMax(p0.y, p1.y, p2.y);
	vex_ld.y = GetfloatMin(p0.y, p1.y, p2.y);
	vex_ru.z = GetfloatMax(p0.z, p1.z, p2.z);
	vex_ld.z = GetfloatMin(p0.z, p1.z, p2.z);
}

bool Box::IsHitBox(Ray r, float t_min, float t_max)
{
	if (vex_ru.x == vex_ld.x || vex_ru.y == vex_ld.y || vex_ru.z == vex_ld.z)
		return true;
	float t_near = (numeric_limits<float>::min)();
	float t_far = (numeric_limits<float>::max)();
	CVector3 r_origin = r.org;
	CVector3 r_direction = r.dir;
	float array_t[6];
	if (r_direction.x == 0) 
	{
		if (r_origin.x > vex_ru.x || r_origin.x < vex_ld.x) 
			return false;
	}
	if (r_direction.y == 0) 
	{
		if (r_origin.y > vex_ru.y || r_origin.y < vex_ld.y) 
			return false;
	}
	if (r_direction.z == 0)
	{
		if (r_origin.z > vex_ru.z || r_origin.z < vex_ld.z)
			return false;
	}
	if ((r_direction.x != 0) && (r_direction.y != 0) && (r_direction.z != 0)) 
	{
		array_t[0] = (vex_ru.x - r_origin.x) / r_direction.x;//小
		array_t[1] = (vex_ld.x - r_origin.x) / r_direction.x;//大
		array_t[2] = (vex_ru.y - r_origin.y) / r_direction.y;
		array_t[3] = (vex_ld.y - r_origin.y) / r_direction.y;
		array_t[4] = (vex_ru.z - r_origin.z) / r_direction.z;
		array_t[5] = (vex_ld.z - r_origin.z) / r_direction.z;
	}
	for (int i = 0; i<6; i = i + 2)
	{
		if (array_t[i] > array_t[i + 1])///保证前小后大
		{
			float t = array_t[i];
			array_t[i] = array_t[i + 1];
			array_t[i + 1] = t;
		}
		if (array_t[i] >= t_near)
		{
			t_near = array_t[i]; 
		}
		if (array_t[i + 1] <= t_far)
		{
			t_far = array_t[i + 1]; 
		}
		if (t_near > t_far)
		{
			return false;
		}
		if (t_far < 0)
		{
			return false;
		}
	}
	return true;
}