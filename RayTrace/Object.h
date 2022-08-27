#pragma once
#ifndef OBJECT_H
#define OBJECT_H
#include"World.h"
#include"Box.h"
#include"Face.h"
class Object :public World
{
public:
	Object();
	~Object();
	Object(int , vector<Face>, int/*��Ƭ����*/, Material */*�������*/, bool, CVector3 /*ru*/, CVector3 /*ld*/);
	virtual bool Hit(  Ray& r, float t_min, float t_max, HitRecord& rec) ;
	virtual bool ShadowHit(  Ray& r, float tmin)  ;
	bool enablebox;/*��Ǹþ����Ƿ�Ҫʹ�ð�Χ�м�*/
	CVector3 ru, ld;
	int obj_index;
	vector<Face>obj_face;
	int obj_f_num;/*��Ƭ����*/
	Material *obj_mat;
};
#endif // SPHERE_H
