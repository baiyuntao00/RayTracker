
#ifndef CAMERA_H
#define CAMERA_H
#define PI 3.1415926
#include "Ray.h"
///�����������
class Camera
{
public:
	Camera(CVector3 lookfrom/*���λ��*/, CVector3 dir,float screen_z);
	Camera(CVector3 lookfrom/*���λ��*/, float screen_z)
	{
		lower_left = CVector3(-0.5, -0.5, screen_z);///���½�
		horizontal = CVector3(1.0, 0.0, 0.0);///ˮƽ
		vertical = CVector3(0.0, 1.0, 0.0);///��ֱ
		origin = lookfrom;
	}
	Ray Get_ray(float s, float t) { 
		dirt = lower_left + s*horizontal + t*vertical - origin;
		return Ray(origin, dirt);
	}
	CVector3 dircam;
	CVector3 origin;//////�����������
	CVector3 dirt;/////���߷�������
	CVector3 lower_left;///��Ļ���½�����
	CVector3 horizontal;///��Ļˮƽ����
	CVector3 vertical;///��Ļ��ֱ����
};
#endif // CAMERA_H