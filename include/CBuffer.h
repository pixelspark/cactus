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


#ifndef __CACTUS_CBUFFER_H
#define __CACTUS_CBUFFER_H

/** The CBuffer class defines a buffer for usage with z-buffering. It contains methods for resetting the array
fast and takes care of memory management. **/
template<class T> class CACTUS_API CBuffer {
	public:
		CBuffer(int width, int height) {
			_array = new T[width*height];
			_height = height;
			_width = width;
			_size = width*height;
		}
		
		CBuffer() {
			_width = 0;
			_height = 0;
			_array = 0;
			_size = 0;
		}

		virtual ~CBuffer() {
			delete[] _array;
			_height = 0;
			_width = 0;
			_size = 0;
		}

		void UnAlloc() {
			delete[] _array;
			_height = 0;
			_width = 0;
			_size = 0;
			_array = 0;
		}

		inline void Clear(T value) {
			for(int a=0;a<_size-1;a++) {
				_array[a] = value;
			}
		}

		inline void Clear() {
			memfill(_array, 0, sizeof(T)*_size);
		}

		void Reset(int val) {
			memset(_array,val,_size*sizeof(T));
				/*long i = sizeof(T)*_size;
				void* ar = _array;

				__asm {
					movq mm0,val
					punpckldq mm0,mm0
					mov edi,ar
					mov eax,i

					loopwrite:
					movntq 0[edi], mm0
					movntq 8[edi],mm0

					add edi,16
					sub eax,2
					jg loopwrite
					
					emms
				}*/
		}
		
		inline T& Get(int w, int h) {
			assert(_array!=0);
			assert(w<=_width);
			assert(h<=_height);
			
			return _array[h*_width+w];
		}

		inline T& operator[](int index) {
			assert(index<=_size);
			assert(_array!=0);
			return _array[index];
		}

		inline void PutIndex(int index, T value) {
			assert(_array!=0);
			_array[i] = value;
		}

		inline T GetIndex(int index) {
			assert(_array!=0);
			assert(_size>index);
			return _array[index];
		}

		inline void Put(int w, int h,T value) {
			assert(_array!=0);
			//assert(w<=_width);
			//assert(h<=_height);
			if(w>=_width||h>=_height) {
				return;
			}

			_array[h*_width+w] = value;
		}

		inline int GetWidth() {
			return _width;
		}

		inline int GetHeight() {
			return _height;
		}

		inline void AllocNewArray(int width, int height) {
			assert(width>=0);
			assert(height>=0);

			if(_array!=0) {
				delete[] _array;
			}

			_width = width;
			_height = height;
			_size = width*height;
			_array = new T[width*height];
		}

		T* _array;
	private:
		int _width;
		int _height;
		int _size;
};

#endif