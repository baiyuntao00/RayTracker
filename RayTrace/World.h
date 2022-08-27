#pragma once
#include"Ray.h"
////碰撞纪录类
///该结构体记录“撞点”处的信息：离光线起点的距离t、
///撞点的坐标向量p_hit、撞点出的法向量V_hit*/
class Material;
struct HitRecord{
	float t;///离光线起点的距离t
	CVector3 P_hit;////撞点
	CVector3 V_hit;///撞点出的法向量V
	Material *mat_ptr;
};
class World
{
public:
	virtual bool Hit(Ray& r, float min, float max, HitRecord& rec)=0;
	virtual bool ShadowHit(Ray& r, float t_min) = 0;
};

