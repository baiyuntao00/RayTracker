#pragma once
#include "Ray.h"
///��Χ��
class Box
{
public:
	Box(){};
	~Box(){};
	Box(CVector3 ru, CVector3 ld) :vex_ru(ru), vex_ld(ld){}///�����Χ����
	Box(CVector3, CVector3, CVector3);///��������Ƭ��Χ����
	bool IsHitBox(Ray ,float,float);
	CVector3 vex_ru, vex_ld;///��Χ�����ϵ�����µ�
	CVector3 pmin, pmax;
};

