
#include"Vector3.h"
class CRGB  
{
public:
	CRGB();
	CRGB(float,float,float);
	virtual ~CRGB();
	friend CRGB operator+(  CRGB &,  CRGB &);//运算符重载
	friend CRGB operator-(  CRGB &,  CRGB &);
	friend CRGB operator*(  CRGB &,  CRGB &);
	friend CRGB operator*(  CRGB &,float);
	friend CRGB operator*(float,  CRGB &);
	friend CRGB operator*(  CVector3,   CRGB &);
	friend CRGB operator/(  CRGB &,float);
	friend CRGB operator+=(CRGB &,CRGB &);
	friend CRGB operator-=(CRGB &,CRGB &);
	friend CRGB operator*=(CRGB &,CRGB &);
	friend bool operator <(CRGB &c1, float);
	friend bool operator >(CRGB &c1, float);
	friend CRGB operator/=(CRGB &,float);
	friend CRGB  Normalize(CRGB);	//归一化到[0,1]区间
public:
	float   red;
	float green;
	float  blue;
};
