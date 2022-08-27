#pragma once
#include "Material.h"
////////材质：漫反射类s
class Diffuse :public Material
{
public:
	Diffuse(CVector3 L,float fa) :
		reflectivity(L),fade(fa){};
	virtual CRGB LocalLight(Ray& r_in, HitRecord& rec, CVector3 Viewpoint, CVector3 Lightpoint);
	virtual bool Refract(Ray&r_in, Ray& RefractRay, HitRecord& rec){ return false; }
	virtual bool Scatter(Ray&r_in, HitRecord& rec, Ray& scattered) { return false; };
	~Diffuse();

private:
	CVector3 reflectivity;////漫反射反射率
	int index;
	float fade;
};

