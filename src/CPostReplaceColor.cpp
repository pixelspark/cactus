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

CPostReplaceColor::CPostReplaceColor() {
	_from = 0;
	_to = 0;
}

CPostReplaceColor::~CPostReplaceColor() {
}

void CPostReplaceColor::ProcessImage (int *buffer, int width, int height) {
	int size = width * height;
	int index = 0;

	for (index = 0; index < size; index++) {
		if (buffer[index] == _from)
			buffer[index] = _to;
	}
}

void CPostReplaceColor::Replace (CColor from, CColor to) {

	_from = MAKE_COLOR(from._red, from._green, from._blue);
	_to = MAKE_COLOR(to._red, to._green, to._blue);
}