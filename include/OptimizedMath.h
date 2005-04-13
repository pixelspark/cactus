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

#ifndef __OPTIMIZED_MATH_H
#define __OPTIMIZED_MATH_H

inline float sin(float i) {
	__asm fld i;
	__asm fsin;
	__asm fstp i;
	return i;
}

inline float cos(float i) {
	__asm fld i;
	__asm fcos;
	__asm fstp i;
	return i;
}

inline float tan(float i) {
	__asm fld i;
	__asm fptan;
	__asm fstp i;
	return i;
}

inline float sqrt(float i) {
	__asm fld i;
	__asm fsqrt;
	__asm fstp i;
	return i;
}

inline float abs(float i) {
	__asm fld i;
	__asm fabs;
	__asm fstp i;
	return i;
}

extern "C" void __cdecl _ftol();

#endif
