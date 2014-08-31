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

CPreSubtract::CPreSubtract() {
}

CPreSubtract::~CPreSubtract() {
}

void CPreSubtract::ProcessImage(int* begin, int width, int height) {
	unsigned char* f = this->f;

	int* end = begin+(width*height);
	for(int* index=end;index>begin;index-=1) {
		int r = (INT_GETRED(*index))-*f;
		int g = (INT_GETGREEN(*index))-*f;
		int b = (INT_GETBLUE(*index))-*f;

		if(r<0) { r = 0; }
		if(g<0) { g = 0; }
		if(b<0) { b = 0; }

		*index = MAKE_COLOR(r,g,b);
}
}