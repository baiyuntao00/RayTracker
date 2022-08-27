#pragma once
#include "Material.h"
class Checker2D :public Material
{
public:
	Checker2D(float s, float fa, CVector3 s1, CVector3 s2) :size(s), fade(fa),speWrite(s1), speBlack(s2){}
	virtual CRGB LocalLight(Ray& r_in, HitRecord& rec, CVector3 Viewpoint, CVector3 Lightpoint);
	virtual bool Refract(Ray&r_in, Ray& RefractRay, HitRecord& rec){ return false; }
	virtual bool Scatter(Ray&r_in, HitRecord& rec,Ray& scattered);
	bool wriorbla(  HitRecord& rec);
	~Checker2D();
private:
	float size;
	CVector3 speWrite,speBlack;////反射率
	float fade; //材料的衰减系数
};

