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


// ---------------------------------------------------------------------------------------------------------------------------------------------------
// This file contains implementations for methods of class CMatrix.
// ---------------------------------------------------------------------------------------------------------------------------------------------------
#include "../include/cactus.h"
using namespace cactus;

CMatrix::CMatrix(CVector right, CVector up, CVector forward) {
	Reset();

	m00 = right._x;
	m10 = right._y;
	m20 = right._z;

	m01 = up._x;
	m11 = up._y;
	m21 = up._z;

	m02 = forward._x;
	m12 = forward._y;
	m22 = forward._z;
}

CMatrix::CMatrix() {
	Reset();
}


void CMatrix::Reset() {
		m01 = m02 = m03 = 0;
		m10 = m12 = m13 = 0;
		m20 = m21  = m23 = 0;
		m30 = m31 = m32 = 0;
		m00 = m11 = m22 = m33 = 1;
}

void CMatrix::Transform(const CMatrix& n) {
	CMatrix m = Clone();
	m00 = n.m00*m.m00 + n.m01*m.m10 + n.m02*m.m20;
	m01 = n.m00*m.m01 + n.m01*m.m11 + n.m02*m.m21;
	m02 = n.m00*m.m02 + n.m01*m.m12 + n.m02*m.m22;
	m03 = n.m00*m.m03 + n.m01*m.m13 + n.m02*m.m23 + n.m03;
	m10 = n.m10*m.m00 + n.m11*m.m10 + n.m12*m.m20;
	m11 = n.m10*m.m01 + n.m11*m.m11 + n.m12*m.m21;
	m12 = n.m10*m.m02 + n.m11*m.m12 + n.m12*m.m22;
	m13 = n.m10*m.m03 + n.m11*m.m13 + n.m12*m.m23 + n.m13;
	m20 = n.m20*m.m00 + n.m21*m.m10 + n.m22*m.m20;
	m21 = n.m20*m.m01 + n.m21*m.m11 + n.m22*m.m21;
	m22 = n.m20*m.m02 + n.m21*m.m12 + n.m22*m.m22;
	m23 = n.m20*m.m03 + n.m21*m.m13 + n.m22*m.m23 + n.m23;	
}

void CMatrix::Transform(const CMatrix* n) {
	CMatrix mm = Clone();
	CMatrix* m  = &mm;

	m00 = n->m00*m->m00 + n->m01*m->m10 + n->m02*m->m20;
	m01 = n->m00*m->m01 + n->m01*m->m11 + n->m02*m->m21;
	m02 = n->m00*m->m02 + n->m01*m->m12 + n->m02*m->m22;
	m03 = n->m00*m->m03 + n->m01*m->m13 + n->m02*m->m23 + n->m03;
	m10 = n->m10*m->m00 + n->m11*m->m10 + n->m12*m->m20;
	m11 = n->m10*m->m01 + n->m11*m->m11 + n->m12*m->m21;
	m12 = n->m10*m->m02 + n->m11*m->m12 + n->m12*m->m22;
	m13 = n->m10*m->m03 + n->m11*m->m13 + n->m12*m->m23 + n->m13;
	m20 = n->m20*m->m00 + n->m21*m->m10 + n->m22*m->m20;
	m21 = n->m20*m->m01 + n->m21*m->m11 + n->m22*m->m21;
	m22 = n->m20*m->m02 + n->m21*m->m12 + n->m22*m->m22;
	m23 = n->m20*m->m03 + n->m21*m->m13 + n->m22*m->m23 + n->m23;	
}


CMatrix CMatrix::Clone() {
	CMatrix m;
	m.m00=m00;  m.m01=m01;  m.m02=m02;  m.m03=m03;
	m.m10=m10;  m.m11=m11;  m.m12=m12;  m.m13=m13;
	m.m20=m20;  m.m21=m21;  m.m22=m22;  m.m23=m23;
	m.m30=m30;  m.m31=m31;  m.m32=m32;  m.m33=m33;
	
	return m;
}

// Faster version of the clone-method above. Avoids creation of temporary objects.
void CMatrix::Clone(CMatrix& m) {
	m.m00=m00;  m.m01=m01;  m.m02=m02;  m.m03=m03;
	m.m10=m10;  m.m11=m11;  m.m12=m12;  m.m13=m13;
	m.m20=m20;  m.m21=m21;  m.m22=m22;  m.m23=m23;
	m.m30=m30;  m.m31=m31;  m.m32=m32;  m.m33=m33;
}

