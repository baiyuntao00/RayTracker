#include "stdafx.h"
#include "Checker2D.h"
#define MAX(a,b) ((a>b)?(a):(b))
#define MIN(a,b) ((a<b)?(a):(b))

CRGB Checker2D::LocalLight(Ray& r_in, HitRecord& rec, CVector3 viewPoint, CVector3 lightPoint)
{
	CVector3 reflectivity;
	if (wriorbla(rec))
	{
		reflectivity = speWrite;
	}
	else
	{
		reflectivity = speBlack;
	}
	locColor = CRGB(0.0, 0.0, 0.0);
	CVector3 v_Light(rec.P_hit, lightPoint);//��Դ����
	CVector3 v_View(rec.P_hit, viewPoint);///���߷���
	v_Light = v_Light.Normalize();/////��λ��
	v_View = v_View.Normalize();
	/////�������
	float cosAlfa = MAX(Dot(v_Light, rec.V_hit), 0);
	locColor += reflectivity*lightColor*cosAlfa;
	////////////������
	locColor += ambColor;
	///ֱ������˥��
	r_in.intensity = r_in.intensity*fade;
	locColor = locColor*r_in.intensity;
	return Normalize(locColor);
}
bool Checker2D::wriorbla(  HitRecord& rec)
{
	float x = rec.P_hit.x ;
	float y = rec.P_hit.y ;
	float z = rec.P_hit.z ;
	if (((int)floor(x / size) + (int)floor(z / size) + (int)floor(y / size)) % 2 == 0)
		return true;
	else
		return false;
}
bool Checker2D::Scatter(Ray&r_in,HitRecord& rec,Ray& scattered) 
{
		CVector3 reflected = Reflect(r_in.dir.Normalize(), rec.V_hit);
		scattered = Ray(rec.P_hit, reflected);///��ȡ���淴��ķ������
		///���������˥��
		scattered.intensity = r_in.intensity*fade;	
		return (Dot(scattered.dir, rec.V_hit) > 0);
}