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

#ifndef __CACTUS_CMATH_H
#define __CACTUS_CMATH_H

class CMath {
	public:
		CMath() {
			trig = false;
		}
		
		~CMath() {
		}

		inline float sin(float angle) {
			#ifdef USE_LUT
			
			static float rad2scale = 4096.0f/3.14159265f/2.0f;
			 static float pad = 256.0f*3.14159265f;
			if(!trig) BuildTrig();
			return sinus[(int)((angle+pad)*rad2scale)&0xFFF];
			
			#else
			
			return (float)::sin(angle);

			#endif
		}

		inline float cos(float angle) {
			#ifdef USE_LUT
			
			static float rad2scale = 4096.0f/3.14159265f/2.0f;
			static float pad = 256.0f*3.14159265f;
			if(!trig) BuildTrig();
			return cosinus[(int)((angle+pad)*rad2scale)&0xFFF];
			
			#else

			return (float)::cos(angle);

			#endif
		}

		void BuildTrig() {		
			static float rad2scale = 4096.0f/3.14159265f/2.0f;

			for (int i=0;i<4096;i++) {
				sinus[i]=(float)::sin((float)i/rad2scale);
				cosinus[i]=(float)::cos((float)i/rad2scale);
			}

			trig = true;
		}
	
	protected:
		float sinus[4096];
		float cosinus[4096];
		bool trig;
};

static CMath math;

#endif