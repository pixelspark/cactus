/** PORT STATUS: done? **/

#ifndef __DDENGINE_LIGHT_H
#define __DDENGINE_LIGHT_H

#include "CoreObject.h"
#include "Vector.h"
#include "Matrix.h"

class Light : public CoreObject {
	public:
		// constructors
		Light(Vector direction);
		Light(Vector direction,int diffuse);
		Light(Vector direction,int color,int highlightSheen,int highlightSpread);
		Light(Vector direction,int diffuse,int specular,int highlightSheen,int highlightSpread);
		virtual ~Light();

		// data members
		Vector v;
		Vector v2;
		int diffuse;
		int specular;
		int highlightSheen;
		int highlightSpread;
		Matrix matrix2;

		// methods
		void project(Matrix m);
};

#endif
