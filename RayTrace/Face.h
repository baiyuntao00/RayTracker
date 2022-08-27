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
	Face(bool ,/*�Ƿ�����ƽ��*/CVector3, CVector3, CVector3, int/*��Ƭ����*/);
	bool hit(  Ray& r, float tmin, float tmax, HitRecord& rec);///�жϹ����Ƿ��뵥λ��Ƭ�ཻ
	bool shadowhit(  Ray& r, float tmin);///�ж���Ӱ�����Ƿ��뵥λ��Ƭ�ཻ
	CVector3 Interpolate_Normal(float, float);/*���������Բ�ֵ*/
	bool is_smooth;/*�Ƿ�����ƽ��*/
	int index;
	CVector3 tri_v[3];
	CVector3 tri_n;
	CVector3 smooth_vex_n[3];
};
struct Vex_Face
{
	Vex_Face();
	~Vex_Face();
	Vex_Face(int/*��������*/);
	int vexIndex;/*��������*/
	vector<int>faceIndex;/*��������Ƭ����*/
};
#endif
