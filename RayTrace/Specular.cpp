#include "stdafx.h"
#include "Specular.h"
#define MAX(a,b) ((a>b)?(a):(b))
#define MIN(a,b) ((a<b)?(a):(b))
CVector3 GetRandom();

Specular::~Specular()
{
}
//////////////局部光照模型
CRGB Specular::LocalLight(Ray& r_in, HitRecord& rec, CVector3 viewPoint, CVector3 lightPoint)
{
	locColor = CRGB(0.0, 0.0, 0.0);
	CVector3 v_Light(rec.P_hit, lightPoint);//光源方向
	CVector3 v_View(rec.P_hit, viewPoint);///视线方向
	v_Light = v_Light.Normalize();/////单位化
	v_View = v_View.Normalize();
	/////漫反射光
	float cosAlfa = MAX(Dot(v_Light, rec.V_hit), 0);
	locColor += reflectivity*lightColor*cosAlfa;
	///////镜面反射光
	CVector3 vh = (v_Light + v_View) / (v_Light + v_View).Mag();
	float cosTheta = MAX(Dot(vh, rec.V_hit), 0);
	float speIde = pow(cosTheta, highLight);
	locColor += speIde*lightColor*0.4;//光照系数为0.5
	////////////环境光
	locColor += ambColor;
	///直射光材料衰减
	r_in.intensity = r_in.intensity*fade;///
	locColor = locColor*r_in.intensity;
	return Normalize(locColor);
}
bool Specular::Scatter(Ray&r_in, HitRecord& rec, Ray& scattered)
{
	CVector3 reflected = Reflect(r_in.dir.Normalize(), rec.V_hit);
	scattered = Ray(rec.P_hit, reflected);///镜面反射的反射光
	///反射光光材料衰减
	scattered.intensity = fade*r_in.intensity;
	scattered.isFade = false;
	return (Dot(scattered.dir, rec.V_hit) > 0);
}