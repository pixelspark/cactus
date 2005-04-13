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

CPostBlur::CPostBlur(){
	_amount = 0;
}

CPostBlur::~CPostBlur(){
}

void CPostBlur::ProcessImage (int *buffer, int width, int height) {
	unsigned char mask_val[9] = {
		1, 1, 1, 
		1, 5 * (11 - _amount), 1, 
		1, 1, 1 
	};
	
	int x, y;
	int end_x = width - 1, end_y = height - 1;
	int mask_x, mask_y, mask_count = 0, divisor = 0;
	int red = 0, green = 0, blue = 0;
	int	index;

	/// Jure: this still needs some optimization
	/// Tommy: maybe this could be optimized using MMX/SSE? If you are going to use MMX/SSE, please use the
	/// USE_OPTIMZATION #define that declares wheter optimizations should be used or not (if any).
	for (x = 1; x < end_x; x++) {
		for (y = 1; y < end_y; y++) {
			mask_count = 0;
			red = 0, green = 0, blue = 0;
			divisor = 0;
			
			for (mask_x = x - 1; mask_x < x + 2; mask_x++) {
				for (mask_y = y - 1; mask_y < y + 2; mask_y++) {
					index = mask_y * width + mask_x;
					
					red += INT_GETRED(buffer[index]) * mask_val[mask_count];
					green += INT_GETGREEN(buffer[index]) * mask_val[mask_count];
					blue += INT_GETBLUE(buffer[index]) * mask_val[mask_count];

					divisor += mask_val[mask_count];					
				}

				mask_count++;
			}

			buffer[index] = MAKE_COLOR(min(255, red / divisor),min(255, green / divisor),min(255, blue / divisor));
		}
	}
}

