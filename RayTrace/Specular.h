#pragma once
#include "Material.h"
//////���ʣ����淴����
class Specular:public Material
{
public:
	Specular(CVector3 ref, float M,float fa)
		:reflectivity(ref), highLight(M),fade(fa){};
	virtual CRGB LocalLight(Ray& r_in, HitRecord& rec, CVector3 Viewpoint, CVector3 Lightpoint);
	virtual bool Refract(Ray&r_in, Ray& RefractRay, HitRecord& rec){ return false; }
	virtual bool Scatter(Ray&r_in, HitRecord& rec, Ray& scattered);
	~Specular();

private:
	CVector3 reflectivity;////������
	float highLight;/////�߹�ָ��
	float fade;
};

