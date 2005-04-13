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


#ifndef __CACTUS_CTEXTUREFACTORY_H
#define __CACTUS_CTEXTUREFACTORY_H

class CACTUS_API CTextureFactory {
	public:
		CTextureFactory() {
			NoiseBufferInitialized = false;
			NoiseBuffer = 0;
		}
		virtual ~CTextureFactory() {
			NoiseBufferInitialized = false;
			if(NoiseBuffer!=0) {
				delete[] NoiseBuffer;
			}
		}
		CTexture Sky(int w, int h, float density);
		CTexture Marble(int w, int h, float density);
		CTexture Wood(int w, int h, float density);
		CTexture Random(int w, int h);
		CTexture CheckerBoard(int w, int h, int cellbits, int oddcolor, int evencolor);
		CTexture CheckerBoard(int w, int h, int cellbits, CColor oddcolor, CColor evencolor);
		CTexture Perlin(int w, int h, float persistency, float density, int samples, int scale);
		CTexture Wave(int w, int h, float persistency, float density, int samples, int scale);
		CTexture Grain(int w, int h, float persistency, float density, int samples, int levels, int scale);
		CTexture Gradient(int w, int h, int* colors, int numcolors, float density);
		float Perlin2d(float x, float y, float wavelength, float persistence, int samples);
		inline float InterpolatedNoise(float x, float y, int octave);
		float SmoothNoise(int x, int y, int o);
		inline float Noise(int x, int y, int octave);
		inline float Noise(int seed, int octave);
		void InitNoiseBuffer();
	private:
		float* NoiseBuffer;
		bool NoiseBufferInitialized;
		int minx;
		int maxx;
		int miny;
		int maxy;
};


#endif