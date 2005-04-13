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


#ifndef __CACTUS_CCOLOR_H
#define __CACTUS_CCOLOR_H

class CACTUS_API CColor {
	public:
		CColor(unsigned char red,unsigned char green, unsigned char blue);
		CColor();
		CColor(int colcode);
		CColor(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);

		inline unsigned char GetRed();
		inline unsigned char GetBlue();
		inline unsigned char GetGreen();
		inline unsigned char GetAlpha();
		void SetRed(unsigned char red);
		void SetGreen(unsigned char green);
		void SetBlue(unsigned char blue);
		void SetAlpha(unsigned char alpha);
		void MixWith(CColor& c);
		inline int ToInt() {
			return (_red<<16)|(_green<<8)|_blue;
		}

		inline void Reset() {
			_blue = 0;
			_red = 0;
			_green = 0;
			_alpha = 0;
		}

		static inline CColor Medium(CColor& a, CColor& b, CColor& c) {
			CColor ret;
			ret._blue = (unsigned char)((a._blue+b._blue+c._blue)/3);
			ret._green = (unsigned char)((a._green+b._green+c._green)/3);
			ret._red = (unsigned char)((a._red+b._red+c._red)/3);
			ret._alpha = (unsigned char)((a._alpha+b._alpha+c._alpha)/3);
			return ret;
		}

		static int* MakeGradient(int* colors, int numcolors, int size) {
			int* pal = new int[size];
			int c1, c2, pos1, pos2, range;
			int r,g,b,r1,g1,b1,r2,g2,b2,dr,dg,db;

			if(numcolors==1) {
				c1 = colors[0];
				for(int i=0;i<size;i++) {
					pal[i] = c1;
					return pal;
				}
			}

			for(int c=0;c<numcolors-1;c++) {
				c1 = colors[c];
				c2 = colors[c+1];
				pos1 = size*c/(numcolors-1);
				pos2 = size*(c+1)/(numcolors-1);
				range = pos2-pos1;
				r1 = INT_GETRED(c1)<<16;
				g1 = INT_GETGREEN(c1)<<16;
				b1 = INT_GETBLUE(c1)<<16;
				r2 = INT_GETRED(c2)<<16;
				g2 = INT_GETGREEN(c2)<<16;
				b2 = INT_GETBLUE(c2)<<16;
				dr=(r2-r1)/range;
				dg=(g2-g1)/range;
				db=(b2-b1)/range;
				r=r1;  g=g1;  b=b1;
				
				for(int i=pos1;i<pos2;i++) {
					pal[i]= CColor(r>>16,g>>16,b>>16).ToInt();
					r+=dr;  g+=dg;  b+=db;
				}
			}

			return pal;
		}

		static inline CColor Scale(CColor& a, int factor) {
			if (factor==0) return CColor(0,0,0);
			if (factor==255) return a;
			
			int r = (a._red*factor)/255;
			int g = (a._green*factor)/255;
			int b = (a._blue*factor)/255;

			return CColor(r,g,b,a._alpha);
		}

		static inline int Scale(int &color, int factor) {
			if (factor==0) return 0;
			if (factor==255) return color;
			if (factor==127) return (color&0xFEFEFE)>>1;
			
			int r=(((color>>16)&255)*factor)>>8;
			int g=(((color>>8)&255)*factor)>>8;
			int b=((color&255)*factor)>>8;
			return ALPHA|(r<<16)|(g<<8)|b;
		}

		static inline CColor Multiply(CColor& a, CColor& b) {
			if(a._red+a._blue+a._green==0) {
				return CColor(0,0,0);
			}

			if(b._red+b._blue+b._green==0) {
				return CColor(0,0,0);
			}
			
		
			int r = (a._red*b._red)/255;
			int g = (a._green*b._green)/255;
			int bl = (a._blue*b._blue)/255;
			int al = (a._alpha*b._alpha)/255;

			return CColor(r,g,bl,al);
		}

		static inline int Multiply(int& color1, int& color2) {
			if ((color1&RGB)==0) return 0;
			if ((color2&RGB)==0) return 0;
			int r=(((color1>>16)&255)*((color2>>16)&255))>>8;
			int g=(((color1>>8)&255)*((color2>>8)&255))>>8;
			int b=((color1&255)*(color2&255))>>8;
			return ALPHA|(r<<16)|(g<<8)|b;
		}

		static inline CColor Add(CColor& a, CColor& b) {
			int ret = Add(a.ToInt(),b.ToInt());
			return CColor(ret);
		}

		static int Add(int ca, int cb) {
			int pixel=(ca&MASK7Bit)+(cb&MASK7Bit);
			int overflow=pixel&0x1010100;
			overflow=overflow-(overflow>>8);
			return ALPHA|overflow|pixel;
		}

		static CColor Invert(CColor& a) {
			CColor ret;
			ret._alpha = a._alpha;
			ret._blue = (unsigned char)255-a._blue;
			ret._green = (unsigned char)255-a._green;
			ret._red = (unsigned char)255-a._red;

			return ret;
		}

		void Invert();

		static CColor Sub(CColor& a, CColor& b) {
			CColor ret;
			ret._blue = a._blue-b._blue;
			ret._green = a._green-b._green;
			ret._red = a._red-b._red;

			if(ret._blue<0) {
				ret._blue = 0;
			}
			if(ret._green<0) {
				ret._green = 0;
			}
			if(ret._green<0) {
				ret._green = 0;
			}

			return ret;
		}

		static int Sub(int &a, int &b) {
			int pixel=(a&MASK7Bit)+(~b&MASK7Bit);
			int overflow=~pixel&0x1010100;
			overflow=overflow-(overflow>>8);
			return ALPHA|(~overflow&pixel);
		}

		inline void operator=(CColor &color){
			_green = color._green;
			_red = color._red;
			_blue = color._blue;
			_alpha = color._alpha;
		}

		inline bool operator==(CColor &color){
			return 
				(_green == color._green) &&
				(_red == color._red) &&
				(_blue == color._blue) &&
				(_alpha == color._alpha);
		}

		static inline int Transparency(int& bkgrd, int& color, int alpha) {
			if (alpha==0) return color;
			if (alpha==255) return bkgrd;
			
			int r=(alpha*(((bkgrd>>16)&255)-((color>>16)&255))>>8)+((color>>16)&255);
			int g=(alpha*(((bkgrd>>8)&255)-((color>>8)&255))>>8)+((color>>8)&255);
			int b=(alpha*((bkgrd&255)-(color&255))>>8)+(color&255);
			
			return ALPHA|(r<<16)|(g<<8)|b;
		}

		static inline void Transparency(CColor& back, CColor& front, CColor& target) {
			register int alpha = target._alpha;
			
			if(alpha==0) {
				target = front;
				return;
			}
			if(alpha==255) {
				target = back;
				return;
			}			
			
			int ialpha = 256 - alpha;

			target._red = (back._red*alpha + front._red*ialpha) >>8;
			target._green = (back._green*alpha + front._green*ialpha) >>8;
			target._blue = (back._blue*alpha + front._blue*ialpha) >>8;
			
		}

		unsigned char _red;
		unsigned char _green;
		unsigned char _blue;
		unsigned char _alpha;
};

#endif