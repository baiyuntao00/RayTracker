#pragma once
#ifndef MATERIAL_H
#define MATERIAL_H
#include "Object.h"
////////²ÄÖÊ»ùÀà
class Material
{
public:
	virtual bool Refract(Ray&r_in, Ray& RefractRay, HitRecord& rec) = 0;
	virtual CRGB LocalLight(Ray& r_in,HitRecord& rec, CVector3 Viewpoint, CVector3 Lightpoint) = 0;
	virtual bool Scatter(Ray&r_in, HitRecord& rec, Ray& scattered) = 0;
	CRGB lightColor = CRGB(1.0, 1.0, 1.0);
	CRGB locColor;
	CRGB ambColor = CRGB(0.10, 0.10, 0.10);
};

#endif // MATERIAL_H