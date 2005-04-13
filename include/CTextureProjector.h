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

#ifndef __CACTUS_CTEXTUREPROJECTOR_H
#define __CACTUS_CTEXTUREPROJECTOR_H

class CACTUS_API CTextureProjector {
	public:
		static void ProjectFrontal(CObject* obj) {
			obj->Rebuild();
			CVector min = obj->Min();
			CVector max = obj->Max();

			float du=1/(max._x-min._x);
			float dv=1/(max._y-min._y);

			obj->_triangles.Restart();
			
			while(obj->_triangles.HasNext()) {
				CTriangle* tri = obj->_triangles.NextStack();

				tri->_a->_u = (tri->_a->pos._x-min._x)*du;
				tri->_a->_v = 1-(tri->_a->pos._y-min._y)*dv;

				tri->_b->_u = (tri->_b->pos._x-min._x)*du;
				tri->_b->_v = 1-(tri->_b->pos._y-min._y)*dv;

				tri->_c->_u = (tri->_c->pos._x-min._x)*du;
				tri->_c->_v = 1-(tri->_c->pos._y-min._y)*dv;
			}
		}

		static void ProjectTop(CObject* obj) {
			obj->Rebuild();
			CVector min=obj->Min();
			CVector max=obj->Max();
			float du=1/(max._x-min._x);
			float dv=1/(max._z-min._z);
			
			obj->_triangles.Restart();
			
			while(obj->_triangles.HasNext()) {
				CTriangle* tri = obj->_triangles.NextStack();

				tri->_a->_u = (tri->_a->pos._x-min._x)*du;
				tri->_a->_v = (tri->_a->pos._z-min._z)*dv;

				tri->_b->_u = (tri->_b->pos._x-min._x)*du;
				tri->_b->_v = (tri->_b->pos._z-min._z)*dv;

				tri->_c->_u = (tri->_c->pos._x-min._x)*du;
				tri->_c->_v = (tri->_c->pos._z-min._z)*dv;
			}
		}
};


#endif