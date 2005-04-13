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

CScene::CScene(): _renderer(this) {
	_readyForRendering = false;
	_needsRebuild = false;
	_lightNeedsRebuild = false;
	_height = 0;
	_width = 0;
	_backgroundColor.Reset();
}

CScene::~CScene() {
}

void CScene::AddObject(CObject* t) {
	_objects.Add(t);
	//t->SetTriangleParent();
	_needsRebuild = true;
}

void CScene::AddLight(CLight* light) {
	_lights.Add(light);
	_lightNeedsRebuild = true;
}

CObject* CScene::At(int i) {
	return *_objects.At(i);
}

void CScene::Clear() {
	_objects.Empty();
	_lights.Empty();
	_needsRebuild = true;
	_lightNeedsRebuild = true;
	_readyForRendering = false;
}

void CScene::Rebuild() {
	_needsRebuild = false;
	_lightNeedsRebuild = false;
	_objects.Restart();
	CObject* cur;

	while(_objects.HasNext()) {
		cur = *_objects.Next();
		cur->Rebuild();
	}
}

CRenderer* CScene::GetRenderer() {
	return &_renderer;
}

void CScene::Prepare() {
	if(_readyForRendering) {
		return;
	}

	Rebuild();
	_renderer.BuildLightmap();
	_readyForRendering = true;
}

void CScene::Transform(CMatrix& mat) {
	_matrix.Transform(mat);
	_normalMatrix.Transform(mat);
}

void CScene::Rotate(float dx, float dy, float dz) {
	_matrix.Rotate(dx, dy, dz);
	_normalMatrix.Rotate(dx, dy, dz);
}

void CScene::Rotate(CVector& d) {
	Rotate(d._x,d._y,d._z);
}

void CScene::RotateSelf(float dx, float dy, float dz) {
	_matrix.RotateSelf(dx, dy, dz);
	_normalMatrix.RotateSelf(dx, dy, dz);
}

void CScene::RotateSelf(CVector& d) {
	RotateSelf(d._x, d._y, d._z);
}

void CScene::Scale(float sx, float sy, float sz) {
	_matrix.Scale(sx, sy, sz);
	//_normalMatrix.Scale(sx, sy, sz);
}

void CScene::Scale(float d) {
	Scale(d,d,d);
}

void CScene::ScaleSelf(float dx, float dy, float dz) {
	_matrix.ScaleSelf(dx,dy,dz);
	//_normalMatrix.ScaleSelf(dx,dy,dz);
}

void CScene::ScaleSelf(float d) {
	ScaleSelf(d,d,d);
}

void CScene::SetPos(CVector& pos) {
	SetPos(pos._x, pos._y, pos._z);
}

void CScene::SetPos(float x, float y, float z) {
	_matrix.m03 = x;
	_matrix.m13 = y;
	_matrix.m23 = z;
}

void CScene::Shift(CVector& v) {
	Shift(v._x, v._y, v._z);
}

void CScene::Shift(float dx, float dy, float dz) {
	_matrix.Shift(dx,dy,dz);
}


