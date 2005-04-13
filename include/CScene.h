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

#ifndef __CACTUS_CSCENE_H
#define __CACTUS_CSCENE_H

class CACTUS_API CScene {
	friend class CRenderer;
	friend class CLightmap;
	public:
		CScene();
		virtual ~CScene();
		void AddObject(CObject* ob);
		void AddLight(CLight* light);
		void Clear();
		void Prepare();
		void Rebuild();
		CObject* At(int index);

		// COREOBJECT
		void Transform(CMatrix& mat);
		void Shift(float dx, float dy, float dz);
		void Shift(CVector& v);
		void Scale(float d);
		void Scale(float sx, float sy, float sz);
		void ScaleSelf(float d);
		void ScaleSelf(float sx, float sy, float sz);
		void Rotate(CVector& d);
		void RotateSelf(CVector& d);
		void Rotate(float dx, float dy, float dz);
		void RotateSelf(float dx, float dy, float dz);
		CVector GetPos();
		void SetPos(float x, float y, float z);
		void SetPos(CVector& p);
		CRenderer* GetRenderer();

		inline void Render(CCanvas* screen, CCamera* cam) {
			_renderer.SetScene(this);
			_renderer.Render(screen, cam);
		}

		int CountObjects() {
			return _objects.GetCount();
		}

		int CountVertices() {
			_objects.Restart();
			CObject* cur;
			int count = 0;

			while(_objects.HasNext()) {
				cur = *_objects.Next();
				count += cur->CountVertices();
			}

			return count;
		}

		void SetAllMaterialMode(int mode) {
			_objects.Restart();
			CObject* cur;

			while(_objects.HasNext()) {
				cur = _objects.NextStack();
				cur->GetMaterial()->SetMode(mode);
			}
		}

		void EnableAllMaterialMode(int mode) {
			_objects.Restart();
			CObject* cur;

			while(_objects.HasNext()) {
				cur = _objects.NextStack();
				cur->GetMaterial()->EnableMode(mode);
			}
		}

		void ToggleAllMaterialMode(int mode) {
			_objects.Restart();
			CObject* cur;

			while(_objects.HasNext()) {
				cur = _objects.NextStack();
				cur->GetMaterial()->ToggleMode(mode);
			}
		}

		void DisableAllMaterialMode(int mode) {
			_objects.Restart();
			CObject* cur;

			while(_objects.HasNext()) {
				cur = _objects.NextStack();
				cur->GetMaterial()->DisableMode(mode);
			}
		}

		int CountTriangles() {
			_objects.Restart();
			CObject* cur;
			int count = 0;

			while(_objects.HasNext()) {
				cur = *_objects.Next();
				count += cur->CountTriangles();
			}

			return count;
		}

		CColor GetBackgroundColor() {
			return _backgroundColor;
		}

		void SetBackgroundColor(CColor s) {
			_backgroundColor = s;
		}

		void SetSize(int h, int w) {
			assert(h>0);
			assert(w>0);

			_height = h;
			_width = w;
		}

		inline int GetHeight() {
			return _height;
		}

		inline int GetWidth() {
			return _width;
		}
	private:
		// CRenderer _renderer;
		CLinkedList<CObject*> _objects;
		CLinkedList<CLight*> _lights;
		int _width;
		int _height;
		CColor _backgroundColor;
		bool _readyForRendering;
		bool _needsRebuild;
		bool _lightNeedsRebuild;
		CMatrix _matrix;
		CMatrix _normalMatrix;
		CRenderer _renderer;
};


#endif