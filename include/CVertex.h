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


#ifndef __CACTUS_CVERTEX_H
#define __CACTUS_CVERTEX_H

class CACTUS_API CVertex {
	friend class CRasterizer;
	public:
		virtual ~CVertex() {
			_parent = 0;
		}
		CVertex(float x, float y, float z);
		CVertex(float x, float y, float z, float u, float v);
		CVertex(CVector pos);
		CVertex(CVector pos,float u, float v);
		CVertex();
		bool Equals(CVertex v);
		
		inline float GetX() {
			return pos._x;
		}

		inline void SetParent(CObject* tri) {
			_parent = tri;
		}

		inline float GetY() {
			return pos._y;
		}

		inline float GetZ() {
			return pos._z;
		}

		inline float GetU() {
			return _u;
		}

		inline float GetV() {
			return _v;
		}

		inline void SetX(float x) {
			pos._x = x;
		}

		inline void SetY(float y) {
			pos._y = y;
		}

		inline void SetZ(float z) {
			pos._z = z;
		}

		inline void SetU(float u) {
			_u = u;
		}

		inline void SetV(float v) {
			_v = v;
		}

	
		void Project(CMatrix* vertexProjection,CMatrix* normalProjection,CCamera* camera);
		void ResetNeighbours();
		void RegenerateNormal();
		void RegisterNeighbour(CTriangle* t);
		void SetUV(float u,float v);
		void ScaleTextureCoordinates(float fx,float fy);
		void ClipFrustum(int w, int h);
		CVertex Clone() const;
		void Clone(CVertex& target);

		CVector pos;
		CVector pos2;
		CVector n;
		CVector n2;
		friend class CTriangle;

		int _x;
		int _y;
		float _z;
		float _u;
		float _v;
		int nx,ny,tx,ty;
		float fact;
		int clipcode;
		bool visible;
		bool outOfFrustum;
		CLinkedList<CTriangle*> _neighbours;
		int _index;
	protected:
		CObject* _parent;
};

#endif