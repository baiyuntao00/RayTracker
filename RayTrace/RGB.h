
#include"Vector3.h"
class CRGB  
{
public:
	CRGB();
	CRGB(float,float,float);
	virtual ~CRGB();
	friend CRGB operator+(  CRGB &,  CRGB &);//���������
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
	friend CRGB  Normalize(CRGB);	//��һ����[0,1]����
public:
	float   red;
	float green;
	float  blue;
};
