#include "Material.h"

Material::Material() {
    
}

Material::~Material() {

}
Material::Material(int color) {
    this->setColor(color);   
}

Material::Material(Texture* t) {
    this->setTexture(t);
    this->setReflectivity(255);
}

void Material::setTexture(Texture* tex) {
    this->texture = tex;
}

void Material::setEnvMap(Texture* map) {
    this->envmap = map;
}

void Material::setColor(int color) {
    this->color = color;
}

void Material::setTransparency(int factor) {
    this->transparency = Math::crop(factor,0,255);
    opaque = (transparency==0);
}

void Material::setReflectivity(int factor) {
	this->reflectivity = Math::crop(factor,0,255);
}

void Material::setFlat(bool flat) {
	this->flat = flat;
}

void Material::setWireframe(bool wf) {
	this->wireframe = wf;
}

Texture* Material::getTexture() {
	return this->texture;
}

Texture* Material::getEnvMap() {
	return this->envmap;
}

int Material::getColor() {
	return this->color;
}

int Material::getTransparency() {
	return this->transparency;
}

int Material::getReflectivity() {
	return this->reflectivity;
}

bool Material::isFlat() {
	return this->flat;
}

bool Material::isWireframe() {
	return this->wireframe;
}
