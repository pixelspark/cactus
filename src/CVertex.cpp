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

CVertex::CVertex() {
	pos = CVector(0.0f,0.0f,0.0f);
	_parent = 0;
	visible = true;
	nx = 0;
	ny = 0;
	tx = 0;
	ty = 0;
	_u = 0;
	_v = 0;
}


CVertex::CVertex(float x, float y, float z, float u, float v) {
	pos = CVector(x,y,z);
	_u = u;
	_v = v;
	_parent = 0;
	visible = true;

	nx = 0;
	ny = 0;
	tx = 0;
	ty = 0;
}


CVertex::CVertex(float x, float y, float z) {
	pos = CVector(x,y,z);
	nx = 0;
	ny = 0;
	tx = 0;
	ty = 0;
	_u = 0;
	_v = 0;
	_parent = 0;
	visible = true;
}

void CVertex::Project(CMatrix* vertexProjection,CMatrix* normalProjection,CCamera* camera) {
	pos2 = pos.Transform(vertexProjection);
	n2 = n.Transform(normalProjection);

	fact = camera->screenscale/camera->fovfact/((pos2._z>0.1)?pos2._z:0.1f);
	_x = (int)(pos2._x*fact+(camera->screenwidth>>1)); 
	_y = (int)(-pos2._y*fact+(camera->screenheight>>1)); 
	_z = 65536.0f*pos2._z;

	nx = (int)(n2._x*127+127);
	ny = (int)(n2._y*127+127);
	
	tx = (int)(_u*_parent->_material.texture._width);
	ty = (int)(_v*_parent->_material.texture._height);
}

CVertex::CVertex(CVector pos,float u,float v) {
	this->pos = pos;
	_u = u;
	_v = v;
	nx = 0;
	ny = 0;
	tx = 0;
	ty = 0;
	_parent = 0;
	visible = true;
}


CVertex::CVertex(CVector pos) {
	this->pos = pos;
	_u = 0;
	_v = 0;
	nx = 0;
	ny = 0;
	tx = 0;
	ty = 0;
	_parent = 0;
	visible = true;
}


bool CVertex::Equals(CVertex v) {
	if((pos._x==v.pos._x)&&(pos._y==v.pos._y)&&(pos._z==v.pos._z)) {
		return true;
	}

	return false;
}


void CVertex::ClipFrustum(int w, int h) {
	clipcode = 0;
	if(_x<0) clipcode |= 1;
	if(_x>=w) clipcode |= 2;
	if(_y<0) clipcode |= 4;
	if(_y>=h) clipcode |= 8;
	if(pos2._z<0) clipcode |= 16;
	visible = (clipcode==0);
}

void CVertex::SetUV(float u,float v) {
	_u = u;
	_v = v;
}

void CVertex::ScaleTextureCoordinates(float fx, float fy) {
	_u *= fx;
	_v *= fy;
}

// does this really work?
void CVertex::Clone(CVertex& target) {
	target = *this;
}

// does this really work?
CVertex CVertex::Clone() {
	return *this;
}

void CVertex::ResetNeighbours() {
	_neighbours.Empty();
}

void CVertex::RegisterNeighbour(CTriangle* t) {
	_neighbours.Add(t);
}

void CVertex::RegenerateNormal() {	
	_neighbours.Restart();
	float nz = 0;
	float nx = 0;
	float ny = 0;

	CTriangle* tri;
	CVector wn;

	while(_neighbours.HasNext()) {
		tri = _neighbours.NextStack();

		wn = tri->GetWeightedNormal();
		nx += wn._x;
		ny += wn._y;
		nz += wn._z;
	}

	n = CVector(nx,ny,nz);
	n.Normalize();
}