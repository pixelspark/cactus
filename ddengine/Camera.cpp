#include "Camera.h"

Camera::Camera() {
	SetFov(90);
}

Camera::~Camera() {
}

Camera::Camera(float fov) {
	SetFov(fov);
}

Matrix Camera::GetMatrix() {
	RebuildMatrices();
	return matrix;
}

Matrix Camera::GetNormalMatrix() {
	RebuildMatrices();
	return normalmatrix;
}

void Camera::RebuildMatrices() {
	if (!needsRebuild) {
		return;
	}

	needsRebuild = false;

	Vector forward = Vector::sub(lookat,pos);
	Vector up = Vector(0,1,0);
	Vector right = Vector::GetNormal(up,forward);

	forward.Normalize();
	up.Normalize();
	right.Normalize();

	normalmatrix = Matrix(right,up,forward);
	normalmatrix.rotate(0,0,roll);
	normalmatrix.Clone(matrix);
	matrix.shift(pos.x,pos.y,pos.z);
	
	normalmatrix = normalmatrix.inverse();
	matrix = matrix.inverse();
}

void Camera::SetFov(float fov) {
	fovfact = (float)(tan(Math::deg2rad(fov))/2);
}	

void Camera::Roll(float angle) {
	roll += angle;
	needsRebuild = true;
}

void Camera::SetPos(float px,float py,float pz) {
	pos = Vector(px,py,pz);
	needsRebuild = true;
}

void Camera::SetPos(Vector p) {
	pos = p;
	needsRebuild = true;
}

void Camera::LookAt(Vector p) {
	lookat = p;
	needsRebuild = true;
}

void Camera::LookAt(float px,float py,float pz) {
	lookat = Vector(px,py,pz);
	needsRebuild = true;
}

void Camera::SetScreenSize(int w,int h) {
	screenwidth = w;
	screenheight = h;
}

void Camera::Shift(float dx,float dy,float dz) {
	pos = pos.Transform(Matrix::shiftMatrix(dx,dy,dz));
	lookat = lookat.Transform(Matrix::shiftMatrix(dx,dy,dz));
	needsRebuild = true;
}

void Camera::Shift(Vector v) {
	Shift(v.x,v.y,v.z);
}

void Camera::Rotate(float dx,float dy,float dz) {
	pos = pos.Transform(Matrix::rotateMatrix(dx,dy,dz));
	needsRebuild = true;
}

void Camera::Rotate(Vector v) {
	Rotate(v.x,v.y,v.z);
}

