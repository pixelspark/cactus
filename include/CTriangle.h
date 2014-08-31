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


#ifndef __CACTUS_CTRIANGLE_H
#define __CACTUS_CTRIANGLE_H

class CACTUS_API CTriangle {
	friend class CRasterizer;
	friend class CRenderer;
	friend class CVertex;
	public:
		CTriangle(CVertex* a, CVertex* b, CVertex* c) {
			_a = a;
			_b = b;
			_c = c;

			_visible = true;
			outOfFrustum = false;
			_parent = 0;
		}

		CTriangle() {
			_a = 0;
			_b = 0;
			_c = 0;
			_visible = false;
			outOfFrustum = false;
			_parent = 0;
		}

		CTriangle(CTriangle& a) {
			_a = a._a;
			_b = a._b;
			_c = a._c;

			_visible = a._visible;
			outOfFrustum = a.outOfFrustum;
			_parent = a._parent;
		}

		/*virtual ~CTriangle() {
			_parent = 0;
			_a = 0;
			_b = 0;
			_c = 0;
		}*/

		void SetVisible(bool v) {
			_visible = v;
		}

		void SetParent(CObject* parent) {
			_parent = parent;
		}

		inline CObject* GetParent() {
			return _parent;
		}

		bool GetVisible() {
			return _visible;
		}

		inline CVertex* GetVertexA() {
			return _a;
		}

		inline CVertex* GetVertexB() {
			return _b;
		}

		inline CVertex* GetVertexC() {
			return _c;
		}

		inline float GetDistance() {
			return (float)(_a->_z+_b->_z+_c->_z);
		}

		inline void Project(CMatrix normalProjection) {
			n2 = n.Transform(normalProjection);
			dist=GetDistance();
		}

		void RegenerateNormal();
		void ClipFrustum(int w,int h);
		CVector GetWeightedNormal();
		CVertex GetMedium();
		CVector GetCenter();

		CVertex* _a;
		CVertex* _b;
		CVertex* _c;
	private:
		bool _visible;
		bool outOfFrustum;
		CVector n;
		CVector n2;
		int minx,maxx,miny,maxy;
		CVector triangleCenter;
		float dist;
		CObject* _parent;
};

#endif