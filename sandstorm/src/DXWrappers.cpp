//--------------------------------------
// Copyright (c) Reliable Software, 1999
//--------------------------------------

#include "../include/Main.h"

using namespace Direct;

Draw::Draw ()
{
	HRESULT res = ::DirectDrawCreate (0, &_pDraw, 0);
	if(res != DD_OK) 
		throw "Cannot create Direct Draw object";
}

unsigned HiBitShift (unsigned val)
{
	unsigned i = 0;
	while (val != 0)
	{
		val >>= 1;
		++i;
	}
	return i;
}

void PixelFormat::Init (SurfaceDesc & desc)
{
	DDPIXELFORMAT & format = desc.PixelFormat ();
	if (format.dwFlags != DDPF_RGB)
		throw "Direct Draw: Non-RGB formats not supported";
	_bpp = format.dwRGBBitCount;
	_redMask = format.dwRBitMask;
	_greenMask = format.dwGBitMask;
	_blueMask = format.dwBBitMask;
	_mask = ~(_redMask | _greenMask | _blueMask);
	switch (_bpp)
	{
	case 16:
		_redShift   = HiBitShift (_redMask) + 8;
		_greenShift = HiBitShift (_greenMask) + 8;
		_blueShift  = HiBitShift (_blueMask) + 8;
		break;
	case 24:
		break;
	case 32:
		break;
	default:
		throw "Only 16, 24 and 32 bit graphics supported";
	}
}

void Surface::Fill (COLORREF color)
{
	assert (_i != 0);
	DDBLTFX bltFx;
	bltFx.dwSize = sizeof (DDBLTFX);
	SurfaceDesc desc;
	GetDescription (desc);
	PixelFormat pix (desc);
	bltFx.dwFillColor = pix.ColorValue (color);
	HRESULT res = _i->Blt (0, 0, 0, DDBLT_COLORFILL, &bltFx);
	if(res != DD_OK) 
		throw "Cannot perform a blt";
}
