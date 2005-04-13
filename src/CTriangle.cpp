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

CVector CTriangle::GetCenter() {
	float cx=(_a->pos._x+_b->pos._x+_c->pos._x)/3;
	float cy=(_a->pos._y+_b->pos._y+_c->pos._y)/3;
	float cz=(_a->pos._z+_b->pos._z+_c->pos._z)/3;
	return CVector(cx,cy,cz);
}

CVertex CTriangle::GetMedium() {
	float cx=(_a->pos._x+_b->pos._x+_c->pos._x)/3;
	float cy=(_a->pos._y+_b->pos._y+_c->pos._y)/3;
	float cz=(_a->pos._z+_b->pos._z+_c->pos._z)/3;
	float cu=(_a->_u+_b->_u+_c->_u)/3;
	float cv=(_a->_v+_b->_v+_c->_v)/3;
	return CVertex(cx,cy,cz,cu,cv);
}

CVector CTriangle::GetWeightedNormal() {
	return CVector::VectorProduct(_a->pos,_b->pos,_c->pos);	
}

void CTriangle::RegenerateNormal() {
	n=CVector::GetNormal(_a->pos,_b->pos,_c->pos);
}

// backface culling and frustum clipping
void CTriangle::ClipFrustum(int w,int h) {
	outOfFrustum = (_a->clipcode&_b->clipcode&_c->clipcode)!=0;
	
	if(outOfFrustum) {
		_visible = false;
		return;
	}

	if(n2._z>0.5f) { // >
		_visible = true;
		return;
	}

	triangleCenter._x = (_a->pos2._x+_b->pos2._x+_c->pos2._x);
	triangleCenter._y = (_a->pos2._y+_b->pos2._y+_c->pos2._y);
	triangleCenter._z = (_a->pos2._z+_b->pos2._z+_c->pos2._z);

	_visible = CVector::Angle(triangleCenter,n2)>0;
}
