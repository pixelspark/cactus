/* ---------------------------------------------------------------------------------------------------------------------------------------------------
Copyright (C) 2003-2004 Tommy van der Vorst

This library is free software; you can redistribute it and/or
modify it under the terms of the GNU Lesser General Public
License as published by the Free Software Foundation; either
version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
License along with this library; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
--------------------------------------------------------------------------------------------------------------------------------------------------- */
#include "../include/cactus.h"
using namespace cactus;

CCamera::CCamera() {
	SetFov(90);
	_fov = 90;
	roll = 0;
	needsRebuild = true;
}

CCamera::CCamera(float fov) {
	SetFov(fov);
	roll = 0;
	_fov = fov;
	needsRebuild = true;
}

CCamera::~CCamera() {
}

CMatrix* CCamera::GetMatrix() {
	RebuildMatrices();
	return &matrix;
}

CMatrix* CCamera::GetNormalMatrix() {
	RebuildMatrices();
	return &normalmatrix;
}

void CCamera::RebuildMatrices() {
	if(!needsRebuild) {
		return;
	}

	needsRebuild = false;
	CVector forward = CVector::Subtract(lookat,pos);
	CVector up = CVector(0,1,0);
	CVector right = CVector::GetNormal(up,forward);

	forward.Normalize();
	up.Normalize();
	right.Normalize();

	normalmatrix = CMatrix(right,up,forward);
	normalmatrix.Rotate(0,0,roll);
	normalmatrix.Clone(matrix);
	matrix.Shift(pos._x,pos._y,pos._z);
	
	normalmatrix = normalmatrix.Inverse();
	matrix = matrix.Inverse();
}


void CCamera::SetFov(float fov) {
	_fov = fov;
	fovfact = (float)(tan(deg2rad(fov)/2));
}

float CCamera::GetFov() {
	return _fov;
}

void CCamera::SetPos(CVector p) {
	pos = p;
	needsRebuild = true;
}

void CCamera::SetPos(float px, float py, float pz) {
	pos = CVector(px,py,pz);
	needsRebuild = true;
}

void CCamera::Roll(float angle) {
	roll += angle;
	needsRebuild = true;
}

void CCamera::LookAt(CVector p) {
	lookat = p;
	needsRebuild = true;
}

void CCamera::LookAt(float px,float py,float pz) {
	lookat = CVector(px,py,pz);
	needsRebuild = true;
}

void CCamera::SetScreenSize(int w,int h) {
	screenwidth = w;
	screenheight = h;
	screenscale=(w<h)?w:h;
}


void CCamera::Shift(float dx,float dy,float dz) {
	pos = pos.Transform(CMatrix::ShiftMatrix(dx,dy,dz));
	lookat = lookat.Transform(CMatrix::ShiftMatrix(dx,dy,dz));
	needsRebuild = true;
}

void CCamera::Shift(CVector v) {
	Shift(v._x,v._y,v._z);
}

void CCamera::Rotate(float dx,float dy,float dz) {
	pos = pos.Transform(CMatrix::RotateMatrix(dx,dy,dz));
	needsRebuild = true;
}

void CCamera::Rotate(CVector v) {
	Rotate(v._x,v._y,v._z);
}
