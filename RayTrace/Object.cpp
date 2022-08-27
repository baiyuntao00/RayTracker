#include "stdafx.h"
#include "Object.h"

Object::Object()
{
	obj_f_num = 0;
}
Object::~Object()
{
	delete obj_mat;
}
Object::Object(int in, vector<Face>f/*面片集*/, int n/*面片数量*/, Material *m/*物体材质*/, bool b,CVector3 r, CVector3 l)
{
	obj_index =in;
	enablebox = b;
	obj_face = f;
	obj_f_num = n;
	obj_mat = m;
	ru = r;
	ld = l;
}
bool Object::Hit(Ray& r, float t_min, float t_max, HitRecord& rec) 
{
	HitRecord tempRec;
	bool isHit = false;
	float clo_far = t_max;
	if (enablebox)
	{
		Box b = Box(ru, ld);
		if (b.IsHitBox(r, t_min, t_max))
		{/*如果光线与景物包围盒相交*/
			for (int i = 0; i < this->obj_f_num; i++)
			{
				if (obj_face[i].hit(r, t_min, clo_far, tempRec))
				{
					isHit = true;
					clo_far = tempRec.t;
					rec = tempRec;
					rec.mat_ptr = obj_mat;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < this->obj_f_num; i++)
		{
			if (obj_face[i].hit(r, t_min, clo_far, tempRec))
			{
				isHit = true;
				clo_far = tempRec.t;
				rec = tempRec;
				rec.mat_ptr = obj_mat;
			}
		}
	}
	return  isHit;
}
bool Object::ShadowHit(Ray& r, float tmin)  
{
	bool isHit = false;
	if (enablebox)
	{
		Box b = Box(ru, ld);
		if (b.IsHitBox(r, tmin,1000))
		{/*如果光线与景物包围盒相交*/
			for (int i = 0; i < this->obj_f_num; i++)
			{
				if (obj_face[i].shadowhit(r, tmin))
				{
					isHit = true;
				}
			}
		}
	}
	else
	{
		for (int i = 0; i < this->obj_f_num; i++)
		{
			if (obj_face[i].shadowhit(r, tmin))
			{
				isHit = true;
			}
		}
	}
	return  isHit;
}
