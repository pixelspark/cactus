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

// ---------------------------------------------------------------------------------------------------------------------------------------------------
// Constructors.
// ---------------------------------------------------------------------------------------------------------------------------------------------------
CVector::CVector(float x, float y, float z) {
	_z = z;
	_x = x;
	_y = y;
}

CVector::CVector() {
	_x = 0;
	_y = 0;
	_z = 0;
}

CVector::CVector(const CVector* other) {
	_x = other->_x;
	_y = other->_y;
	_z = other->_z;
}

void CVector::Normalize() {
	float invdist = 1/GetLength();
	_x *= invdist;
	_y *= invdist;
	_z *= invdist;
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------
// Pythagoras-like method for calculation this vector's length.
// ---------------------------------------------------------------------------------------------------------------------------------------------------
float CVector::GetLength() {
	return (float)sqrt(_x*_x+_y*_y+_z*_z);
}

void CVector::Reverse() {
	_x = -_x;
	_y = -_y;
	_z = -_z;
}


void CVector::Scale(float f) {
	_x *= f;
	_y *= f;
	_z *= f;
}

CVector CVector::Transform(CMatrix m) {
	float newx = _x*m.m00 + _y*m.m01 + _z*m.m02 + m.m03;
	float newy = _x*m.m10 + _y*m.m11 + _z*m.m12 + m.m13;
	float newz = _x*m.m20 + _y*m.m21 + _z*m.m22 + m.m23;

	return CVector(newx,newy,newz);
}

CVector CVector::Transform(CMatrix* m) {
	float newx = _x*m->m00 + _y*m->m01 + _z*m->m02 + m->m03;
	float newy = _x*m->m10 + _y*m->m11 + _z*m->m12 + m->m13;
	float newz = _x*m->m20 + _y*m->m21 + _z*m->m22 + m->m23;

	return CVector(newx,newy,newz);
}

CVector CVector::Clone() {
	return CVector(this);
}

void CVector::Clone(CVector& target) const {
	target = CVector(this);
}