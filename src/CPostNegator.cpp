/* ---------------------------------------------------------------------------------------------------------------------------------------------------
Copyright (C) 2003-2004 Jure Lebar, Tommy van der Vorst

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

void CPostNegator::ProcessImage (int *buffer, int width, int height){
	int	size = width*height;
	
	#ifdef USE_OPTIMIZATIONS
	
	int* begin = buffer;
	int* end = buffer+size;

	static const int f[] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF };

	for(int* index=end;index>begin;index-=2) {
		__asm {
			mov eax, index		// eax points to the current two pixels
			movq MM1, [eax]	  // move the current two pixels to MM1

			movq MM2, f			// MM2 = 0xFFFFFFFF 0xFFFFFFFF
			psubd MM2, MM1	// subtract MM1 from MM2 and place the result in MM2
			movq [eax] , MM2 // place the two pixels in MM2 back in the buffer
		}
	}

	__asm {
		emms					// let the processor know we're finished with MMX
	}

	#else

	for (int index = size; index > 0; index--){
		buffer[index] = 0xFFFFFFFF - buffer[index];
	}
		
	#endif
}

