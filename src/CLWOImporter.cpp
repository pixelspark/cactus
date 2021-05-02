/* ---------------------------------------------------------------------------------------------------------------------------------------------------
Copyright (C) 2003-2004 Tommy van der Vorst, Jure Lebar

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

#ifndef NO_LWO_IMPORTER

CObject* CLWOImporter::FromLWO (const char* lpszFilePath) {
	FILE *file;
	CObject	*pObject = NULL;
	unsigned long datasize, bytesread;
	unsigned long type, size;

	file = fopen (lpszFilePath, "rb");

	if (!file) {
		return NULL;
	}

	union {
		unsigned long	val;
		struct {
			unsigned char	f;
			unsigned char	o;
			unsigned char	r;
			unsigned char	m;
		} ch;
	} form, pnts, polys, lwob, srfs;

	form.ch.f = 'F'; form.ch.o = 'O'; form.ch.r = 'R'; form.ch.m = 'M';
	pnts.ch.f = 'P'; pnts.ch.o = 'N'; pnts.ch.r = 'T'; pnts.ch.m = 'S';
	lwob.ch.f = 'L'; lwob.ch.o = 'W'; lwob.ch.r = 'O'; lwob.ch.m = 'B';
	polys.ch.f = 'P'; polys.ch.o = 'O';	polys.ch.r = 'L'; polys.ch.m = 'S';	
	srfs.ch.f = 'S'; srfs.ch.o = 'R'; srfs.ch.r = 'F'; srfs.ch.m = 'S';	
	
	// Make sure the Lightwave file is an IFF file.
    fread(&type, sizeof(unsigned long), 1, file);
	
	if (type != form.val) {
		fclose (file);
		assert(false);	// Not an IFF lightwave file
		return NULL;
	}	
	
    fread(&datasize, sizeof(unsigned long), 1, file);

	pObject = new CObject();
	
    // Make sure the IFF file has a LWOB form type.
    fread(&type, sizeof(unsigned long), 1, file);
    if (type != lwob.val) {
		fclose (file);
		assert(false);	// Not a LWO object
		return NULL;
	}

	// Read all Lightwave chunks.
    bytesread = 4;
    while (bytesread < datasize)  {		
		fread(&type, sizeof(unsigned long), 1, file);
		fread(&size, sizeof(unsigned long), 1, file);

		size = SwapEndian (size);
		
		if (type == pnts.val)	// Points
			read_pnts((unsigned short)size, file, pObject); 
		else if (type == polys.val)	// Polygons
        	read_polys((unsigned short)size, file, pObject); 
		else			// The rest is skipped
			fseek(file, (long)size, SEEK_CUR);
				
		bytesread += size + 8;
    }

	fclose(file);
	return pObject;
}

bool CLWOImporter::read_pnts (unsigned short size, FILE *file, CObject *pObject) {
	struct VERTEX_TAG {
		float	xx;
		float	yy;
		float	zz;
	} *points;
	
	size = size / sizeof(VERTEX_TAG);

	points = new VERTEX_TAG[size];
	fread (points, sizeof(VERTEX_TAG), size, file);

	for (int i=0; i < size; i++) {
		pObject->AddVertex 
		(
		new CVertex
			(
			SwapEndian (points[i].xx),
			SwapEndian (points[i].yy),
			SwapEndian (points[i].zz)
			)
		);
	}
	
	delete points;
	return true;
}

bool CLWOImporter::read_polys (unsigned short size, FILE *file,  CObject *pObject) {
	struct POLY_TAG {
		unsigned short	count;
		unsigned short	vertex1;
		unsigned short	vertex2;
		unsigned short	vertex3;
		unsigned short	surface;
	} *polys;

	size = size / sizeof(POLY_TAG);
	polys = new POLY_TAG[size];

	fread (polys, sizeof(POLY_TAG), size, file);

	for (int i=0; i < size; i++) {
		pObject->AddTriangle 
		(
		SwapEndian (polys[i].vertex1),
		SwapEndian (polys[i].vertex2),
		SwapEndian (polys[i].vertex3)
		);
	}

	delete polys;
	return true;
}

bool CLWOImporter::read_srfs (unsigned short size, FILE *file, CObject *pObject) {
	return true;
}

unsigned long CLWOImporter::SwapEndian (unsigned long num)
{
	union bigend {
		unsigned long	a;
		struct {
			unsigned char	a;
			unsigned char	b;
			unsigned char	c;
			unsigned char	d;
		} b;
	}	tool, temp;
	
	tool.a = num;
	temp = tool;

	tool.b.a = temp.b.d;
	tool.b.b = temp.b.c;
	tool.b.c = temp.b.b;
	tool.b.d = temp.b.a;

	return tool.a;	
}

unsigned short CLWOImporter::SwapEndian (unsigned short num) {
	union bigend {
		unsigned short	a;
		struct {
			unsigned char	hi;
			unsigned char	lo;
		} b;
	}	tool;
	unsigned char	temp;

	tool.a = num;
	temp = tool.b.hi;
	
	tool.b.hi = tool.b.lo;
	tool.b.lo = temp;
	
	return tool.a;	
}

float CLWOImporter::SwapEndian (float num) {
	union bigend {
		float	a;
		struct {
			unsigned char	a;
			unsigned char	b;
			unsigned char	c;
			unsigned char	d;
		} b;
	}	tool, temp;
	
	tool.a = num;
	temp = tool;
	
	tool.b.a = temp.b.d;
	tool.b.b = temp.b.c;
	tool.b.c = temp.b.b;
	tool.b.d = temp.b.a;
	
	return tool.a;
}

#endif