/** PORT STATUS: all methods implemented, except for methods that load material info from file.
Needs the Texture class to be implemented. **/

#ifndef __DDENGINE_MATERIAL_H
#define __DDENGINE_MATERIAL_H

#include "Math.h"

class Texture;
class TextureSettings;

class Material {
	public:
		Material();
		Material(int color);
		Material(Texture* t);
		virtual ~Material();
		int color;
		int transparency;
		int reflectivity; // = 255 by default, implement that
		Texture* texture;
		Texture* envmap;
		bool flat; // false by default
		bool wireframe; // false by default
		bool opaque; // true by default
		// String texturepath
		// String envmappath
		TextureSettings* textureSettings;
		TextureSettings* envmapSettings;
        
        // methods
        void setTexture(Texture* tex);
        void setEnvMap(Texture* map);
        void setColor(int color);
        void setTransparency(int factor);
        void setReflectivity(int factor);
        void setFlat(bool flat);
        void setWireframe(bool wf);
        Texture* getTexture();
        Texture* getEnvMap();
        int getColor();
        int getTransparency();
        int getReflectivity();
        bool isFlat();
        bool isWireframe();
        
};

#endif
