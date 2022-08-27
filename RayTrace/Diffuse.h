#pragma once
#include "Material.h"
////////���ʣ���������s
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
	CVector3 reflectivity;////�����䷴����
	int index;
	float fade;
};

