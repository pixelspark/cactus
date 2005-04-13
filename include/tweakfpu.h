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

#ifndef __CACTUS_FPUTWEAK
#define __CACTUS_FPUTWEAK

inline unsigned short BoostFPU() {
	unsigned short OldCW;
	unsigned short Load;

	__asm {
		fstcw   OldCW			; store copy of CW
		mov     ax, OldCW		; get it in ax
		and     eax, 0FCFFh		; 24 bit precision
		mov     Load, ax		; store it
		fldcw   Load			; load the FPU
	}

	return OldCW;
}

inline unsigned short TweakFPU(unsigned short newCW) {
	unsigned short oldCW;

	__asm {
		fstcw   oldCW	; store copy of CW
		fldcw   newCW	; load the FPU
	}

	return oldCW;
}

inline void RestoreFPU(unsigned short oldCW) {
	__asm fldcw oldCW;
}

class CFPUTweak {
	private:
		unsigned short oldCW;

	public:
		CFPUTweak() {
			oldCW = BoostFPU();
		}

		~CFPUTweak() {
			RestoreFPU(oldCW);
		}
};

#endif