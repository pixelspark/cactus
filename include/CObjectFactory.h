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


#ifndef __CACTUS_COBJECTFACTORY_H
#define __CACTUS_COBJECTFACTORY_H

// ---------------------------------------------------------------------------------------------------------------------------------------------------
// This class can generate various common objects and primitives, like a cube, sphere, torusknot and a lot more.
// ---------------------------------------------------------------------------------------------------------------------------------------------------
class CACTUS_API CObjectFactory {
	public:
		CObjectFactory() {
		}
		virtual ~CObjectFactory() {
		}
		CObject* Cube(float xsize, float ysize, float zsize);
		CObject* HeightField(float* data, int mapWidth, int mapHeight, float height, bool doubleSided);
		CObject* RotationObject(CVector* path, int numpath, int sides);
		CObject* Field3D(int resolution, float height);
		CObject* Cone(float height, float radius, int segments);
		CObject* Tube(CVector* path, int segments, float r, int steps, bool closed);
		CObject* TorusKnot(float p, float q,  float r_tube, float r_out, float r_in, float h, int segments, int steps);
		CObject* Sphere(float radius, int segments);
		CObject* Spiral(float h, float r_out,  float r_in, float r_tube, float w, float f, int segments, int steps);
};

#endif