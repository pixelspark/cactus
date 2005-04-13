/** PORT STATUS: almost done, at least i guess so :-) maybe we have to change some instances to be
pointers. **/

#ifndef __DDENGINE_COREOBJECT_H
#define __DDENGINE_COREOBJECT_H

#include "Matrix.h"
#include "Vector.h"

class CoreObject {
	protected:
		CoreObject();
		virtual ~CoreObject();
	public:
		Matrix matrix;
		Matrix normalmatrix;

		virtual void Transform(Matrix m);
		virtual void Shift(float dx,float dy,float dz);
		virtual void Shift(Vector v);
		virtual void Scale(float d);
		virtual void Scale(float dx,float dy,float dz);
		virtual void ScaleSelf(float d);
		virtual void ScaleSelf(float dx,float dy,float dz);
		virtual void Rotate(Vector d);
		virtual void RotateSelf(Vector d);
		virtual void Rotate(float dx,float dy,float dz);
		virtual void RotateSelf(float dx,float dy,float dz);
		virtual void SetPos(float x,float y,float z);
		virtual void SetPos(Vector v);
		virtual Vector GetPos();

};

#endif
