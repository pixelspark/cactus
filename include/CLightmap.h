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


#ifndef __CACTUS_CLIGHTMAP_H
#define __CACTUS_CLIGHTMAP_H

/** This class holds a so-called 'lightmap' for fast rasterization. Before anything gets rendered, RebuildLightmap is called. 
This method first creates a 'sphere' in memory, and then tests how all lights in the scene affect this sphere. Then, these values are
stored in the lightmap. **/
class CACTUS_API CLightmap {
	friend class CRasterizer;

	public:
		CLightmap(CScene* scene);
		CLightmap() {
			// nix
		}
		void BuildSphereMap();
		void RebuildLightmap();
		void RebuildLightmap(CScene* sc) {
			_scene = sc;
			RebuildLightmap();
		}
	protected:
		int diffuse[65536];
		int specular[65536];
		float sphere[65536];
		CColor ambient;
		int temp, overflow, pos, r, g, b;
		CColor color;
		CScene* _scene;
};

#endif