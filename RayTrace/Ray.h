#pragma once
#ifndef _Ray3_h_
#define _Ray3_h_
#include"Vector3.h"
#include"RGB.h"
#include <limits>
using namespace std;
///������
class Ray
{
public:
	Ray();
	Ray(CRGB rgb) :ray_rgb(rgb){ isFade = true,intensity = 1.0, len = (numeric_limits<float>::max)(); };
	Ray(CVector3& a, CVector3& b) :org(a), dir(b){ isFade=true, intensity = 1.0, len = (numeric_limits<float>::max)(); }
	CVector3 PointRay(float t) { return org + t*dir; }/*����ײ����*/
public:
	CVector3 org/*�������*/, dir/*���߷���*/;
	bool isFade;///�δ������Ƿ�Ҫ˥������
	float len;///���ߵĳ��ȣ���㵽ײ���㣬����ײ��������Ϊ500��
	float intensity;///1.0��ǿ�ȱ�ʾֱ���
	CRGB ray_rgb/*������ɫ*/;
};
#endif
