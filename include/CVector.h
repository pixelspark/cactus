/* ---------------------------------------------------------------------------------------------------------------------------------------------------
Copyright (C) 2003 Tommy van der Vorst

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


#ifndef __CACTUS_CVECTOR_H
#define __CACTUS_CVECTOR_H

// ---------------------------------------------------------------------------------------------------------------------------------------------------
// Vector class. If you don't know what vectors are and what they are used for, consider reading this: 
// http://tfpsly.planet-d.net/Docs/3dIca/3dica1.htm#chap1. It is an excellent tutorial about the mathematics involved in 3D graphics.
// ---------------------------------------------------------------------------------------------------------------------------------------------------
class CACTUS_API CVector {
	public:
		CVector();
		CVector(float x, float y, float z);
		CVector(CVector* other);

		float GetLength();
		void Normalize();
		void Reverse();
		void Scale(float f);
		CVector Clone();
		void Clone(CVector& target);
		inline CVector Transform(CMatrix m);
		inline CVector Transform(CMatrix* m);

		static float Angle(CVector& a, CVector& b) {
			a.Normalize();
			b.Normalize();
			return a._x*b._x+a._y*b._y+a._z*b._z;
		}


		static CVector Add(CVector a, CVector b) {
			return CVector(a._x+b._x,a._y+b._y,a._z+b._z);
		}

 		static CVector Subtract(CVector a, CVector b) {
			return CVector(a._x-b._x,a._y-b._y,a._z-b._z);
		}

		static CVector Scale(float f, CVector v) {
			return CVector(v._x*f,v._y*f,v._z*f);
		}

		static CVector CVector::GetNormal(CVector a,CVector b) {
			CVector ret =  VectorProduct(a,b);
			ret.Normalize();
			return ret;
		}

		static CVector CVector::GetNormal(CVector a,CVector b,CVector c) {
			CVector ret = VectorProduct(a,b,c);
			ret.Normalize();
			return ret;
		}

		static CVector CVector::VectorProduct(CVector a,CVector b) {
			return CVector(a._y*b._z-b._y*a._z,a._z*b._x-b._z*a._x,a._x*b._y-b._x*a._y);
		}

		static CVector CVector::VectorProduct(CVector a,CVector b,CVector c) {
			return VectorProduct(Subtract(b,a),Subtract(c,a));
		}

		bool operator ==(CVector& c) {
			if(c._x==_x&&c._y==_y&&c._z==_z) {
				return true;
			}
			return false;
		}

		float _x;
		float _y;
		float _z;
};


#endif