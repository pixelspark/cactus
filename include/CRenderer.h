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


#ifndef __CACTUS_CRENDERER_H
#define __CACTUS_CRENDERER_H

class CACTUS_API CRenderer {
	friend class CRasterizer;

	public:
		CRenderer(CScene* sc);
		CRenderer();
		virtual ~CRenderer();
		void Render(CCanvas* can, CCamera* cam);
		void SetScene(CScene* sc);
		CScene* GetScene();
		void ClearQueue();
		void EnqueueTriangle(CTriangle* tr);
		CLinkedList<CTriangle*> GetTriangleQueue();
		CRasterizer* GetRasterizer();
		void SetMode(int rasterizerMode);
		int GetMode();

		void SetPopulateIDBuffer(bool pid);
		bool GetPopulateIDBuffer();
		CTriangle* GetTriangleAt(int x, int y);

		// coreobject methods
		void Transform(CMatrix& m);
		void Shift(float dx, float dy, float dz);
		void Shift(CVector& v);
		void Scale(float d);
		void Scale(float sx, float sy, float sz);
		void ScaleSelf(float d);
		void ScaleSelf(float x, float y, float z);
		void Rotate(CVector& r);
		void RotateSelf(CVector& r);
		void Rotate(float dx, float dy, float dz);
		void RotateSelf(float dx, float dy, float dz);
		void SetPos(float x, float y, float z);
		void SetPos(CVector& p);
		void BuildLightmap();
		CVector GetPos();

	protected:
		CScene* _scene;
		CBuffer<float> _zbuffer;
		CLinkedList<CTriangle*> _triangleQueue;
		CMatrix _matrix;
		CMatrix _normalMatrix;
		CRasterizer _rasterizer;
		CLightmap _lightmap;
		bool _zbufferNegative;
		bool _populateIDBuffer;
		CTriangle** _IDBuffer;
};

#endif