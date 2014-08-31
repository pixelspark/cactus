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


#ifndef __CACTUS_CCANVAS_H
#define __CACTUS_CCANVAS_H

/** This class holds a buffer where the rasterizer can draw to. Subclass it if you want to adapt it to your operating system.
For Windows, there is already a GDI subclass of CCanvas. See the sandstorm library. 
@remark
	Each pixel is represented in the canvas as 1 integer. Use the INT_GETRED, INT_GETGREEN and INT_GETBLUE macros
	to get the color per channel from this integer. Use MAKE_COLOR to create your own color from separate channel values.
**/
class CACTUS_API CCanvas {
	friend class CPostEffect;

	public:
		CCanvas(int width, int height) {
			_buffer = new int[width*height];
			_width = width;
			_height = height;
			_disableClear = false;
		}
		
		virtual ~CCanvas() {
		}

		inline void SetDisableClear(bool c) {
			_disableClear = c;
		}

		void Destroy() {
			if(_buffer!=0) {
				delete[] _buffer;
			}
		}

		inline int Mix(int a, int b, int c, int d) {
			// red channel
			int red = (INT_GETRED(a)+INT_GETRED(b)+INT_GETRED(c)+INT_GETRED(d))>>2;
			int green = (INT_GETGREEN(a)+INT_GETGREEN(b)+INT_GETGREEN(c)+INT_GETGREEN(d))>>2;
			int blue = (INT_GETBLUE(a)+INT_GETBLUE(b)+INT_GETBLUE(c)+INT_GETBLUE(d))>>2;

			return MAKE_COLOR(red,green,blue);
		}

		void ScaleDown() {
			int new_width = _width/2;
			int new_height = _height/2;

			int* new_buffer;
			new_buffer = new int[new_width*new_height];

			for(int x=0;x<_width-2;x+=2) {
				int new_x = x/2;

				for(int y=0;y<_height-2;y+=2) {
					int new_y = y/2;
					new_buffer[(new_y*new_width)+new_x] = Mix(_buffer[y*_width+x], _buffer[y*_width+x+1], _buffer[(y+1)*_width+x],_buffer[(y+1)*_width+x+1]);
				}
			}

			throw 1337;

			memcpy(_buffer,new_buffer,4*new_width*new_height);
			//delete[] new_buffer;
		}

		virtual void StartPainting() {
			// signals that the rendering is about to begin
		}
		
		inline int GetWidth() {
			return _width;
		}

		inline int GetHeight() {
			return _height;
		}

		inline virtual void Clear() {
			/*for(int i=0;i<_width*_height*3;i++) {
				_buffer[i] = 0;
			}*/
			
			if(!_disableClear)  {
				memset(_buffer,0,sizeof(int)*_width*_height);
			}
		}

		void UseBuffer(int* buf) {
			delete[] _buffer;
			_buffer = buf;
		}

		inline virtual void Clear(CColor c) {
			int col = c.ToInt();
			
			for(int y=0;y<_height;y++) {
				for(int x=0;x<_width;x++) {
					_buffer[y*_width+x] = col;
				}
			}
		}

		virtual void Render() {
			// rendering has ended, our final image in _buffer can be drawn to screen
		}

		void DrawTexel(int x, int y, const CColor& c) {
			int col = c.ToInt();
			_buffer[y*_width+x] = col;
		}

		inline CColor At(int x, int y) {
			return CColor(_buffer[y*_width+x]);
		}
	
		inline void At(int x, int y, CColor* c) {
		}

		inline void At(int x, int y, int& c) {
			c = _buffer[y*_width+x];
		}

		inline void ApplyEffect (CPostEffect& e) {
			e.Call(_buffer, _width, _height);
		}

		inline void ApplyEffect(CPostEffect* e) {
			e->Call(_buffer,_width,_height);
		}

		int* _buffer; // pixel array
		int _width;
		int _height;
		bool _disableClear;
};

#endif