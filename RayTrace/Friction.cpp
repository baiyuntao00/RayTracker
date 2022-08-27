#include "stdafx.h"
#include "Friction.h"
#define MAX(a,b) ((a>b)?(a):(b))
#define MIN(a,b) ((a<b)?(a):(b))
CVector3 GetRandom();

Friction::~Friction()
{
}
//////////////�ֲ�����ģ��
CRGB Friction::LocalLight(Ray& r_in, HitRecord& rec, CVector3 viewPoint, CVector3 lightPoint)
{
	locColor = CRGB(0.0, 0.0, 0.0);
	CVector3 v_Light(rec.P_hit, lightPoint);//��Դ����
	CVector3 v_View(rec.P_hit, viewPoint);///���߷���
	v_Light = v_Light.Normalize();/////��λ��
	v_View = v_View.Normalize();
	/////�������
	float cosAlfa = MAX(Dot(v_Light, rec.V_hit), 0);
	locColor += reflectivity*lightColor*cosAlfa;
	///////���淴���
	CVector3 vh = (v_Light + v_View).Normalize();
	float cosTheta = MAX(Dot(vh, rec.V_hit), 0);
	float speIde = pow(cosTheta, highLight);
	locColor += speIde*lightColor*0.5;//����ϵ��Ϊ0.5
	////////////������
	locColor += ambColor;
	///ֱ������˥��
	r_in.intensity = r_in.intensity*fade;///
	locColor = locColor*r_in.intensity;
	return Normalize(locColor);
}
bool Friction::Scatter(Ray&r_in, HitRecord& rec, Ray& scattered)
{
	CVector3 reflected = Reflect(r_in.dir.Normalize(), rec.V_hit);
	scattered = Ray(rec.P_hit, RandomVec(reflected, 0.1));///���淴��ķ����
	///���������˥��
	scattered.intensity = fade*r_in.intensity;
	return (Dot(scattered.dir, rec.V_hit) > 0);
}