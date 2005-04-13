#ifndef __DDENGINE_MATRIX_H
#define __DDENGINE_MATRIX_H

#include "Vector.h"
#include "Math.h"

class Matrix {
	public:
		// constructors
		Matrix();
		Matrix(Vector right,Vector up,Vector forward);
		virtual ~Matrix();
		
		// data members
		float m00,m01,m02,m03;
		float m10,m11,m12,m13;
		float m20,m21,m22,m23;
		float m30,m31,m32,m33;

		// methods
		static Matrix shiftMatrix(float dx,float dy,float dz) {
			Matrix m;
			m.m03 = dx;
			m.m13 = dy;
			m.m23 = dz;

			return m;
		}

		static Matrix scaleMatrix(float dx,float dy,float dz) {
			Matrix m;
			m.m00 = dx;
			m.m11 = dy;
			m.m22 = dz;
			return m;
		}

		static Matrix scaleMatrix(float d) {
			return scaleMatrix(d,d,d);
		}

		static Matrix rotateMatrix(float dx,float dy,float dz) {
			Matrix out;
			float fSin;
			float fCos;

			if(dx!=0) {
				Matrix m;
				fSin = (float)sin(dx);
				fCos = (float)cos(dx);
				m.m11 = fCos;
				m.m12 = fSin;
				m.m21 = fSin;
				m.m22 = fCos;
				out.transform(m);
			}

			if(dy!=0) {
				Matrix m;
				fSin = (float)sin(dy);
				fCos = (float)cos(dy);
				m.m00 = fCos;
				m.m02 = fSin;
				m.m20 = fSin;
				m.m22 = fCos;
				out.transform(m);
			}

			if(dz!=0) {
				Matrix m;
				fSin = (float)sin(dz);
				fCos = (float)cos(dz);
				m.m00 = fCos;
				m.m01 = fSin;
				m.m10 = fSin;
				m.m10 = fCos;
				out.transform(m);
			}

			return out;
		}
		
		void shift(float dx,float dy,float dz);
		void scale(float dx,float dy,float dz);
		void scale(float d);
		void rotate(float dx,float dy,float dz);
		void scaleSelf(float d);
		void scaleSelf(float dx,float dy,float dz);
		void rotateSelf(float dx,float dy,float dz);
		void transform(Matrix m);
		void preTransform(Matrix m);
		
		static Matrix multiply(Matrix m1,Matrix m2) {
			Matrix m;
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

		Matrix GetClone();
		Matrix inverse();
		void Reset();
		///void importFromArray(float[][] data);
};

#endif
