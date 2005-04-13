/* ---------------------------------------------------------------------------------------------------------------------------------------------------
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
--------------------------------------------------------------------------------------------------------------------------------------------------- */
#include "../include/cactus.h"
using namespace cactus;

CTexture::CTexture(int width, int height, int* data) {
	_width = width;
	_height = height;
	_pixel = data;
	_pixel = new int[width*height];
	
	for(int y=0;y<height*width;y++) {
		_pixel[y] = data[y];
	}

	_bitWidth = 0;
	_bitHeight = 0;
}

CTexture::CTexture(int width, int height) {
	_width = width;
	_height = height;
	_pixel = 0;
	Clear();
	_bitWidth = 0;
	_bitHeight = 0;
}

CTexture::CTexture() {
	_width = 0;
	_height = 0;
	_pixel = 0;
	_bitWidth = 0;
	_bitHeight = 0;
}

CTexture::~CTexture() {
	/*if(_pixel!=0) {
		delete[] _pixel;
	}*/
}

void CTexture::Add(CTexture* tex) {
	for(int i=0;i<_width*_height;i++) {
		_pixel[i] = CColor::Add(_pixel[i],tex->_pixel[i]);
	}
}

void CTexture::Sub(CTexture* tex) {
	for(int i=0;i<_width*_height;i++) {
		_pixel[i] = CColor::Sub(_pixel[i],tex->_pixel[i]);
	}
}

void CTexture::Clear() {
	if(_pixel==0) {
		return;
	}

	memset(_pixel, 0, sizeof(int)*_width*_height);
}

CTexture CTexture::Clone() {
	CTexture ret;

	ret._height = _height;
	ret._width = _width;
	ret._bitHeight = _bitHeight;
	ret._bitWidth = _bitWidth;
	ret._pixel = new int[_width*_height];

	// TODO: use memcpy here
	for(int i=0;i<_width*_height;i++) {
		ret._pixel[i] = _pixel[i];
	}

	return ret;
}


void CTexture::Invert() {
	for(int i=0;i<_width*_height;i++) {
		_pixel[i] = 255-_pixel[i];
	}
}

void CTexture::Put(int* data) {
	if(_pixel!=0) {
		delete[] _pixel;
	}

	_pixel = new int[_width*_height];
	memcpy(_pixel, data, sizeof(int)*_width*_height);
}

void CTexture::Resize(int w, int h) {
	SetSize(w,h);
}

void CTexture::Colorize(int* pal, int num) {
	int range=num-1;
	for (int i=_width*_height;i>=0;i--) {
		_pixel[i] = pal[Crop<int>(_pixel[i],0,range)];
	}
}


void CTexture::SetSize(int w, int h) {
	if(_width==w&&_height==h) {
		return;
	}

	int offset=w*h;
	int offset2;
	if (w*h!=0) {
		int* newpixels =new int[w*h];
		for(int j=h-1;j>=0;j--) {
			offset-=w;
			offset2=(j*_height/h)*_width;
			for (int i=w-1;i>=0;i--) {
				newpixels[i+offset] = _pixel[(i*_width/w)+offset2];
			}
		}

		_width=w; 
		_height=h; 
		delete[] _pixel;
		_pixel = newpixels;
	}
}

void CTexture::Resize() {
	float log2inv=1/ log((float)2);

	_bitWidth=(int)(log((float)_width)*log2inv);
	_bitHeight=(int)(log((float)_height)*log2inv);
	int w=(int)pow(2,_bitWidth);
	int h=(int)pow(2,_bitHeight);
	Resize(w,h);
}

void CTexture::ToBumpmap() {
	if((_pixel!=0)&&((_width*_height)!=0)) {
		for(int x=0;x<_width;x++) {
			for(int y=0;y<_height;y++) {
				_pixel[y*_width+x] = (INT_GETRED(_pixel[y*_width+x])+INT_GETBLUE(_pixel[y*_width+x])+INT_GETGREEN(_pixel[y*_width+x]))/3;
			}
		}
	}
}