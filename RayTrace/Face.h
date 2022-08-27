#pragma once
#ifndef FACE_H
#define FACE_H
#include "World.h"
#include <vector>
using namespace std;
class Face
{
public:
	Face();
	Face(bool ,/*是否网格平滑*/CVector3, CVector3, CVector3, int/*面片索引*/);
	bool hit(  Ray& r, float tmin, float tmax, HitRecord& rec);///判断光线是否与单位面片相交
	bool shadowhit(  Ray& r, float tmin);///判断阴影光线是否与单位面片相交
	CVector3 Interpolate_Normal(float, float);/*法向量线性插值*/
	bool is_smooth;/*是否网格平滑*/
	int index;
	CVector3 tri_v[3];
	CVector3 tri_n;
	CVector3 smooth_vex_n[3];
};
struct Vex_Face
{
	Vex_Face();
	~Vex_Face();
	Vex_Face(int/*顶点索引*/);
	int vexIndex;/*顶点索引*/
	vector<int>faceIndex;/*共三角面片索引*/
};
#endif
