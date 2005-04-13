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

#ifndef __CACTUS_CRASTERIZER_H
#define __CACTUS_CRASTERIZER_H

class CACTUS_API CRasterizer {
	friend class CRenderer;

	public:
		CRasterizer(CRenderer* rend);
		CRasterizer();
		virtual ~CRasterizer();
		void RebuildReferences();
		void LoadMaterial(CMaterial* material);
		void LoadLightmap(CLightmap* lightmap);
		void DrawLine(CVertex* a, CVertex* b, CColor& c);
		void DrawLine(int, int, int, int, int, int, CColor& c);

		// renderers
		inline void RenderLine();
		inline void RenderLineF();
		inline void RenderLineP();
		inline void RenderLineT();
		inline void RenderLinePT();
		inline void RenderLinePE();
		inline void RenderLinePET();
		inline void RenderLinePEB();
		inline void RenderLinePB();
		inline void DrawDot(int x, int y, float z, int color);


		void DrawWireframe(CTriangle* tri);
		inline void Render(CTriangle* tri);
		void SetCanvas(CCanvas* cv) {
			_canvas = cv;
		}
		void SetMode(int m) {
			_mode = m;
		}

		int GetMode() {
			return _mode;
		}

		void SetRenderer(CRenderer* rend) {
			_renderer = rend;
		}

		CRenderer* GetRenderer() {
			return _renderer;
		}
	public:
		bool _zbufferNegative;
		CRenderer* _renderer;
		int _width;
		int _height;
		int _mode;
		bool enableLighting;
		CBuffer<float>* _zbuffer;
		CCanvas* _canvas;
		CTexture* texture;
		int c,s;
		int color;
		int reflectivity, transparency;
		int bkgrd;
		
		CLightmap* _lightmap;
		CTexture* _bumpmap;
		int* _envmap;

		int tw, th, tbitW, tbitH;
		 int	lutID,r,
				x1,x2,x3,x4,y1,y2,y3;
		 float z1,z2,z3,z4,z,dz,dzBase,zBase;
		 int	x,y,k,dx,dy,offset,pos,temp,
				xL,xR,xBase,xMax,yMax,dxL,dxR,
			
				nx1,nx2,nx3,nx4,ny1,ny2,ny3,ny4,
				nxBase,nyBase,
				dnx4,dny4,
				dnx,dny,nx,ny,
				dnxBase,dnyBase,
			
				tx1,tx2,tx3,tx4,ty1,ty2,ty3,ty4,
				txBase,tyBase,
				dtx4,dty4,
				dtx,dty,tx,ty,
				dtxBase,dtyBase;

		int yXwidth;
		int currentColor;
		long frameNr;
		CTriangle* _currentTriangle;
};

#endif