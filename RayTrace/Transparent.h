#pragma once
#include "Material.h"
///���ʣ�͸����
class Transparent :
	/*͸���������ʵ�ʵ��������*/
	public Material
{
public:
	Transparent(CVector3 sp,float hs,float R/*������*/)
		:reflectivity(sp), shl(hs),nIn_nOut(R){};
	virtual bool Refract(Ray&r_in, Ray& RefractRay, HitRecord& rec);
	virtual CRGB LocalLight(Ray& r_in, HitRecord& rec, CVector3 Viewpoint, CVector3 Lightpoint);
	virtual bool Scatter(Ray&r_in, HitRecord& rec, Ray& scattered);
	CVector3 reflectivity;////
	float shl;///�߹�
	float nIn_nOut;//////������
	float fadeRefract;///˥��
	float fade;
private:
};

