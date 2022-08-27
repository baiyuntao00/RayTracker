#pragma once
#include"Ray.h"
////��ײ��¼��
///�ýṹ���¼��ײ�㡱������Ϣ����������ľ���t��
///ײ�����������p_hit��ײ����ķ�����V_hit*/
class Material;
struct HitRecord{
	float t;///��������ľ���t
	CVector3 P_hit;////ײ��
	CVector3 V_hit;///ײ����ķ�����V
	Material *mat_ptr;
};
class World
{
public:
	virtual bool Hit(Ray& r, float min, float max, HitRecord& rec)=0;
	virtual bool ShadowHit(Ray& r, float t_min) = 0;
};

