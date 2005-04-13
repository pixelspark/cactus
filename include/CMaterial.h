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

#ifndef __CACTUS_CMATERIAL_H
#define __CACTUS_CMATERIAL_H

typedef void (FCustomRasterizer)(CRasterizer*); 

class CACTUS_API CMaterial {
	friend class CRasterizer;
	friend class CVertex;

	public:
		CMaterial();
		void SetTexture(CTexture t);
		void SetEnvMap(CTexture t);
		void SetBumpMap(CTexture t);
		inline int GetMode() {
			return mode;
		}

		void CopyFrom(CMaterial* mat) {
			texture = mat->texture;
			envmap = mat->envmap;
			bumpmap = mat->bumpmap;
			mode = mat->mode;
			transparency = mat->transparency;
			reflectivity = mat->reflectivity;
			color = mat->color;
			_custom = mat->_custom;
		}

		inline int GetTransparency() {
			return transparency;
		}

		inline int GetReflectivity() {
			return reflectivity;
		}

		inline CColor GetColor() {
			return color;
		}

		inline void SetMode(int m) {
			mode = m;
		}

		inline void EnableMode(int m) {
			mode |= m;
		}

		inline void DisableMode(int m) {
			mode &= ~m;
		}

		inline void ToggleMode(int m) {
			if((mode&m)>0) {
				DisableMode(m);
			}
			else {
				EnableMode(m);
			}
		}

		inline void SetTransparency(int t) {
			assert(t>=0&&t<=255);
			transparency = t;
		}

		inline void SetReflectivity(int r) {
			assert(r>=0&&r<=255);
			reflectivity = r;
		}

		inline void SetColor(CColor c) {
			color = c;
		}

		void SetCustomRasterizer(FCustomRasterizer c) {
			_custom = c;
		}

		void CallCustomRasterizer(CRasterizer* r) {
			_custom(r);
		}

	protected:
		CTexture texture;
		CTexture envmap;
		CTexture bumpmap;
		int mode;
		int transparency;
		int reflectivity;
		CColor color;
		FCustomRasterizer* _custom;
};

#endif