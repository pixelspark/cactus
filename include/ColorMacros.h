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


#ifndef __CACTUS_COLORMACROS_H
#define __CACTUS_COLORMACROS_H

#define ALPHA 0xFF000000
#define RED 0xFF0000
#define GREEN 0xFF00
#define BLUE 0xFF

#define MASK7Bit 0xFEFEFF 
#define MASK6Bit 0xFCFCFC
#define RGB 0xFFFFFF

#define INT_GETALPHA(color) ((color&ALPHA)>>24)
#define INT_GETRED(color) ((color&RED)>>16)
#define INT_GETBLUE(color) (color&BLUE)
#define INT_GETGREEN(color) ((color&GREEN)>>8)
#define COLOR_FROM_INT(pix) CColor(INT_GETRED(pix), INT_GETGREEN(pix), INT_GETBLUE(pix))
#define MAKE_COLOR(r,g,b) (ALPHA|(r<<16)|(g<<8)|b)

#endif