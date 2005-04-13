#include "CoreObject.h"

CoreObject::CoreObject() {
}

CoreObject::~CoreObject() {
}

void CoreObject::Transform(Matrix m) {
	matrix.transform(m);
	normalmatrix.transform(m);
}

void CoreObject::Shift(float dx,float dy,float dz) {
	matrix.shift(dx,dy,dz);
}

void CoreObject::Shift(Vector v) {
	Shift(v.x,v.y,v.z);
}

void CoreObject::Scale(float d) {
	matrix.scale(d);
}

void CoreObject::Scale(float dx,float dy,float dz) {
	matrix.scale(dx,dy,dz);
}

void CoreObject::ScaleSelf(float dx,float dy,float dz) {
	matrix.scaleSelf(dx,dy,dz);
}

void CoreObject::ScaleSelf(float d) {
	matrix.scaleSelf(d);
}

void CoreObject::Rotate(Vector d) {
	RotateSelf(d.x,d.y,d.z);
}

void CoreObject::RotateSelf(Vector d) {
	RotateSelf(d.x,d.y,d.z);
}

void CoreObject::Rotate(float dx,float dy,float dz) {
	matrix.rotate(dx,dy,dz);
	normalmatrix.rotate(dx,dy,dz);
}

void CoreObject::RotateSelf(float dx,float dy,float dz) {
	matrix.rotateSelf(dx,dy,dz);
	normalmatrix.rotateSelf(dx,dy,dz);
}

void CoreObject::SetPos(float x,float y,float z) {
	matrix.m03 = x;
	matrix.m13 = y;
	matrix.m23 = z;
}

void CoreObject::SetPos(Vector v) {
	SetPos(v.x,v.y,v.z);
}

Vector CoreObject::GetPos() {
	Vector v;
	v.x = matrix.m03;
	v.y = matrix.m13;
	v.z = matrix.m23;

	return v;
}