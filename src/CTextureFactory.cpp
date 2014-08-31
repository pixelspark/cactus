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

float CTextureFactory::InterpolatedNoise(float x, float y, int octave) {
	int intx = (int)x;
	int inty = (int)y;
	float fracx = x-(float)intx;
	float fracy = y-(float)inty;

	float i1 = Interpolate(Noise(intx, inty, octave), Noise(intx+1, inty, octave),fracx);
	float i2 = Interpolate(Noise(intx, inty+1, octave), Noise(intx+1, inty+1, octave), fracx);
	return Interpolate(i1, i2, fracy);
}

float CTextureFactory::SmoothNoise(int x, int y, int o) {
	return	(Noise(x-1, y-1,o)+Noise(x+1, y-1,o)+Noise(x-1, y+1,o)+Noise(x+1, y+1,o))/16+(Noise(x-1, y,o)+Noise(x+1, y,o)+Noise(x, y-1,o)+Noise(x, y+1,o))/8+Noise(x,y,o)/4;
}
	
float CTextureFactory::Noise(int x, int y, int octave) {
	return NoiseBuffer[((octave&3)*8192)+((x+y*57)&8191)];
}	

void CTextureFactory::InitNoiseBuffer() {
	if(NoiseBufferInitialized) {
		return;
	}

	NoiseBuffer = new float[4*8192];
	for(int octave=0; octave<4; octave++) {
		for(int i=0;i<8192;i++) {
			NoiseBuffer[octave*8192+i] = Noise(i, octave);
		}
	}
	NoiseBufferInitialized = true;
}

float CTextureFactory::Noise(int seed, int octave) {
	int id=octave&3;
    int n =(seed<<13)^seed;
			
	if (id==0) return (float)(1.0f- ((n * (n * n * 15731 + 789221) + 1376312589)&0x7FFFFFFF)*0.000000000931322574615478515625f);
	if (id==1) return (float)(1.0f- ((n * (n * n * 12497 + 604727) + 1345679039)&0x7FFFFFFF)*0.000000000931322574615478515625f);
	if (id==2) return (float)(1.0f- ((n * (n * n * 19087 + 659047) + 1345679627)&0x7FFFFFFF)*0.000000000931322574615478515625f);
	return (float)(1.0f- ((n * (n * n * 16267 + 694541) + 1345679501)&0x7FFFFFFF)*0.000000000931322574615478515625f);
}

float CTextureFactory::Perlin2d(float x, float y, float wavelength, float persistence, int samples) {
	float sum=0;
	float freq=1.0f/wavelength;
	float amp=persistence;
	float range=0;
	
	for (int i=0;i<samples;i++) {
		sum+=amp*InterpolatedNoise(x*freq,y*freq,i); // interpolated noise

		range+=amp;
		amp*=persistence;
		freq*=2;
	}
	return Crop<float>(sum/persistence*0.5f+0.5f,0,1);
}

CTexture CTextureFactory::Perlin(int w, int h, float persistency, float density, int samples, int scale) {
	InitNoiseBuffer();
	CTexture t(w,h);
	//int pos=0;
	float wavelength=(float)((w>h)?w:h)/density;
	
	int* data = new int[w*h];

	for(int y=0;y<h;y++) {
		for(int x=0;x<w;x++) {
			int pixel =(int)((float)scale*Perlin2d((float)x,(float)y,wavelength,persistency,samples));
			data[y*w+x] = pixel;
		}
	}

	t.Put(data);
	
	delete[] data;
	return t;
}

CTexture CTextureFactory::Wave(int w, int h, float persistency, float density, int samples, int scale) {
	InitNoiseBuffer();
	CTexture t(w,h);
	//int pos = 0;
	float wavelength = (float)((w>h)?w:h)/density;
	
	int* data = new int[w*h];

	for(int y=0;y<h;y++) {
		for(int x=0;x<w;x++) {
			int pixel =(int)((float)scale*(math.sin(32*Perlin2d((float)x,(float)y,wavelength,persistency,samples))*0.5+0.5));
			data[y*w+x] = pixel;
		}
	}
			
	t.Put(data);

	delete[] data;
	return t;
}


CTexture CTextureFactory::Sky(int w, int h,float density) {
	int colors[2];
	colors[0]=0x003399;
	colors[1]=0xFFFFFF;

	int* grad = CColor::MakeGradient(colors,2,1024);
	CTexture ret = Perlin(w,h, 0.5f, 2.8f*density, 8, 1024);
	ret.Colorize(grad,1023);

	delete[] grad;
	return ret;
}

CTexture CTextureFactory::Marble(int w, int h, float density) {
	/*
		int[] colors=new int[3];
			colors[0]=0x111111;
			colors[1]=0x696070;
			colors[2]=0xFFFFFF;
			return WAVE(w,h,0.5f,0.64f*density,6,1024).colorize(
				idx3d_Color.makeGradient(colors,1024));
				*/
	int colors[3];
	colors[0] = 0x111111;
	colors[1] = 0x696070;
	colors[2] = 0xFFFFFF;
	
	int* grad = CColor::MakeGradient(colors,3,1024);
	CTexture ret = Wave(w,h,0.5f,0.64f*density, 6,1024);
	ret.Colorize(grad, 1023);
	delete[] grad;
	return ret;
}

CTexture CTextureFactory::Wood(int w, int h, float density) {
	int colors[3];
	colors[0]=0x332211;
	colors[1]=0x523121;
	colors[2]=0x996633;		
			
	CTexture ret = Grain(w,h, 0.5f, 3.0f*density, 3, 8, 1024);
	int* grad = CColor::MakeGradient(colors,3,1024);
	ret.Colorize(grad, 1023);

	delete[] grad;
	return ret;
}

CTexture CTextureFactory::CheckerBoard(int w, int h, int cellbits, CColor oddColor, CColor evenColor) {
	CTexture t(w,h);
	int iEvenColor = evenColor.ToInt();
	int iOddColor = oddColor.ToInt();
	int* colors = new int[w*h];

	int pos=0;
	for (int y=0;y<h;y++) {
		for (int x=0;x<w;x++) {
			colors[pos++] = (((x>>cellbits)+(y>>cellbits))&1)==0 ? iEvenColor : iOddColor;
		}
	}

	t.Put(colors);
	delete[] colors;
	return t;
}

CTexture CTextureFactory::Gradient(int w, int h, int* colors, int numcolors,float density) {			
	CTexture ret = Grain(w,h, 0.5f, 3.0f*density, 3, 8, 1024);
	int* grad = CColor::MakeGradient(colors,numcolors,1024);
	ret.Colorize(grad, 1023);
	delete[] grad;

	return ret;
}

CTexture CTextureFactory::CheckerBoard(int w, int h, int cellbits, int oddcolor, int evencolor) {
	return CheckerBoard(w,h,cellbits, CColor(oddcolor), CColor(evencolor));
}
CTexture CTextureFactory::Grain(int w, int h, float persistency, float density, int samples, int levels, int scale) {
	InitNoiseBuffer();
	CTexture t(w,h);
	int pos = 0;
	float wavelength = (float)((w>h)?w:h)/density;
	float perlin;

	int* pixels = new int[w*h];
	
	for(int y=0;y<h;y++) {
		for(int x=0;x<w;x++) {
			perlin=(float)levels*Perlin2d((float)x,(float)y,wavelength,persistency,samples);
			pixels[pos++] = (int)((float)scale*(perlin-(float)(int)perlin));
		}
	}

	t.Put(pixels);
	delete[] pixels;
	return t;
}