#include "stdafx.h"
#include "HitGroup.h"


HitGroup::~HitGroup()
{
	for (int i = 0; i < obj_num; i++)
	{
		delete[]obj_list[i];
		obj_list[i] = NULL;
	}
	delete obj_list;
	obj_list = NULL;
}
bool HitGroup::Hit(  Ray& r, float t_min, float t_max, HitRecord& rec)   {
	HitRecord tempRec;
	bool isHit = false;
	float clo_far = t_max;
	for (int i = 0; i < obj_num; i++) {
		if (obj_list[i]->Hit(r, t_min, clo_far, tempRec))
		{
			isHit = true;
			clo_far = tempRec.t;
			rec = tempRec;
		}
	}
	return isHit;
}
bool HitGroup::ShadowHit(  Ray& r, float t_min)  
{
	for (int i = 0; i < obj_num; i++)
	{
		if (obj_list[i]->ShadowHit(r, t_min))
			return true;
	}
	return false;
}