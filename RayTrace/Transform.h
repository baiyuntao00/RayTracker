#pragma once
#include "Matrix.h"
#include "Vector3.h"
class Transform
{
public:
	Transform();
	Transform(CVector3 ax, CVector3 in) :maxp(ax), minp(in){};
	~Transform();
	friend CVector3 ZoomTran(CVector3, float zoom);
	friend CVector3 MoveTran(CVector3, float x, float y, float z);
    CVector3 RotateTran(char, CVector3, float);
private:
	CVector3 minp, maxp;
};

