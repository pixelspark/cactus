#if !defined (DIRECTDRAW_H)
#define DIRECTDRAW_H

//--------------------------------------
// Copyright (c) Reliable Software, 1999
//--------------------------------------
#include "ddraw.h"
#include "Canvas.h"
#include <cassert>

namespace Direct
{
	// Direct Draw object

	class Draw
	{
	public:
		Draw ();
		~Draw ()
		{
			_pDraw->Release ();
		}
		void SetCoopNormal (HWND h)
		{
			HRESULT res = _pDraw->SetCooperativeLevel(h, DDSCL_NORMAL);
			if(res != DD_OK) 
				throw "Cannot set normal cooperative level";
		}
		IDirectDraw * operator-> () { return _pDraw; }
	private:
		IDirectDraw * _pDraw;
	};

	// The base class for all interfaces
	// Has sharing semantics

	template<class I>
	class IFace
	{
	public:
		IFace (IFace<I> & i)
		{
			i->AddRef ();
			_i = i._i;
		}
		~IFace ()
		{
			if (_i)
				_i->Release ();
		}
		void operator = (IFace<I> & i)
		{
			if (i._i)
				i._i->AddRef ();
			if (_i)
				_i->Release ();
			_i = i._i;
		}
		I * operator-> () { return _i; }
		operator I * () { return _i; }

	protected:

		IFace () : _i (0) {}
	protected:

		I * _i;
	};

	// Clipper for blitting

	class Clipper: public IFace<IDirectDrawClipper>
	{
	public:
		Clipper (Draw & draw) 
		{
			HRESULT res = draw->CreateClipper (0, &_i, 0);
			if (res != DD_OK)
				throw "Cannot create clipper";
		}
		void SetHWnd (HWND hwnd)
		{
			_i->SetHWnd (0, hwnd);
		}
	};

	// Surface description

	class SurfaceDesc
	{
	public:
		SurfaceDesc ()
		{
			Clear ();
		}
		DDSURFACEDESC * operator & () { return &_srfDesc; }
		void Clear ()
		{
			memset (&_srfDesc, 0, sizeof (DDSURFACEDESC));
			_srfDesc.dwSize = sizeof (DDSURFACEDESC);
		}
		void SetCapabilities (DWORD caps)
		{
			_srfDesc.dwFlags |= DDSD_CAPS;
			_srfDesc.ddsCaps.dwCaps = caps;
		}
		void SetDimensions (int width, int height)
		{
			_srfDesc.dwFlags |= (DDSD_WIDTH | DDSD_HEIGHT);
			_srfDesc.dwWidth = width;
			_srfDesc.dwHeight = height;
		}

		int Height () const { return _srfDesc.dwHeight; }
		int Width () const { return _srfDesc.dwWidth; }
		int Pitch () const { return _srfDesc.lPitch; }
		void * Buffer () const { return _srfDesc.lpSurface; }
		DDPIXELFORMAT & PixelFormat () { return _srfDesc.ddpfPixelFormat; }
	private:
		DDSURFACEDESC	_srfDesc;
	};

	// Pixel format

	class PixelFormat
	{
	public:
		PixelFormat () {}
		PixelFormat (SurfaceDesc & desc)
		{
			Init (desc);
		}
		void Init (SurfaceDesc & desc);
		int BitsPp () const { return _bpp; }
		unsigned long Mask () const { return _mask; }
		unsigned long ColorValue16 (COLORREF color)
		{
			return (
				  (GetRValue (color) << _redShift) & (_redMask << 16)
				| (GetGValue (color) << _greenShift) & (_greenMask << 16)
				| (GetBValue (color) << _blueShift) & (_blueMask << 16))
				>> 16;
		}
		unsigned long ColorValue24 (COLORREF color)
		{
			return
				  (GetRValue (color) << 16) & _redMask
				| (GetGValue (color) << 8) & _greenMask
				| GetBValue (color) & _blueMask;
		}
		unsigned long ColorValue32 (COLORREF color)
		{
			return
				  (GetRValue (color) << 16) & _redMask
				| (GetGValue (color) << 8) & _greenMask
				| GetBValue (color) & _blueMask;
		}
		unsigned long ColorValue (COLORREF color)
		{
			switch (_bpp)
			{
			case 16:
				return ColorValue16 (color);
			case 24:
				return ColorValue24 (color);
			case 32:
				return ColorValue32 (color);
			default:
				throw "PixelFormat: only 16, 24 and 32 bits supported";
			}
		}

	private:
		int				_bpp; // bits per pixel 4, 8, 16, 24, or 32
		unsigned long	_redMask;
		unsigned long	_greenMask;
		unsigned long	_blueMask;
		unsigned _redShift;
		unsigned _greenShift;
		unsigned _blueShift;
		unsigned long	_mask;
	};

	// Surface (base class)

