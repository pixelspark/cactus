/* ---------------------------------------------------------------------------------------------------------------------------------------------------
Copyright (C) 2003-2004 Tommy van der Vorst

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
#include "../include/cactus.h"
using namespace cactus;

CObject::CObject() {
	_dirty = true;
	_visible = true;
	_id = 0;
}

CObject::~CObject() {
	//_dirty = false;
	//_vertices.Empty();
	//_triangles.Empty();
	//_visible = false;
	//_id = 0;
	for(unsigned int a=0;a<_vertices.size();a++) {
		delete _vertices.at(a);
	}

	_triangles.Restart();
	while(_triangles.HasNext()) {
		delete _triangles.Next();
	}
}

void CObject::AddTriangle(CTriangle* tr) {
	_triangles.Add(tr);
	tr->SetParent(this);
	_dirty = true;
}

void CObject::AddTriangle(int a, int b, int c) {
	CTriangle* tr = new CTriangle(_vertices.at(a), _vertices.at(b), _vertices.at(c));
	AddTriangle(tr);
}

void CObject::SetVisible(bool v) {
	_visible = v;
}


int CObject::CountVertices() {
	return (int)_vertices.size();
}

int CObject::CountTriangles() {
	return _triangles.GetCount();
}

void CObject::Clone(CObject &obj) {
	obj._dirty = _dirty;
	obj._matrix = _matrix;
	obj._normalMatrix = _normalMatrix;
	obj._triangles = _triangles;
	obj._vertices = _vertices;
}

CVector CObject::GetPos() {
		return CVector(_matrix.m03,_matrix.m13,_matrix.m23);
}

void CObject::Rebuild() {
	if(!_dirty) {
		return;
	}
	_dirty = false;
	
	for(unsigned int a=0;a<_vertices.size();a++) {
		CVertex* x = _vertices.at(a);
		x->ResetNeighbours();
		x->SetParent(this);
	}

	CTriangle* current;
	
	_triangles.Restart();
	while(_triangles.HasNext()) {
		current = _triangles.NextStack();

		current->_a->RegisterNeighbour(current);
		current->_b->RegisterNeighbour(current);
		current->_c->RegisterNeighbour(current);
	}

	Regenerate();
}

void CObject::Regenerate() {
	_triangles.Restart();
	while(_triangles.HasNext()) {
		CTriangle* t = _triangles.NextStack();
		t->RegenerateNormal();
	}

	for(unsigned int a=0;a<_vertices.size();a++) {
		CVertex* x = _vertices.at(a);
		x->RegenerateNormal();
	}
}

void CObject::RemoveTriangles() {
	_triangles.Empty();
}

void CObject::Rotate(float dx, float dy, float dz) {
	_matrix.Rotate(dx, dy, dz);
	_normalMatrix.Rotate(dx, dy, dz);
}

void CObject::Rotate(CVector& d) {
	Rotate(d._x,d._y,d._z);
}

void CObject::RotateSelf(float dx, float dy, float dz) {
	_matrix.RotateSelf(dx, dy, dz);
	_normalMatrix.RotateSelf(dx, dy, dz);
}

void CObject::RotateSelf(CVector& d) {
	RotateSelf(d._x, d._y, d._z);
}

void CObject::Scale(float sx, float sy, float sz) {
	_matrix.Scale(sx, sy, sz);
}

void CObject::Scale(float d) {
	Scale(d,d,d);
}

void CObject::ScaleSelf(float dx, float dy, float dz) {
	_matrix.ScaleSelf(dx,dy,dz);
}

void CObject::ScaleSelf(float d) {
	ScaleSelf(d,d,d);
}

void CObject::SetPos(CVector& pos) {
	SetPos(pos._x, pos._y, pos._z);
}

void CObject::SetPos(float x, float y, float z) {
	_matrix.m03 = x;
	_matrix.m13 = y;
	_matrix.m23 = z;
}

void CObject::Shift(CVector& v) {
	Shift(v._x, v._y, v._z);
}

void CObject::Shift(float dx, float dy, float dz) {
	_matrix.Shift(dx,dy,dz);
}

void CObject::Transform(CMatrix& mat) {
	_matrix.Transform(mat);
	_normalMatrix.Transform(mat);
}

CVector CObject::Min() {
	CTriangle* cur;
	CVector max;


	_triangles.Restart();
	while(_triangles.HasNext()) {
		cur = _triangles.NextStack();

		if(cur->_a->pos._x<max._x) {
			max._x = cur->_a->pos._x;
		}
		if(cur->_b->pos._x<max._x) {
			max._x = cur->_b->pos._x;
		}
		if(cur->_c->pos._x<max._x) {
			max._x = cur->_c->pos._x;
		}

		if(cur->_a->pos._y<max._y) {
			max._y = cur->_a->pos._y;
		}
		if(cur->_b->pos._y<max._y) {
			max._y = cur->_b->pos._y;
		}
		if(cur->_c->pos._y<max._y) {
			max._y = cur->_c->pos._y;
		}

		if(cur->_a->pos._z<max._z) {
			max._z = cur->_a->pos._z;
		}
		if(cur->_b->pos._z<max._z) {
			max._z = cur->_b->pos._z;
		}
		if(cur->_c->pos._z<max._z) {
			max._z = cur->_c->pos._z;
		}
	}

	return max;
}

void CObject::MatrixMeltdown() {
	Rebuild();
	CVertex* cur;
	
	for(unsigned int a=0;a<_vertices.size();a++) {
		cur = _vertices.at(a);

		cur->pos.Transform(_matrix);
	}

	Regenerate();
	_matrix.Reset();
	_normalMatrix.Reset();
}

CVector CObject::Max() {
		CTriangle* cur;
	CVector max;


	_triangles.Restart();
	while(_triangles.HasNext()) {
		cur = _triangles.NextStack();

		if(cur->_a->pos._x>max._x) {
			max._x = cur->_a->pos._x;
		}
		if(cur->_b->pos._x>max._x) {
			max._x = cur->_b->pos._x;
		}
		if(cur->_c->pos._x>max._x) {
			max._x = cur->_c->pos._x;
		}

		if(cur->_a->pos._y>max._y) {
			max._y = cur->_a->pos._y;
		}
		if(cur->_b->pos._y>max._y) {
			max._y = cur->_b->pos._y;
		}
		if(cur->_c->pos._y>max._y) {
			max._y = cur->_c->pos._y;
		}

		if(cur->_a->pos._z>max._z) {
			max._z = cur->_a->pos._z;
		}
		if(cur->_b->pos._z>max._z) {
			max._z = cur->_b->pos._z;
		}
		if(cur->_c->pos._z>max._z) {
			max._z = cur->_c->pos._z;
		}
	}

	return max;
}

CVector CObject::GetCenter() {
	CVector max = Max();
	CVector min = Min();

	return CVector((max._x+min._x)/2,(max._y+min._y)/2,(max._z+min._z)/2);
}

/* Centers the object in its coordinate system. The offset from origin to object center will be transfered to the matrix,
so your object actually does not move. Usefull if you want prepare objects for self rotation. */
void CObject::Detach() {
		CVector center = GetCenter();
		
		_triangles.Restart();
		while(_triangles.HasNext()) {
			CTriangle* c = _triangles.NextStack();
			
			c->_a->pos._x -= center._x;
			c->_b->pos._x -= center._x;
			c->_c->pos._x -= center._x;
			
			c->_a->pos._y -= center._y;
			c->_b->pos._y -= center._y;
			c->_c->pos._y -= center._y;

			c->_a->pos._z -= center._z;
			c->_b->pos._z -= center._z;
			c->_c->pos._z -= center._z;
		}

		Shift(center);
}

