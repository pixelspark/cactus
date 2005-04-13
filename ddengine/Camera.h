#ifndef __DDENGINE_CAMERA_H
#define __DDENGINE_CAMERA_H

class Camera;
#include "Matrix.h"
#include "Vector.h"
#include "Math.h"

class Matrix;
class Math;
class Vector;

class Camera {
	public:
		// constructors/destructor
		Camera();
		Camera(float fov);
		virtual ~Camera();
		
		// data members
		Matrix matrix;
		Matrix normalmatrix;
		Vector pos;
		Vector lookat;
		float roll;
		float fovfact;
		int screenwidth;
		int screenheight;
		int screenscale;

		// methods
		Matrix GetMatrix();
		Matrix GetNormalMatrix();
		void RebuildMatrices();
		void SetFov(float fov);
		void Roll(float angle);
		void SetPos(float px,float py,float pz);
		void SetPos(Vector p);
		void LookAt(float px,float py,float pz);
		void LookAt(Vector p);
		void SetScreenSize(int w,int h);
		void Shift(float dx,float dy,float dz);
		void Shift(Vector v);
		void Rotate(float dx,float dy,float dz);
		void Rotate(Vector v);
		
		static Camera Front() {
			Camera cam;
			cam.SetPos(0,0,-2);
			return cam;
		}

		static Camera Left() {
			Camera cam;
			cam.SetPos(-2,0,0);
			return cam;
		}

		static Camera Right() {
			Camera cam;
			cam.SetPos(2,0,0);
			return cam;
		}

		static Camera Top() {
			Camera cam;
			cam.SetPos(0,-2,0);
			return cam;
		}
	private:
		bool needsRebuild;

};

#endif
