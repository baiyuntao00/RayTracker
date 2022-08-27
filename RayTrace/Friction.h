#pragma once
#include "Material.h"
class Friction :
	public Material
{
public:
	Friction(CVector3 ref, float M,float fa)
		:reflectivity(ref), highLight(M),fade(fa){};
	virtual CRGB LocalLight(Ray& r_in, HitRecord& rec, CVector3 Viewpoint, CVector3 Lightpoint);
	virtual bool Refract(Ray&r_in, Ray& RefractRay, HitRecord& rec){ return false; }
	virtual bool Scatter(Ray&r_in, HitRecord& rec, Ray& scattered);
	~Friction();

private:
	CVector3 reflectivity;////反射率
	float highLight;/////高光指数
	float fade; //材料的衰减数系
};

