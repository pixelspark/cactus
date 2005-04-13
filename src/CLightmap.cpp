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


// ---------------------------------------------------------------------------------------------------------------------------------------------------
// Implementations for the CLightmap class.
// ---------------------------------------------------------------------------------------------------------------------------------------------------
#include "../include/cactus.h"
using namespace cactus;

CLightmap::CLightmap(CScene* scene) {
	scene->Rebuild();
	_scene = scene;

	BuildSphereMap();
	RebuildLightmap();

}

void CLightmap::BuildSphereMap() {
	float fnx, fny, fnz;
	int pos;

	for (int ny=-128;ny<128;ny++) {
		fny=(float)ny/128;
		for (int nx=-128;nx<128;nx++) {
			pos=nx+128+((ny+128)<<8);
			fnx=(float)nx/128;
			fnz=(float)(1-sqrt(fnx*fnx+fny*fny));
			sphere[pos] = (fnz>0)?fnz:0;
		}
	}
}

void CLightmap::RebuildLightmap() {
	CVector l;
	float fnx, fny, phongfact, sheen, spread;
	CColor diffuse, specular;
	int cos, dr, dg, db, sr, sg, sb, pos;

	for(int ny=-128;ny<128;ny++) {
		fny = (float)ny/128;
		for(int nx=-128;nx<128;nx++) {
			pos = nx+128+((ny+128)<<8);
			fnx = (float)nx/128;
			sr = 0;
			sg = 0;
			sb = 0;
			dr = 0;
			dg = 0;
			db = 0;
		
			_scene->_lights.Restart();
			while(_scene->_lights.HasNext()) {
				CLight* li = _scene->_lights.NextStack();
				l = li->v;
				specular = li->specular;
				diffuse = li->diffuse;
				sheen = (float)li->highlightSheen/255.0f;
				spread = (float)li->highlightSpread/4096;
				spread = (spread<0.01f)?0.01f:spread;

				//cos=(int)(255*idx3d_Vector.angle(light[i].v,new idx3d_Vector(fnx,fny,sphere[pos])));
				cos = (int)(255*CVector::Angle(li->v,CVector(fnx, fny, sphere[pos])));
				cos = (cos>0)?cos:0;

				dr += (diffuse._red*cos)>>8; // >>8
				dg += (diffuse._green*cos)>>8; //>>8;
				db += (diffuse._blue*cos)>>8; //>>8;

				phongfact = sheen*(float)pow((float)cos/255.0f,1/spread);

				sr += (int)((float)specular._red*phongfact);
				sg += (int)((float)specular._green*phongfact);
				sb += (int)((float)specular._blue*phongfact);

				sr = sr>255?255:sr;
				sg = sg>255?255:sg;
				sb = sb>255?255:sb;

				dr = dr>255?255:dr;
				dg = dg>255?255:dg;
				db = db>255?255:db;				
			}

			this->diffuse[pos] = CColor(dr, dg, db).ToInt();
			this->specular[pos] = CColor(sr, sg, sb).ToInt();
		}
	}
}