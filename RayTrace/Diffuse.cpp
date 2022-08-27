#include "stdafx.h"
#include "Diffuse.h"
#include <iostream>
#define MAX(a,b) ((a>b)?(a):(b))
#define MIN(a,b) ((a<b)?(a):(b))
using namespace std;
#define MAX(a,b) ((a>b)?(a):(b))

Diffuse::~Diffuse()
{
}
//////////////�ֲ�����ģ��
CRGB Diffuse::LocalLight(Ray& r_in, HitRecord& rec, CVector3 viewPoint, CVector3 lightPoint)
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
	float speIde = pow(cosTheta, 100);
	locColor += speIde*lightColor*0.25;
	////////////������
	locColor += ambColor;
	///ֱ������˥��
	r_in.intensity = r_in.intensity*fade;
	locColor = locColor*r_in.intensity;
	return Normalize(locColor);
}