CMatrix CMatrix::Inverse() {
	CMatrix m;
	
	float q1 = m12;  float q6 = m10*m01;  float q7 = m10*m21;  float q8 = m02;  
	float q13 = m20*m01;  float q14 = m20*m11;  float q21 = m02*m21;  float q22 = m03*m21;  
	float q25 = m01*m12;  float q26 = m01*m13;  float q27 = m02*m11;  float q28 = m03*m11;  
	float q29 = m10*m22;  float q30 = m10*m23;  float q31 = m20*m12;  float q32 = m20*m13;  
	float q35 = m00*m22;  float q36 = m00*m23;  float q37 = m20*m02;  float q38 = m20*m03;  
	float q41 = m00*m12;  float q42 = m00*m13;  float q43 = m10*m02;  float q44 = m10*m03;  
	float q45 = m00*m11;  float q48 = m00*m21;  
	float q49 = q45*m22-q48*q1-q6*m22+q7*q8;
	float q50 = q13*q1-q14*q8;
	float q51 = 1/(q49+q50);
		
	m.m00 = (m11*m22*m33-m11*m23*m32-m21*m12*m33+m21*m13*m32+m31*m12*m23-m31*m13*m22)*q51;
	m.m01 = -(m01*m22*m33-m01*m23*m32-q21*m33+q22*m32)*q51;
	m.m02 = (q25*m33-q26*m32-q27*m33+q28*m32)*q51;
	m.m03 = -(q25*m23-q26*m22-q27*m23+q28*m22+q21*m13-q22*m12)*q51;
	m.m10 = -(q29*m33-q30*m32-q31*m33+q32*m32)*q51;
	m.m11 = (q35*m33-q36*m32-q37*m33+q38*m32)*q51;
	m.m12 = -(q41*m33-q42*m32-q43*m33+q44*m32)*q51;
	m.m13 = (q41*m23-q42*m22-q43*m23+q44*m22+q37*m13-q38*m12)*q51;
	m.m20 = (q7*m33-q30*m31-q14*m33+q32*m31)*q51;
	m.m21 = -(q48*m33-q36*m31-q13*m33+q38*m31)*q51;
	m.m22 = (q45*m33-q42*m31-q6*m33+q44*m31)*q51;
	m.m23 = -(q45*m23-q42*m21-q6*m23+q44*m21+q13*m13-q38*m11)*q51;

	return m;
}

void CMatrix::PreTransform(CMatrix n) {
	CMatrix m = Clone();
	m00 = m.m00*n.m00 + m.m01*n.m10 + m.m02*n.m20;
	m01 = m.m00*n.m01 + m.m01*n.m11 + m.m02*n.m21;
	m02 = m.m00*n.m02 + m.m01*n.m12 + m.m02*n.m22;
	m03 = m.m00*n.m03 + m.m01*n.m13 + m.m02*n.m23 + m.m03;
	m10 = m.m10*n.m00 + m.m11*n.m10 + m.m12*n.m20;
	m11 = m.m10*n.m01 + m.m11*n.m11 + m.m12*n.m21;
	m12 = m.m10*n.m02 + m.m11*n.m12 + m.m12*n.m22;
	m13 = m.m10*n.m03 + m.m11*n.m13 + m.m12*n.m23 + m.m13;
	m20 = m.m20*n.m00 + m.m21*n.m10 + m.m22*n.m20;
	m21 = m.m20*n.m01 + m.m21*n.m11 + m.m22*n.m21;
	m22 = m.m20*n.m02 + m.m21*n.m12 + m.m22*n.m22;
	m23 = m.m20*n.m03 + m.m21*n.m13 + m.m22*n.m23 + m.m23;	
}

void CMatrix::RotateSelf(float dx,float dy,float dz) {
	PreTransform(RotateMatrix(dx,dy,dz));
}

void CMatrix::Rotate(float dx,float dy,float dz) {
	Transform(RotateMatrix(dx,dy,dz));
}

void CMatrix::Scale(float d) {
	Transform(ScaleMatrix(d));
}

void CMatrix::Scale(float dx,float dy,float dz) {
	Transform(ScaleMatrix(dx,dy,dz));
}

void CMatrix::ScaleSelf(float dx,float dy,float dz) {
	PreTransform(ScaleMatrix(dx,dy,dz));
}

void CMatrix::ScaleSelf(float d) {
	PreTransform(ScaleMatrix(d));
}

void CMatrix::Shift(float dx,float dy,float dz) {
	Transform(ShiftMatrix(dx,dy,dz));
}
