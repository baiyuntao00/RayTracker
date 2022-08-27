#include "stdafx.h"
#include "Camera.h"
Camera::Camera(CVector3 l/*œ‡ª˙Œª÷√*/, CVector3 dir, float screen_z)
:origin(l), dircam(dir)
{

	CVector3 vec_z = origin.Normalize();
	CVector3 vec_y = dircam.Normalize();
	CVector3 vec_x = Cross(vec_y, vec_z).Normalize();
	horizontal = vec_x*1.0;
	vertical = vec_y*1.0;
	CVector3 screenori = origin - vec_z* screen_z;
	lower_left = screenori - vec_y*0.5 - vec_x*0.5;
}