	class Surface: public IFace<IDirectDrawSurface>
	{
		friend class SurfaceBuf;
	protected:
		// Locking and unlocking the whole surface
		void Lock (SurfaceDesc & desc)
		{
			assert (_i != 0);
			HRESULT res;
			do
				res = _i->Lock (0, &desc, 0, 0);
			while (res == DDERR_WASSTILLDRAWING);

			if(res != DD_OK) 
				throw "Cannot lock surface";
		}
		void Unlock ()
		{
			assert (_i != 0);
			_i->Unlock (0);
		}
	public:
		Surface () {}

		void GetDescription (SurfaceDesc & desc)
		{
			HRESULT res = _i->GetSurfaceDesc (&desc);
			if(res != DD_OK) 
				throw "Cannot get surface description";
		}

		void SetClipper (Clipper & clipper)
		{
			assert (_i != 0);
			HRESULT res = _i->SetClipper (clipper);
			if(res != DD_OK) 
				throw "Cannot set clipper";
		}
		void BltFrom (Surface & src, RECT * dstRect = 0, RECT * srcRect = 0)
		{
			assert (_i != 0);
			HRESULT res = _i->Blt (dstRect, src._i, srcRect, 0, 0);
			if(res != DD_OK) 
				throw "Cannot perform a blt";
		}
		void Fill (COLORREF color);
	};

	class Canvas: public ::Canvas
	{
	public:
		Canvas (Surface & surface)
			: _surface (surface), Canvas (0)
		{
			HRESULT res;
			do {
				res = _surface->GetDC (&_hdc);
			} while (res == DDERR_WASSTILLDRAWING);
			if (res != DD_OK)
				throw "Cannot get DC from surface";
		}
		~Canvas ()
		{
			_surface->ReleaseDC (_hdc);
		}
	private:
		Surface & _surface;
	};

	// Surface buffer for direct pixel setting

	class SurfaceBuf
	{
	public:
		SurfaceBuf (Surface & surface)
			: _surface (surface)
		{
			SurfaceDesc desc;
			surface.Lock (desc);
			_pitch = desc.Pitch ();
			_buf = static_cast<unsigned char *> (desc.Buffer ());
			_format.Init (desc);
			int bpp = _format.BitsPp ();
			if (bpp != 16 && bpp != 24 && bpp != 32)
			{
				surface.Unlock ();
				throw "Only high color and true color supported";
			}
		}
		~SurfaceBuf ()
		{
			_surface.Unlock ();
		}
		void SetPixel (int x, int y, COLORREF color)
		{
			switch (_format.BitsPp ())
			{
			case 16:
				{
					int offset = y * _pitch + x * 2;
					unsigned short * p = reinterpret_cast<unsigned short *> (_buf + offset);
					*p &= _format.Mask ();
					*p |= static_cast<unsigned short> (_format.ColorValue16 (color));
				}
				break;
			case 24:
				{
					int offset = y * _pitch + x * 3;
					unsigned long * p = reinterpret_cast<unsigned long *> (_buf + offset);
					*p &= _format.Mask ();
					*p |= _format.ColorValue24 (color);
				}
				break;
			case 32:
				{
					int offset = y * _pitch + x * 4;
					unsigned long * p = reinterpret_cast<unsigned long *> (_buf + offset);
					*p &= _format.Mask ();
					*p |= _format.ColorValue32 (color);
				}
				break;
			}
		}
	private:
		Surface   & _surface;
		unsigned char  * _buf;
		int			_pitch;
		PixelFormat	_format;
	};

	// Primary surface representing the screen

	class PrimarySurface: public Surface
	{
	public:
		PrimarySurface () {}
		PrimarySurface (Draw & draw) { Init (draw); }
		void Init (Draw & draw)
		{
			SurfaceDesc desc;
			desc.SetCapabilities (DDSCAPS_PRIMARYSURFACE);
			HRESULT res = draw->CreateSurface (&desc, &_i, 0);
			if(res != DD_OK) 
				throw "Cannot create primary surface";
		}
	};

	// Off-screen surface

	class OffScreenSurface: public Surface
	{
	public:
		OffScreenSurface () {}
		OffScreenSurface (Draw & draw, int width, int height) { Init (draw, width, height); }
		void Init (Draw & draw, int width, int height)
		{
			SurfaceDesc desc;
			desc.SetCapabilities (DDSCAPS_OFFSCREENPLAIN);
			desc.SetDimensions (width, height);
			HRESULT res = draw->CreateSurface (&desc, &_i, 0);
			if(res != DD_OK) 
				throw "Cannot create off-screen surface";
		}
	};

	// Client rectangle in screen coordinates

	class WinRect: public RECT
	{
	public:
		WinRect (HWND h)
		{
			POINT pt;
			pt.x = 0;
			pt.y = 0;
			::ClientToScreen (h, &pt);
			::GetClientRect (h, this);
			left += pt.x;
			right += pt.x;
			top += pt.y;
			bottom += pt.y;
		}
	};

}

#endif
