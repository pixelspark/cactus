#include "Light.h"

Light::Light(Vector direction,int diffuse,int specular,int highlightSheen,int highlightSpread) {
	v = direction.Clone();
	v.Normalize();
	this->diffuse = diffuse;
	this->specular = specular;
	this->highlightSheen = highlightSheen;
	this->highlightSpread = highlightSpread;
}

Light::Light(Vector direction,int color,int highlightSheen,int highlightSpread) {
	v = direction.Clone();
	v.Normalize();
	this->diffuse = color;
	this->specular = color;
	this->highlightSheen = highlightSheen;
	this->highlightSpread = highlightSpread;
}

Light::Light(Vector direction,int diffuse) {
	v = direction.Clone();
	v.Normalize();
	this->diffuse = diffuse;
}

Light::Light(Vector direction) {
	v = direction.Clone();
	v.Normalize();
}

Light::~Light() {

}

void Light::project(Matrix m) {
	matrix2 = matrix.GetClone();
	matrix2.transform(m);
	v2 = v.Transform(matrix2);
}
