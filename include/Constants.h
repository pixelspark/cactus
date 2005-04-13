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


#ifndef __CACTUS_CONSTANTS_H
#define __CACTUS_CONSTANTS_H

// ---------------------------------------------------------------------------------------------------------------------------------------------------
// Rasterizer modes: 
//
//	0	1	 2	 4	 8  16 32
//	F	W	P	E	T   B  C
//
// These are the bits that can be set/unset to select features. For example, if you want textured, phongshaded, you can specify
// int mode = PHONG&TEXTURED, because PHONG (bit 4) plus TEXTURED (bit 16) is 20. To change a mode, for example,
// if you have a phong-shaded, envmapped cube, it will have mode 12 (8+4). If you want to have it flatshaded, consider this:
// int mode = PHONG&ENVMAP; 
// mode = mode~PHONG;
// mode = mode|FLAT;
//
// Have fun :-)
// ---------------------------------------------------------------------------------------------------------------------------------------------------
const static int FLAT = 0;
const static int WIREFRAME = 1;
const static int PHONG = 2;
const static int ENVMAP = 4;
const static int TEXTURED = 8;
const static int BUMPMAP = 16;
const static int CUSTOM = 32;
const static int VERTICES = 64;


// zbuffer constant
const float zFar =4294967295.0f;

#endif