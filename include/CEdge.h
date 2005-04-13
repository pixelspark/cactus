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


#ifndef __CACTUS_CEDGE_H
#define __CACTUS_CEDGE_H

/** This class is not really used by cactus. **/
class CACTUS_API CEdge {	
	public:
		CEdge(CVertex* start,CVertex* end) {
			_start = start;
			_end = end;
		}

		CEdge() {
			_start = 0;
			_end = 0;
		}

		~CEdge() {
			_start = 0;
			_end = 0;
		}

		CVertex* _start;
		CVertex* _end;
};


#endif