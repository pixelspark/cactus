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


#ifndef __CACTUS_CCAMERA_H
#define __CACTUS_CCAMERA_H

/** This class defines a Camera in 3D space.  
@remarks
	To render the view of a camera, you should first create a CCanvas. Then, call CScene::Render(CCanvas*,CCamera*) to
	render to the Canvas what the Camera is seeing.
**/
class CACTUS_API CCamera {
	public:
		// constructors/destructor
		CCamera();
		CCamera(float fov);
		virtual ~CCamera();
		
		// data members
		CMatrix matrix;
		CMatrix normalmatrix;
		CVector pos;
		CVector lookat;
		float roll;
		float fovfact;
		float _fov;
		int screenwidth;
		int screenheight;
		int screenscale;

		// methods
		CMatrix* GetMatrix();
		CMatrix* GetNormalMatrix();
		void RebuildMatrices();
		void SetFov(float fov);
		float GetFov();
		void Roll(float angle);
		void SetPos(float px,float py,float pz);
		void SetPos(CVector p);
		void LookAt(float px,float py,float pz);
		void LookAt(CVector p);
		void SetScreenSize(int w,int h);
		void Shift(float dx,float dy,float dz);
		void Shift(CVector v);
		void Rotate(float dx,float dy,float dz);
		void Rotate(CVector v);
		CVector GetPos() {
			return pos;
		}
		
		static CCamera Front() {
			CCamera cam;
			cam.SetPos(0,0,-2);
			return cam;
		}

		static CCamera Left() {
			CCamera cam;
			cam.SetPos(-2,0,0);
			return cam;
		}

		static CCamera Right() {
			CCamera cam;
			cam.SetPos(2,0,0);
			return cam;
		}

		static CCamera Top() {
			CCamera cam;
			cam.SetPos(0,-2,0);
			return cam;
		}
	private:
		bool needsRebuild;
};

#endif