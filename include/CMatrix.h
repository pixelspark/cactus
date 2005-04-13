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


#ifndef __CACTUS_CMATRIX_H
#define __CACTUS_CMATRIX_H

class CACTUS_API CMatrix {
	public:
		CMatrix();
		CMatrix(CVector right, CVector up, CVector forward);
		void Reset();
		void Transform(CMatrix& m);
		void Transform(CMatrix* m);
		CMatrix Clone();
		void Clone(CMatrix& m);
		CMatrix Inverse();
		void PreTransform(CMatrix m);

		void Shift(float dx,float dy,float dz);
		void Scale(float dx,float dy,float dz);
		void Scale(float d);
		void Rotate(float dx,float dy,float dz);
		void ScaleSelf(float d);
		void ScaleSelf(float dx,float dy,float dz);
		void RotateSelf(float dx,float dy,float dz);

		float m00,m01,m02,m03;
		float m10,m11,m12,m13;
		float m20,m21,m22,m23;
		float m30,m31,m32,m33;

		// Several methods for generating matrices
		static CMatrix ShiftMatrix(float dx,float dy,float dz) {
			CMatrix m;
			m.m03 = dx;
			m.m13 = dy;
			m.m23 = dz;

			return m;
		}

		static CMatrix ScaleMatrix(float dx,float dy,float dz) {
			CMatrix m;
			m.m00 = dx;
			m.m11 = dy;
			m.m22 = dz;
			return m;
		}

		static CMatrix ScaleMatrix(float d) {
			return ScaleMatrix(d,d,d);
		}

		static CMatrix RotateMatrix(float dx,float dy,float dz) {
			CMatrix out;
			float fSin;
			float fCos;

			if(dx!=0) {
				CMatrix m;
				fSin = (float)math.sin(dx);
				fCos = (float)math.cos(dx);
				m.m11 = fCos;
				m.m12 = fSin;
				m.m21 = -fSin;
				m.m22 = fCos;
				out.Transform(m);
			}

			if(dy!=0) {
				CMatrix m;
				fSin = (float)math.sin(dy);
				fCos = (float)math.cos(dy);
				m.m00 = fCos;
				m.m02 = fSin;
				m.m20 = -fSin;
				m.m22 = fCos;
				out.Transform(m);
			}

			if(dz!=0) {
				CMatrix m;
				fSin = (float)math.sin(dz);
				fCos = (float)math.cos(dz);
				m.m00 = fCos;
				m.m01 = fSin;
				m.m10 = -fSin;
				m.m11 = fCos;
				out.Transform(m);
			}

			return out;
		}

		// Multiplies a matrix. Code copied from Peter Walser's engine as described on top of this file
		static inline CMatrix Multiply(CMatrix m1,CMatrix m2) {
			CMatrix m;
			m.m00 = m1.m00*m2.m00 + m1.m01*m2.m10 + m1.m02*m2.m20;
			m.m01 = m1.m00*m2.m01 + m1.m01*m2.m11 + m1.m02*m2.m21;
			m.m02 = m1.m00*m2.m02 + m1.m01*m2.m12 + m1.m02*m2.m22;
			m.m03 = m1.m00*m2.m03 + m1.m01*m2.m13 + m1.m02*m2.m23 + m1.m03;
			m.m10 = m1.m10*m2.m00 + m1.m11*m2.m10 + m1.m12*m2.m20;
			m.m11 = m1.m10*m2.m01 + m1.m11*m2.m11 + m1.m12*m2.m21;
			m.m12 = m1.m10*m2.m02 + m1.m11*m2.m12 + m1.m12*m2.m22;
			m.m13 = m1.m10*m2.m03 + m1.m11*m2.m13 + m1.m12*m2.m23 + m1.m13;
			m.m20 = m1.m20*m2.m00 + m1.m21*m2.m10 + m1.m22*m2.m20;
			m.m21 = m1.m20*m2.m01 + m1.m21*m2.m11 + m1.m22*m2.m21;
			m.m22 = m1.m20*m2.m02 + m1.m21*m2.m12 + m1.m22*m2.m22;
			m.m23 = m1.m20*m2.m03 + m1.m21*m2.m13 + m1.m22*m2.m23 + m1.m23;
			return m;
		}

		static inline CMatrix FromArray(float** array) {
			CMatrix m;
			m.m00 = array[0][0];
			m.m01 = array[0][1];
			m.m02 = array[0][2];
			m.m03 = array[0][3];

			m.m10 = array[1][0];
			m.m11 = array[1][1];
			m.m12 = array[1][2];
			m.m13 = array[1][3];

			m.m20 = array[2][0];
			m.m21 = array[2][1];
			m.m22 = array[2][2];
			m.m23 = array[2][3];

			m.m30 = array[3][0];
			m.m31 = array[3][1];
			m.m32 = array[3][2];
			m.m33 = array[3][3];

			return m;
		}
};

#endif