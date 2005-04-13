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

CSpline::CSpline() {
	// set up matrix (Hermite polynomial)
	_coeffs.m00 = 2.0f;
	_coeffs.m01 = -2.0f;
	_coeffs.m02 = 1.0f;
	_coeffs.m03 = 1.0f;

	_coeffs.m10 = -3.0f;
	_coeffs.m11 = 3.0f;
	_coeffs.m12 = -2.0f;
	_coeffs.m13 = -1.0f;

	_coeffs.m20 = 0.0f;
	_coeffs.m21 = 0.0f;
	_coeffs.m22 = 1.0f;
	_coeffs.m23 = 0.0f;

	_coeffs.m30 = 1.0f;
	_coeffs.m31 = 0.0f;
	_coeffs.m32 = 0.0f;
	_coeffs.m33 = 0.0f;

	_autoCalculate = true;
}

CSpline::~CSpline() {
}

void CSpline::AddPoint(const CVector& p) {
	_points.push_back(p);
	if(_autoCalculate) {
		RecalculateTangents();
	}
}

CVector CSpline::Interpolate(float t) {
	// Currently assumes points are evenly spaced, will cause velocity change where this is not the case
	float seg = t * _points.size();
	unsigned int segIndex = (unsigned int)seg;
	t = seg - segIndex;
	return Interpolate(segIndex,t);
}

CVector CSpline::Interpolate(unsigned int fromIndex,float t) {
	assert(fromIndex>=0 && fromIndex<_points.size());

	if((fromIndex+1)==_points.size()) {
		return _points[fromIndex];
	}

	if(t==0.0f) {
		return _points[fromIndex];
	}

	if(t==1.0f) {
		return _points[fromIndex+1];
	}

	float t2,t3;
	t2 = t*t;
	t3 = t2*t;
	// Vector4 powers(t3,t2,t,1);
	CVector powers(t3,t2,t);

	CVector& point1 = _points[fromIndex];
	CVector& point2 = _points[fromIndex+1];
	CVector& tan1 = _tangents[fromIndex];
	CVector& tan2 = _tangents[fromIndex+1];

	CMatrix pt;
	pt.m00 = point1._x;
	pt.m01 = point1._y;
	pt.m02 = point1._z;
	pt.m03 = 1.0f;
	
	pt.m10 = point2._x;
	pt.m11 = point2._y;
	pt.m12 = point2._z;
	pt.m13 = 1.0f;

	pt.m20 = tan1._x;
	pt.m21 = tan1._y;
	pt.m22 = tan1._z;
	pt.m23 = 1.0f;

	pt.m30 = tan2._x;
	pt.m31 = tan2._y;
	pt.m32 = tan2._z;
	pt.m33 = 1.0f;

	CVector ret = powers.Transform(_coeffs).Transform(pt); 
	return ret;
}

void CSpline::RecalculateTangents() {
	unsigned int numPoints;
	bool isClosed;

	numPoints = (unsigned int)_points.size();
	if(numPoints<2) {
		return;
	}

	if(_points[0] == _points[numPoints-1]) {
		isClosed = true;
	}
	else {
		isClosed = false;
	}

	_tangents.resize(numPoints);

	for(unsigned int ix=0;ix<numPoints;ix++) {
		if(ix==0) {
			if(isClosed) {
				_tangents[ix] = CVector::Subtract(_points[1],_points[numPoints-2]);
				_tangents[ix].Scale(0.5f);
			}
			else {
				_tangents[ix] = CVector::Subtract(_points[1], _points[0]);
				_tangents[ix].Scale(0.5f);
			}
		}
		else if(ix == (numPoints-1)) {
			if(isClosed) {
				_tangents[ix] = _tangents[0];
			}
			else {
				_tangents[ix] = CVector::Subtract(_points[ix],_points[ix-1]);
				_tangents[ix].Scale(0.5f);
			}
		}
		else {
			_tangents[ix] = CVector::Subtract(_points[ix+1],_points[ix-1]);
			_tangents[ix].Scale(0.5f);
		}
	}
}

const CVector& CSpline::GetPoint(unsigned short index) const {
	assert(index<_points.size());

	return _points[index];
}

unsigned short CSpline::CountPoints() const {
	return (unsigned short)_points.size();
}

void CSpline::Clear() {
	_points.clear();
	_tangents.clear();
}

void CSpline::UpdatePoint(unsigned short index, const CVector &value) {
	assert(index<_points.size());

	_points[index] = value;
	if(_autoCalculate) {
		RecalculateTangents();
	}
}

void CSpline::SetAutoCalculate(bool a) {
	_autoCalculate = a;
}