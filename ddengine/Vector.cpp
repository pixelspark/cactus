#include "Vector.h"

Vector::Vector() {
	// do nothing
}

Vector::Vector(float xpos,float ypos,float zpos) {
	x = xpos;
	y = ypos;
	z = zpos;
}

Vector::~Vector() {
}

Vector Vector::Normalize() {
	float dist = Length();
	if(dist==0) {
		return *this;
	}
	float invdist = 1/dist;
	x *= invdist;
	y *= invdist;
	z *= invdist;
	return *this;
}

Vector Vector::Reverse() {
	x = -x;
	y = -y;
	z = -z;

	return *this;
}

float Vector::Length() {
	return (float)sqrt(x*x+y*y+z*z);
}

Vector Vector::Transform(Matrix m) {
	float newx = x*m.m00 + y*m.m01 + z*m.m02 + m.m03;
	float newy = x*m.m10 + y*m.m11 + z*m.m12 + m.m13;
	float newz = x*m.m20 + y*m.m21 + z*m.m22 + m.m23;

	return Vector(newx,newy,newz);
}

void Vector::BuildCylindric() {
	r = (float)sqrt(x*x+y*y);
	theta = (float)atan2(x,y);
}

Vector Vector::Clone() {
	return Vector(x,y,z);
}

void Vector::BuildCarthesian() {
	x = (float)(r*cos(theta));
	y = (float)(r*sin(theta));
}
