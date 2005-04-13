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
#include <float.h>
using namespace cactus;

CRenderer::CRenderer(CScene* sc): _lightmap(sc) {
	SetScene(sc);
	_rasterizer.SetRenderer(this);
	_zbufferNegative = false;
	_populateIDBuffer = false;
	_IDBuffer = 0;
}

CRenderer::~CRenderer() {
	_scene = 0;
	_zbuffer.UnAlloc();
	if(_IDBuffer!=0) delete[] _IDBuffer;
	_populateIDBuffer = false;
}

void CRenderer::SetPopulateIDBuffer(bool pid) {
	_populateIDBuffer = pid;
	if(pid) {
		_IDBuffer = new CTriangle*[_scene->GetWidth()*_scene->GetHeight()];
		memset(_IDBuffer,0,sizeof(CTriangle*)*_scene->GetWidth()*_scene->GetHeight());
	}
	else {
		if(_IDBuffer!=0) delete[] _IDBuffer;
	}
}

bool CRenderer::GetPopulateIDBuffer() {
	return _populateIDBuffer;
}

CTriangle* CRenderer::GetTriangleAt(int x, int y) {
	if(!_populateIDBuffer) return 0;
	if(x<0||y<0) return 0;
	if(x>_scene->GetWidth()||y>_scene->GetHeight()) return 0;
	return _IDBuffer[y*_scene->GetWidth()+x];	
}

CRasterizer* CRenderer::GetRasterizer() {
	return &_rasterizer;
}

void CRenderer::SetMode(int rasterizerMode) {
	_rasterizer.SetMode(rasterizerMode);
}

int CRenderer::GetMode() {
	return _rasterizer.GetMode();
}

CScene* CRenderer::GetScene() {
 	return _scene;
}

void CRenderer::SetScene(CScene* sc) {
	_scene = sc;

	if(_scene->_lightNeedsRebuild) {
		_lightmap.BuildSphereMap();
		_lightmap.RebuildLightmap(sc);
		_scene->_lightNeedsRebuild = false;
	}

	_rasterizer.SetRenderer(this);
	_rasterizer.RebuildReferences();
}

void CRenderer::Render(CCanvas* can, CCamera* cam) {
	// clear buffers
	if(!((_zbuffer.GetWidth()==can->GetWidth())&&(_zbuffer.GetHeight()==can->GetHeight()))) {
		_zbuffer.AllocNewArray(can->GetWidth(),can->GetHeight());
	}

	_zbuffer.Clear(FLT_MAX);

	if(_populateIDBuffer) memset(_IDBuffer,0,sizeof(_IDBuffer)*_scene->GetWidth()*_scene->GetHeight());

	_rasterizer.SetCanvas(can);
	can->StartPainting();
	can->Clear();
	cam->SetScreenSize(can->GetWidth(),can->GetHeight()); 

	_scene->Prepare();

	CMatrix m = CMatrix::Multiply(*cam->GetMatrix(),_scene->_matrix);
	CMatrix nm = CMatrix::Multiply(*cam->GetNormalMatrix(),_scene->_normalMatrix);

	CMatrix normalProjection, vertexProjection;
	CMatrix* normalProjectionPointer = 0;
	CMatrix* vertexProjectionPointer = 0;
	CObject* obj;
	CTriangle* t;

	int w = can->GetWidth();
	int h = can->GetHeight();
	
	_scene->_objects.Restart();
	while(_scene->_objects.HasNext()) {
		obj = *(_scene->_objects.Next());

		if(obj->IsVisible()) {	
			obj->_matrix.Clone(vertexProjection);
			obj->_normalMatrix.Clone(normalProjection);

			vertexProjection.Transform(m);
			normalProjection.Transform(nm);

			_rasterizer.LoadMaterial(&obj->_material);
			obj->_triangles.Restart();
			vertexProjectionPointer = &vertexProjection;
			normalProjectionPointer = &normalProjection;

			while(obj->_triangles.HasNext()) {
				t = obj->_triangles.NextStack();
				t->_a->Project(vertexProjectionPointer,normalProjectionPointer,cam);
				t->_a->ClipFrustum(w,h);
				t->_b->Project(vertexProjectionPointer,normalProjectionPointer,cam);
				t->_b->ClipFrustum(w,h);
				t->_c->Project(vertexProjectionPointer,normalProjectionPointer,cam);
				t->_c->ClipFrustum(w,h);				
				
				t->Project(normalProjection);
				t->ClipFrustum(w,h);

				//EnqueueTriangle(t);
				if(t->GetVisible()) {
					_rasterizer.Render(t);
				}
			}
		}
	}

	can->Render();

}

void CRenderer::ClearQueue() {
	_triangleQueue.Empty();
}

void CRenderer::BuildLightmap() {
	
	_lightmap.RebuildLightmap();
	_rasterizer.LoadLightmap(&_lightmap);
}

CLinkedList<CTriangle*> CRenderer::GetTriangleQueue() {
	//SortTriangles(_triangleQueue,0,_triangleQueue.GetCount()-1);
	
	return _triangleQueue;
}

void CRenderer::EnqueueTriangle(CTriangle* tr) {
	if(tr->GetVisible()) {	
		_triangleQueue.Add(tr);
	}
}