CVector CObject::GetDimensions() {
	CVector max = Max();
	CVector min = Min();
	return CVector(max._x-min._x,max._y-min._y,max._z-min._z);
}

/**
void CObject::MeshSmooth() {
	Rebuild();
	CTriangle tri;
	float u,v;
	CVertex* a,b,c,d,e,f,temp;
	CVector ab,bc,ca,nab,nbc,nca,center;
	float sab,sbc,sca,rab,rbc,rca;
	float uab,vab,ubc,vbc,uca,vca;
	float sqrt3=(float)sqrt(3.0f);
	
	_triangles.Restart();
	while(_triangles.HasNext()) {
		tri= _triangles.Next();

		a = &tri._a;
		b = &tri._b;
		c = &tri._c;
		ab = CVector::Scale(0.5f,CVector::Add(b->pos,a->pos));
		bc = CVector::Scale(0.5f,CVector::Add(c->pos,b->pos));
		ca = CVector::Scale(0.5f,CVector::Add(a->pos,c->pos));

		rab = CVector::Subtract(ab,a->pos).Length();
		rbc = CVector::Subtract(bc,b->pos).Length();
		rca = CVector::Subtract(ca,c->pos).Length();
		
		nab = CVector::Scale(0.5f, CVector::Add(a.n,b.n));
		nbc=idx3d_Vector.scale(0.5f, CVector::Add(b.n,c.n));
		nca=idx3d_Vector.scale(0.5f, CVector::add(c.n,a.n));
		uab = 0.5f*(a.u+b.u);
		vab = 0.5f*(a.v+b.v);
		ubc = 0.5f*(b.u+c.u);
		vbc = 0.5f*(b.v+c.v);
		uca = 0.5f*(c.u+a.u);
		vca = 0.5f*(c.v+a.v);
		sab = 1f-nab.GetLength();
		sbc = 1f-nbc.GetLength();
		sca = 1f-nca.GetLength();
		nab.Normalize();
		nbc.Normalize();
		nca.Normalize();
		
		d = new CVertex(CVector::Sub(ab,CVector::Scale(rab*sab,nab)),uab,vab);
		e = new CVertex(CVector::Sub(bc,CVector::Scale(rbc*sbc,nbc)),ubc,vbc);
		f = new CVertex(CVector::Sub(ca,CVector::Scale(rca*sca,nca)),uca,vca);
		
		AddVertex(d);
		AddVertex(e);
		AddVertex(f);
		tri.p2=d;
		tri.p3=f;
		AddTriangle(b,e,d);
		AddTriangle(c,f,e);
		AddTriangle(d,e,f);
	}
	RemoveDuplicateVertices();			
}
**/