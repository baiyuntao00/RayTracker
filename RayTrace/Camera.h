
#ifndef CAMERA_H
#define CAMERA_H
#define PI 3.1415926
#include "Ray.h"
///其他：相机类
class Camera
{
public:
	Camera(CVector3 lookfrom/*相机位置*/, CVector3 dir,float screen_z);
	Camera(CVector3 lookfrom/*相机位置*/, float screen_z)
	{
		lower_left = CVector3(-0.5, -0.5, screen_z);///左下角
		horizontal = CVector3(1.0, 0.0, 0.0);///水平
		vertical = CVector3(0.0, 1.0, 0.0);///竖直
		origin = lookfrom;
	}
	Ray Get_ray(float s, float t) { 
		dirt = lower_left + s*horizontal + t*vertical - origin;
		return Ray(origin, dirt);
	}
	CVector3 dircam;
	CVector3 origin;//////光线起点向量
	CVector3 dirt;/////光线方向向量
	CVector3 lower_left;///屏幕左下角坐标
	CVector3 horizontal;///屏幕水平向量
	CVector3 vertical;///屏幕竖直向量
};
#endif // CAMERA_H