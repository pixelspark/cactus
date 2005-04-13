/** Porting status: almost ported, the following methods really need to be ported:
-- fastRnd for calculating random int's very very fast
-- fastRndBit
**/

#ifndef __DDENGINE_MATH_H
#define __DDENGINE_MATH_H

#define PI 3.1415926535
#define RAD2SCALE (4096/PI/2)
#define PAD (256*PI)

#include <math.h>
#include <stdlib.h>
#include <time.h>

class Math {
	public:
		static float deg2rad(float deg) {
			return (float)(deg*0.0174532925194);
		}

		static float rad2deg(float rad) {
			return (float)(rad*57.295779514719);
		}

		static float pythagoras(float a,float b) {
			return (float)sqrt(a*a+b*b);
		}

		static int pythagoras(int a,int b) {
			return (int)sqrt(a*a+b*b);
		}

		static int crop(int num,int min,int max) {
			return (num<min)?min:(num>max)?max:num;
		}

		static float crop(float num,float min,float max) {
			return (num<min)?min:(num>max)?max:num;
		}

		static bool inrange(int num,int min,int max) {
			return ((num>=min)&&(num<max));
		}

		static void clearBuffer(int buffer[],int value) {
			for(int a=0;a<sizeof(buffer);a++) {
				buffer[a] = value;
			}
		}

		static void cropBuffer(int buffer[],int min,int max) {
			for(int i=sizeof(buffer)-1;i>=0;i--) {
				buffer[i] = crop(buffer[i],min,max);
			}
		}

		static void copyBuffer(int source[],int target[]) {
			for(int a=0;a<sizeof(source);a++) {
				target[a] = source[a];
			}
		}

		static float random() {
			srand(time(NULL));

			return (float)(rand()*2-1);
		}

		static float random(float min,float max) {
			return (float)(rand()*(max-min)+min);
		}

		static float randomWithDelta(float average,float delta) {
			return (float)(average+rand()*delta);
		}

		/** NOT YET IMPLEMENTED **/
		static int fastRnd(int bits) {
			return 0;
		}

		static float interpolate(float a,float b,float d) {
			float f = (float)((1-cos(d*PI))*0.5);
			return a+f*(b-a);
		}
};

#endif
