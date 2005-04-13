/** ---------------------------------------------------------------------------------------------------------------------------------------------------
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
--------------------------------------------------------------------------------------------------------------------------------------------------- **/

#include "../include/cactus.h"
using namespace cactus;

#ifdef USE_OPTIMIZATIONS

 extern "C" __declspec(naked) void __cdecl _ftol() {
	__asm {
		PUSH	edx
		PUSH	ecx
		SUB		esp,8
		FSTP	QWORD PTR [esp]
		POP		eax
		POP		edx
		MOV		ecx,edx
		AND		edx,0x000FFFFF
		OR		 edx,0x00100000
		SHL		edx,11
		SHR		eax,21
		OR		 eax,edx
		MOV		edx,ecx
		AND		ecx,0x7FF00000
		JZ		zero
		SHR		ecx,20
		SUB		ecx,0x41E
		JC		negexp
		SHL		eax,CL
		JMP		shifted
		
		negexp:
		NEG		ecx
		CMP		ecx,32
		JAE		zero
		SHR		eax,CL
		
		shifted:
			AND edx,0x80000000
			POP ecx
			POP	edx
			JNZ negative
			RET
		
		negative:
			NEG ecx
			RET

		zero:
			SUB eax,eax
			POP ecx
			POP edx
			RET
	}
}

#endif

 void CACTUS_API SortTriangles(CLinkedList<CTriangle*>& tri, int L, int R) {
	/*float m = (tri.Atn(L)->GetDistance()+tri.Atn(R)->GetDistance())/2;
	int i = L;
	int j = R;

	CTriangle* temp;

	do {
		while(tri.Atn(i)->GetDistance()>m) {
			i++;
		}

		while(tri.Atn(j)->GetDistance()>m) {
			j--;
		}

		if(i<=j) {
			temp = tri.Atn(i);
			tri.Assign(i,tri.Atn(j));
			tri.Assign(j,temp);
			i++;
			j--;
		}
	} while(j>=i);

	if(L<j) {
		SortTriangles(tri,L,j);
	}
	if(R>i) {
		SortTriangles(tri,i,R);
	}*/
}
