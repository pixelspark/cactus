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


#ifndef __CACTUS_COBJECT_H
#define __CACTUS_COBJECT_H

/** This class represents an object in 3d space. Most 3D programmers call it a mesh, we call it an object. **/
class CACTUS_API CObject {
	friend class CRenderer;
	public:
		CObject();
		virtual ~CObject();
		void SetPos(float x, float y, float z);
		void SetPos(CVector& pos);
		void AddTriangle(CTriangle* tr);
		void AddTriangle(int a, int b, int c);
		void RemoveDuplicateVertices();
		void RemoveDegeneratedTriangles();
		void SetTriangleParent() {
			_triangles.Restart();
			while(_triangles.HasNext()) {
				_triangles.NextStack()->SetParent(this);
			}
		}
		void GetIndexOf(CVertex* vert) {
			
		}
		void RemoveTriangles();
		void Rebuild();
		void Detach();
		void MatrixMeltdown();
		void Regenerate();
		int CountVertices();
		int CountTriangles();
		CVector Min();
		CVector Max();
		CVector GetCenter();
		CVector GetDimensions();
		void Clone(CObject& obj);

		// CoreObject
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
		inline bool IsVisible() {
			return _visible;
		}

		inline void AddVertex(CVertex* vert) {
			_vertices.push_back(vert);
		}

		inline CMaterial* GetMaterial() {
			return &_material;
		}

		inline CVertex* VertexAt(int x) {
			return _vertices.at(x);
		}

		void SetVisible(bool v);

		CLinkedList<CTriangle*> _triangles;
		std::vector<CVertex*> _vertices;
		CMaterial _material;
		int _id; // this variable can be used to identify an object on the screen using the ID-buffer.
	protected:
		CMatrix _matrix;
		CMatrix _normalMatrix;
		bool _dirty;
		bool _visible;
};


#endif