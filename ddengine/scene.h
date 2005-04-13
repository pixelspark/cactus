#ifndef __DDENGINE_SCENE_H
#define __DDENGINE_SCENE_H

#include "Vector.h"

class RenderPipeline;
class Environment;

class Scene {
	public:
		Scene();
		~Scene();
		RenderPipeline* renderPipeline;
		int width,height;
		Environment* environment;
		Camera defaultCamera;
		int objects;
		int lights;
		bool objectsNeedRebuild;
		bool LightsNeedRebuild;
		bool preparedForRendering;
		Vector normalizedOffset;
		
};

#endif

