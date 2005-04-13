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


#ifndef __CACTUS_INLINES_H
#define __CACTUS_INLINES_H

template<class T> inline bool Inrange(T num, T min, T max) {
	return ((num>=min)&&(num<max));
}

// ---------------------------------------------------------------------------------------------------------------------------------------------------
// Inline method definitions. These need to be defined in the header file, because otherwise an application that uses this library won't
// be able of running them, since it has no access to the source code.
// ---------------------------------------------------------------------------------------------------------------------------------------------------
inline CACTUS_API double deg2rad(double deg) {
	return deg/180*PI;
}

inline CACTUS_API double rad2deg(double rad) {
	return rad/PI*180;
}

inline CACTUS_API float Interpolate(float a, float b, float d) {
	float f=(float)(1-cos(d*PI))*0.5f;
	return a+f*(b-a);
}

template<class T> inline T Crop(T num,T min,T max) {
	return (num<min)?min:(num>max)?max:num;
}

inline CACTUS_API const char* GetCactusVersion() {
	return CACTUS_VERSION;
}

#endif