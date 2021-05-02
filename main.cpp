#include <iostream>
#include <fstream>
#include "include/cactus.h"

#include <SDL/SDL.h>
#ifdef __EMSCRIPTEN__
    #include <emscripten.h>
#endif

using namespace cactus;

int GWidth = 512, GHeight = 512;

CScene* InitScene() {
    CScene* sc = new CScene();
    
    sc->SetSize(GHeight, GWidth);
    sc->SetBackgroundColor(CColor(255,0,0));
    
    CObjectFactory f;
    CTextureFactory sf;
    CObject* torus = f.TorusKnot(5,4,0.28f,1.4f,0.48f,0.8f,190,30);
    
    torus->GetMaterial()->SetColor(CColor(0,100,0));
    torus->GetMaterial()->SetMode(FLAT|WIREFRAME);
    torus->GetMaterial()->SetReflectivity(100);
    torus->GetMaterial()->SetTransparency(55);
    //torus->GetMaterial()->SetEnvMap(t);
    sc->AddObject(torus);

	CObject* cube = f.Cube(1.0, 1.0, 1.0);
	cube->GetMaterial()->CopyFrom(torus->GetMaterial());
	cube->GetMaterial()->SetMode(PHONG);
	cube->GetMaterial()->SetColor(CColor(0,55,100));
	//cube->Scale(2.0);
	//cube->Rotate(0.5, 0.5, 0.5);
	//cube->SetPos(0.0, 0.5, 0.5);
	sc->AddObject(cube);
    
    CObject* hf = f.Field3D(10,0.5f);
    hf->GetMaterial()->CopyFrom(torus->GetMaterial());
    hf->GetMaterial()->SetMode(WIREFRAME);
    hf->GetMaterial()->SetColor(CColor(236,0,0));
    hf->Scale(3.0f,3.0f,3.0f);
    sc->AddObject(hf);

	CObject* hfb = f.Field3D(20,2.0f);
	hfb->GetMaterial()->CopyFrom(torus->GetMaterial());
	hfb->GetMaterial()->SetMode(PHONG);
	hfb->GetMaterial()->SetColor(CColor(255,204,0));
	hfb->Scale(2.0f,2.0f,1.0f);
	hfb->Rotate(0.5f, 0.5f, 1.0f);
	sc->AddObject(hfb);
    
    CLight* light = new CLight();
    light->SetDirection(CVector(0.0f,0.0f,100.0f));
    light->highlightSheen = 200;
    light->highlightSpread = 120;
    light->diffuse = CColor(255,255,255);
    light->specular  = CColor(255,255,255);
    sc->AddLight(light);
    
    return sc;
}

struct Context {
    CCanvas* canvas;
    CCamera* camera;
    CScene* scene;
    SDL_Surface* screen;
    unsigned int frames;
    unsigned int ms;
};

void loop(void* arg) {
    Context* ctx = reinterpret_cast<Context*>(arg);
    ctx->scene->Render(ctx->canvas, ctx->camera);

    if (SDL_MUSTLOCK(ctx->screen)) {
        SDL_LockSurface(ctx->screen);
    }

    for(int y = 0; y < GHeight; y++) {
        for(int x = 0; x < GWidth; x++) {
            CColor pixel = ctx->canvas->At(x,y);
            *((Uint32*)ctx->screen->pixels + y * GWidth + x) = SDL_MapRGBA(ctx->screen->format, pixel.GetRed(), pixel.GetGreen(), pixel.GetBlue(), 255);
        }
    }

    if (SDL_MUSTLOCK(ctx->screen)) {
        SDL_UnlockSurface(ctx->screen);
    }
    SDL_Flip(ctx->screen); 
    ctx->scene->Rotate(0.05, 0.03, 0.01);
    ctx->frames++;

    if((ctx->frames % 100) == 0) {
        unsigned int now = SDL_GetTicks();
        unsigned int time = now - ctx->ms;
        float fps = ((float)ctx->frames) / time  * 1000.0;
        printf("%d frames, %d ms, %f frames/sec\n", ctx->frames, time, fps);
    }
}

int main(int argc, const char * argv[]) {
    CScene* scene = InitScene();
    
    CCamera* camera = new CCamera();
    camera->SetPos(0,0,-5);
    camera->LookAt(0.0f,0.0f,0.0f);
    
    CCanvas* canvas = new CCanvas(GWidth, GHeight);

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *screen = SDL_SetVideoMode(GWidth, GHeight, 32, SDL_SWSURFACE);
    
    Context* ctx = new Context;
    ctx->screen = screen;
    ctx->camera = camera;
    ctx->scene = scene;
    ctx->canvas = canvas;
    ctx->frames = 0;
    ctx->ms = SDL_GetTicks();

    emscripten_set_main_loop_arg(loop, ctx, -1, 0);
    
    // Write PPM
    /*std::cout << "P3" << std::endl;
    std::cout << GWidth << " " << GHeight << std::endl;
    std::cout << "255" << std::endl;
    
    for(int y=0; y<GHeight; y++)
    {
        for(int x=0; x<GWidth; x++)
        {
            CColor pixel = canvas.At(x,y);
            std::cout << (int)pixel.GetRed() << " " << (int)pixel.GetGreen() << " " << (int)pixel.GetBlue() << " ";
        }
        
        std::cout << std::endl;
    }
    return 0;*/
}
