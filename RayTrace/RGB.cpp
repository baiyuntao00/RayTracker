
#include "stdafx.h"
#include "RGB.h"
CRGB::CRGB()
{
	red=0.0;
	green=0.0;
	blue=0.0;
}
CRGB::CRGB(float r,float g,float b)//重载构造函数
{
	red=r;
	green=g;
	blue=b;
}

CRGB::~CRGB()
{

}

CRGB operator +(  CRGB &c1,  CRGB &c2)//+运算符重载
{
	CRGB c;
	c.red=c1.red+c2.red;
	c.green=c1.green+c2.green;
	c.blue=c1.blue+c2.blue;
	return c;
}

CRGB operator -(CRGB &c1,  CRGB &c2)//-运算符重载
{
	CRGB c;
	c.red=c1.red-c2.red;
	c.green=c1.green-c2.green;
	c.blue=c1.blue-c2.blue;
	return c;
}

CRGB operator *(  CRGB &c1,  CRGB &c2)//*运算符重载
{
	CRGB c;
	c.red=c1.red*c2.red;
	c.green=c1.green*c2.green;
	c.blue=c1.blue*c2.blue;
	return c;
}

CRGB operator *(  CRGB &c1,float k)//*运算符重载
{
   CRGB c;
   c.red=k*c1.red;
   c.green=k*c1.green;
   c.blue=k*c1.blue;
   return c;
}

CRGB operator *(float k,  CRGB &c1)//*运算符重载
{
   CRGB c;
   c.red=k*c1.red;
   c.green=k*c1.green;
   c.blue=k*c1.blue;
   return c;
}
CRGB operator *(  CVector3 v,   CRGB &c1)//*运算符重载
{
	CRGB c;
	c.red = v.x*c1.red;
	c.green = v.y*c1.green;
	c.blue = v.z*c1.blue;
	return c;
}

CRGB operator /(  CRGB &c1,float k)///运算符重载
{
   CRGB c;
   c.red=c1.red/k;
   c.green=c1.green/k;
   c.blue=c1.blue/k;
   return c;
}

CRGB operator +=(CRGB &c1,CRGB &c2)//+=运算符重载
{
	c1.red=c1.red+c2.red;
	c1.green=c1.green+c2.green;
	c1.blue=c1.blue+c2.blue;
	return c1;
}
bool operator <(CRGB &c1, float a)//+=运算符重载
{
	if (c1.red < a&&
		c1.green < a&&
		c1.blue < a)
		return true;
	else
		return false;
}
bool operator >(CRGB &c1, float a)//+=运算符重载
{
	if (c1.red > a&&
		c1.green > a&&
		c1.blue > a)
		return true;
	else
		return false;
}

CRGB operator -=(CRGB &c1,CRGB &c2)//-=运算符重载
{
	c1.red=c1.red-c2.red;
	c1.green=c1.green-c2.green;
	c1.blue=c1.blue-c2.blue;
	return c1;
}

CRGB operator *=(CRGB &c1,CRGB &c2)//*=运算符重载
{
	c1.red=c1.red*c2.red;
	c1.green=c1.green*c2.green;
	c1.blue=c1.blue*c2.blue;
	return c1;
}

CRGB operator /=(CRGB &c1,float k)///=运算符重载
{
	c1.red=c1.red/k;
	c1.green=c1.green/k;
	c1.blue=c1.blue/k;
	return c1;
}

CRGB Normalize(CRGB c1)//归一化
{
	CRGB c2;
	c2.red = (c1.red < 0.0) ? 0.0 : ((c1.red > 1.0) ? 1.0 : c1.red);
	c2.green = (c1.green < 0.0) ? 0.0 : ((c1.green > 1.0) ? 1.0 : c1.green);
	c2.blue = (c1.blue < 0.0) ? 0.0 : ((c1.blue > 1.0) ? 1.0 : c1.blue);
	return c2;
}

