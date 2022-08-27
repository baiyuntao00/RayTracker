#include "stdafx.h"
#include "Transparent.h"
#include "math.h"
#include <iostream>
#define MAX(a,b) ((a>b)?(a):(b))
#define MIN(a,b) ((a<b)?(a):(b))
using namespace std;

float Schlick(float c, float n)
{
	float r0 = ((1 - n) / (1 + n))*((1 - n) / (1 + n));
	return r0 + (1 - r0)*pow((1 - c), 5);
}
CRGB Transparent::LocalLight(Ray& r_in, HitRecord& rec, CVector3 viewPoint, CVector3 lightPoint)
{
	locColor = CRGB(0.0, 0.0, 0.0);
	CVector3 v_Light(rec.P_hit, lightPoint);//光源方向
	CVector3 v_View(rec.P_hit, viewPoint);///视线方向
	v_Light = v_Light.Normalize();/////单位化
	v_View = v_View.Normalize();
	/////////////镜面反射光
	CVector3 vh = (v_Light + v_View).Normalize();
	float cosTheta = MAX(Dot(vh, rec.V_hit), 0);
	float speIde = pow(cosTheta, shl);
	float t = Schlick(Dot(v_View, rec.V_hit), nIn_nOut);
	locColor += speIde*lightColor*(1 - fadeRefract);
	////////////环境光
	locColor += ambColor;
	return Normalize(locColor);
}
bool Transparent::Refract(Ray&r_in, Ray& refractRay, HitRecord& rec)
{
	CVector3 n = rec.V_hit;
	CVector3 wo = -1*r_in.dir.Normalize();
	float nt = nIn_nOut;
	float cosThetai = Dot(wo, n);
	if (cosThetai < 0.0)
	{
		cosThetai = -cosThetai;
		nt = 1 / nIn_nOut;
		n = -1 * n;
	}
	float temp = 1.0 - (1 - cosThetai *cosThetai) / (nt*nt);
	if (temp < 0)
	{
		/*发生全反射*/
		fadeRefract = 0.0;
		return false;
	}
	fadeRefract = 1.0 - Schlick(cosThetai, nt);
	float cosThetat = sqrt(1.0 - (1 - cosThetai *cosThetai) / (nt*nt));
	CVector3 refracted = -1*wo / nt - (cosThetat - cosThetai / nt)*n;
	refractRay = Ray(rec.P_hit, refracted);//折射光线
	refractRay.intensity = r_in.intensity*fadeRefract;
	refractRay.isFade = false;
	return true;
}
bool Transparent::Scatter(Ray&r_in, HitRecord& rec,Ray& scattered)
{
	CVector3 n = rec.V_hit;//////法向量
	CVector3 rin = r_in.dir.Normalize();
	float nt = nIn_nOut;
	if (Dot(rin, n) >= 0)
	{
		nt = 1 / nIn_nOut;
		n =  -1*n;
	}
	CVector3 reflected = Reflect(rin, n);////////////反射向量
	scattered = Ray(rec.P_hit, reflected);
	scattered.intensity = (1 - fadeRefract)*r_in.intensity;
	scattered.isFade = false;
	return false;
}
