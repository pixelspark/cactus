#ifndef __DDENGINE_VECTOR_H
#define __DDENGINE_VECTOR_H

#include "Matrix.h"
#include "Math.h"

class Matrix;

class Vector {
	public:
		// constructors
		Vector();
		Vector(float xpos,float ypos,float zpos);
		virtual ~Vector();


		// data members
		float x;
		float y;
		float z;
		float r;
		float theta;

		// methods
		Vector Normalize();
		Vector Reverse();
		float Length();
		Vector Transform(Matrix m);
		void BuildCylindric();
		void BuildCarthesian();
		Vector Clone();

		
		static Vector Vector::GetNormal(Vector a,Vector b) {
			return vectorProduct(a,b).Normalize();
		}

		static Vector Vector::GetNormal(Vector a,Vector b,Vector c) {
			return vectorProduct(a,b,c).Normalize();
		}

		static Vector Vector::vectorProduct(Vector a,Vector b) {
			return Vector(a.y*b.z-b.y*a.z,a.z*b.x-b.z*a.x,a.x*b.y-b.x*a.y);
		}

		static Vector Vector::vectorProduct(Vector a,Vector b,Vector c) {
			return vectorProduct(sub(b,a),sub(c,a));
		}

		static float Vector::angle(Vector a,Vector b) {
			a.Normalize();
			b.Normalize();

			return a.x*b.x+a.y*b.y+a.z*b.z;
		}

		static Vector Vector::add(Vector a,Vector b) {
			return Vector(a.x+b.x,a.y+b.y,a.z+b.z);
		}

		static Vector Vector::sub(Vector a,Vector b) {
			return Vector(a.x-b.x,a.y-b.y,b.x-b.y);
		}

		static Vector Vector::scale(float f,Vector a) {
			return Vector(f*a.x,f*a.y,f*a.z);
		}

		static float Vector::len(Vector a) {
			return (float)sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
		}

		static Vector Vector::random(float fact) {
			// not yet implemented
			return Vector(0,0,0);
		}
};
#endif
