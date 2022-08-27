#pragma once
#include "Ray.h"
///包围盒
class Box
{
public:
	Box(){};
	~Box(){};
	Box(CVector3 ru, CVector3 ld) :vex_ru(ru), vex_ld(ld){}///景物包围盒用
	Box(CVector3, CVector3, CVector3);///三角形面片包围盒用
	bool IsHitBox(Ray ,float,float);
	CVector3 vex_ru, vex_ld;///包围盒右上点和左下点
	CVector3 pmin, pmax;
};

