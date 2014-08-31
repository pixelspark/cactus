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


#ifndef __CACTUS_CLIGHT_H
#define __CACTUS_CLIGHT_H

/** This class brightens up your 3d-scene.  Shouldn't be too difficult to use. **/
class CACTUS_API CLight {
	friend class CLightmap;

	public:
		CLight();
		CLight(CVector& direction);
		CLight(CVector& direction, CColor& diffuse);
		CLight(CVector& direction, CColor& color, int highlightSheen, int highlightSpread);
		CLight(CVector& direction, CColor& diffuse,CColor& specular, int highlightSheen, int highlightSpread);
		void Project(CMatrix& m);
		void SetDirection(const CVector& direction) {
			direction.Clone(v);
			v.Normalize();
		}
	
		CVector v; // light direction
		CVector v2; // projected light direction
		CColor diffuse;
		CColor specular;
		int highlightSheen;
		int highlightSpread;
		CMatrix matrix2;
		CMatrix matrix;
};

#endif