#include "stdafx.h"
#include "Face.h"

Face::Face()
{}
Face::Face(bool en, CVector3 p0, CVector3 p1, CVector3 p2, int i)
{
	is_smooth = en;
	tri_v[0] = p0;
	tri_v[1] = p1;
	tri_v[2] = p2;
	index = i;
	tri_n = Cross(CVector3(tri_v[1] - tri_v[0]), CVector3(tri_v[2] - tri_v[0])).Normalize();
}

bool Face::hit(  Ray& ray, float t_min, float t_max, HitRecord& rec)
{    /*”–Œ Ã‚*/

	float a = tri_v[0].x - tri_v[1].x, b = tri_v[0].x - tri_v[2].x, c = ray.dir.x, d = tri_v[0].x - ray.org.x;
	float e = tri_v[0].y - tri_v[1].y, f = tri_v[0].y - tri_v[2].y, g = ray.dir.y, h = tri_v[0].y - ray.org.y;
	float i = tri_v[0].z - tri_v[1].z, j = tri_v[0].z - tri_v[2].z, k = ray.dir.z, l = tri_v[0].z - ray.org.z;
	float m = f*k - g*j, n = h*k - g*l, p = f*l - h*j;
	float q = g*i - e*k, s = e*j - f*i;

	float inv_denom = 1.0 / (a*m + b*q + c*s);

	float e1 = d*m - b*n - c*p;
	float beta = e1*inv_denom;
	if (beta < 0.0)
		return false;
	float r = e*l - h*i;
	float e2 = a*n + d*q + c*r;
	double gamma = e2*inv_denom;
	if (gamma<0.0)
		return false;
	if (beta + gamma>1.0)
		return false;
	float e3 = a*p - b*r + d*s;
	float t = e3*inv_denom;
	if (t > t_min&& t < t_max)
	{
		rec.t = t;
		rec.P_hit = ray.PointRay(rec.t);
		if (!is_smooth)
		{
			rec.V_hit = tri_n;
		}
		else
		{
			rec.V_hit = Interpolate_Normal(beta, gamma);
		}
		return true;
	}
	return false;
}
CVector3 Face::Interpolate_Normal(float beta,float gamma)
{
	CVector3 normal((1 - beta - gamma)*smooth_vex_n[0] + beta*smooth_vex_n[1] + gamma* smooth_vex_n[2]);
	return normal.Normalize();
}
bool Face::shadowhit(Ray& ray, float tmin)
{
	float a = tri_v[0].x - tri_v[1].x, b = tri_v[0].x - tri_v[2].x, c = ray.dir.x, d = tri_v[0].x - ray.org.x;
	float e = tri_v[0].y - tri_v[1].y, f = tri_v[0].y - tri_v[2].y, g = ray.dir.y, h = tri_v[0].y - ray.org.y;
	float i = tri_v[0].z - tri_v[1].z, j = tri_v[0].z - tri_v[2].z, k = ray.dir.z, l = tri_v[0].z - ray.org.z;

	float m = f*k - g*j, n = h*k - g*l, p = f*l - h*j;
	float q = g*i - e*k, s = e*j - f*i;

	float inv_denom = 1.0 / (a*m + b*q + c*s);

	float e1 = d*m - b*n - c*p;
	float beta = e1*inv_denom;
	if (beta < 0.0)
		return false;
	float r = e*l - h*i;
	float e2 = a*n + d*q + c*r;
	double gamma = e2*inv_denom;
	if (gamma<0.0)
		return false;
	if (beta + gamma>1.0)
		return false;
	float e3 = a*p - b*r + d*s;
	float t = e3*inv_denom;
	if (t > 0.001&& t <tmin)
	{
		return true;
	}
	return false;
}
Vex_Face::Vex_Face()
{
	vexIndex = -1;
}
Vex_Face::~Vex_Face()
{
	vexIndex = -1;
}
Vex_Face::Vex_Face(int v)
{
	vexIndex= v;
}