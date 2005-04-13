#ifndef __CACTUS_CPOSTSUBTRACT_H
#define __CACTUS_CPOSTSUBTRACT_H

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
class CACTUS_API CPreSubtract : public CPreEffect {
	public:
		CPreSubtract();
		virtual ~CPreSubtract();

		void ProcessImage (int *buffer, int width, int height);
		inline void SetLevel(unsigned char x) {
			f[0] = x;
			f[1] = x;
			f[2] = x;
			f[3] = x;
			f[4] = x;
			f[5] = x;
			f[6] = x;
			f[7] = x;
		}
	
	protected:
		unsigned char f[8];
};

#endif