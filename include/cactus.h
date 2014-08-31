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

---------------------------------------------------------------------------------------------------------------------------------------------------
I want to thank:
- Peter Walser, for sharing his famous idx3d-engine for Java with the whole world.
- .oisyn, for providing various tips on 3D-engines.
- All people from Tweakers.net and Gathering of Tweakers' /14 forum (Programming & Webscripting).
- All people from flipcode.com, for posting their handy COTD's
- The OGRE project (http://ogre.sf.net), for their excellent work (some ideas have been 'borrowed' from OGRE)
- Jure Lebar, for CPostBlur,CLWOImporter and some other things

I didn't write this whole engine by myself, it is based on the work of Peter Walser (as listed above). The engine
uses amost the same techniques (with a few optimizations though ;-)) and you will see that this library can be 
used the same way as you would use his engine. Underneath is a quote, which I found in each sourcefile of mr.
Walser, which I think would be nice to put here:

"On the eight day, God started debugging...."

Classnames are not the same as in idx3dIII: a classname like 'idx3d_Object' is converted to 'CObject'.
Function names are mostly the same, except that most of them start with an uppercase character,
such that	idx3d_Matrix.rotateSelf becomes CMatrix.RotateSelf.
--------------------------------------------------------------------------------------------------------------------------------------------------- */
  
#define CACTUS_VERSION "Cactus DLL v1.7.0"
//#define PI 3.1415926535897932384626433832795028841971693 
//#undef PI
#define PI 3.141

// ---------------------------------------------------------------------------------------------------------------------------------------------------
// This is a block of code that enables us to use this headerfile both when we compile the library and when we use it in another
// application. This is very useful though. All functions that need to be exported must be defined with CACTUS_API.
// ---------------------------------------------------------------------------------------------------------------------------------------------------

#ifdef __MACH__
    #define CACTUS_API
#else
    #ifdef CACTUS_EXPORTS
        #define CACTUS_API __declspec(dllexport)
    #else
        #define CACTUS_API __declspec(dllimport)
    #endif
#endif

// system includes
#include <assert.h>
#include <memory.h>
#include <vector>
#include <math.h>
#include "linked_list.h"

//#define USE_OPTIMIZATIONS
#define USE_LUT

#ifdef USE_OPTIMIZATIONS
#include "OptimizedMath.h"
#endif


namespace cactus {
	// ---------------------------------------------------------------------------------------------------------------------------------------------------
	// Class declarations, so that one class can use another without changing the order of definition
	// ---------------------------------------------------------------------------------------------------------------------------------------------------
	class CMatrix;
	class CVector;
	class CTriangle;
	class CCanvas;
	class CColor;
	class CCamera;
	class CObject;
	class CScene;
	class CRenderer;
	class CRasterizer;
	class CLightmap;

	// Post effect classes
	class CPostEffect;
	class CPostGrayscale;
	class CPostReplaceColor;
	class CPostNegator;
	class CPostBlur;
	class CPreEffect;
	class CPreSubtract;

	// cactus includes
	#include "ColorMacros.h"
	#include "TweakFPU.h"
	#include "Constants.h"
	#include "Inlines.h"
	#include "CMath.h"

	#include "CColor.h"
	#include "CPostEffect.h"
	#include "CPostGrayscale.h"
	#include "CPostReplaceColor.h"
	#include "CPostNegator.h"
	#include "CPreSubtract.h"
	#include "CPostBlur.h"
	#include "CMatrix.h"
	#include "CVector.h"
	#include "CVertex.h"
	#include "CEdge.h"
	#include "CTriangle.h"
	#include "CTexture.h"
	#include "CMaterial.h"
	#include "CObject.h"
	#include "CObjectFactory.h"
	#include "CBuffer.h"
	#include "CCanvas.h"
	#include "CLight.h"
	#include "CLightmap.h"
	#include "CRasterizer.h"
	#include "CRenderer.h"
	#include "CScene.h"
	#include "CCamera.h"
	#include "CTextureProjector.h"
	#include "CTextureFactory.h"
	#include "CSpline.h"	

	// importers
	#include "CLWOImporter.h"
}
