#pragma once
#ifndef HitGroup_H
#define HitGroup_H
#include "World.h"
class HitGroup : public World
{
public:
	HitGroup();
	~HitGroup();
	HitGroup(World **l, int n) :obj_list(l), obj_num(n){}
	virtual bool Hit(  Ray& r, float tmin, float tmax, HitRecord& rec)  ;
	virtual bool ShadowHit(  Ray& r, float tmin)  ;
	World **obj_list;///////物体清单
	int obj_num;
};
#endif // SPHERE_H
