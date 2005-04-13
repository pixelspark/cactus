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


#ifndef __CACTUS_CTEXTURE_H
#define __CACTUS_CTEXTURE_H

class CACTUS_API CTexture {
	friend class CRasterizer;
	public:
		CTexture();
		CTexture(int width, int height);
		CTexture(int width, int height, int* data);
		void Resize();
		int GetWidth() {
			return _width;
		}

		int GetHeight() {
			return _height;
		}

		unsigned char* GetDataAsRGBA() {
			unsigned char* data = new unsigned char[_width*_height*3];
			for(int y=0;y<_height;y++) {
				for(int x=0;x<_width;x++) {
					data[(y*_width*3)+(x*3)] = INT_GETRED(_pixel[y*_width+x]);
					data[(y*_width*3)+(x*3)+1] =  INT_GETGREEN(_pixel[y*_width+x]);
					data[(y*_width*3)+(x*3)+2] =  INT_GETBLUE(_pixel[y*_width+x]);
				}
			}

			return data;
		}
		void Colorize(int* cols, int num);
		void SetFlatTransparency(int alpha);
		void Resize(int w, int h);
		void Put(int* data);
		void Mix(CTexture* tex);
		void Add(CTexture* tex);
		void Sub(CTexture* sub);
		void Invert();
		void Multiply(CTexture* mult);
		void Clear();
		void ToBumpmap();
		void SetSize(int w, int h);
		virtual ~CTexture();
		CTexture Clone();

		int _height;
		int _width;	
		int* _pixel;
	protected:
		int _bitWidth;
		int _bitHeight;	
};


#endif