#pragma once
#ifndef _Ray3_h_
#define _Ray3_h_
#include"Vector3.h"
#include"RGB.h"
#include <limits>
using namespace std;
///光线类
class Ray
{
public:
	Ray();
	Ray(CRGB rgb) :ray_rgb(rgb){ isFade = true,intensity = 1.0, len = (numeric_limits<float>::max)(); };
	Ray(CVector3& a, CVector3& b) :org(a), dir(b){ isFade=true, intensity = 1.0, len = (numeric_limits<float>::max)(); }
	CVector3 PointRay(float t) { return org + t*dir; }/*返回撞击点*/
public:
	CVector3 org/*光线起点*/, dir/*光线方向*/;
	bool isFade;///次代光线是否要衰减（）
	float len;///光线的长度（起点到撞击点，若无撞击，则设为500）
	float intensity;///1.0的强度表示直射光
	CRGB ray_rgb/*光线颜色*/;
};
#endif
