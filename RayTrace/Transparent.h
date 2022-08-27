#pragma once
#include "Material.h"
///材质：透明类
class Transparent :
	/*透明玻璃材质的实现有问题*/
	public Material
{
public:
	Transparent(CVector3 sp,float hs,float R/*折射率*/)
		:reflectivity(sp), shl(hs),nIn_nOut(R){};
	virtual bool Refract(Ray&r_in, Ray& RefractRay, HitRecord& rec);
	virtual CRGB LocalLight(Ray& r_in, HitRecord& rec, CVector3 Viewpoint, CVector3 Lightpoint);
	virtual bool Scatter(Ray&r_in, HitRecord& rec, Ray& scattered);
	CVector3 reflectivity;////
	float shl;///高光
	float nIn_nOut;//////折射率
	float fadeRefract;///衰减
	float fade;
private:
};

