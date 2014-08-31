#include <iostream>
#include <fstream>
#include "cactus.h"

using namespace cactus;

int GWidth = 1024, GHeight = 768;

CScene* InitScene() {
    CScene* sc = new CScene();
    
    sc->SetSize(GHeight, GWidth);
    sc->SetBackgroundColor(CColor(255,0,0));
    
    CObjectFactory f;
    CTextureFactory sf;
    CObject* torus = f.TorusKnot(5,4,0.28f,1.2f,0.48f,0.8f,90,8);
    
    torus->GetMaterial()->SetColor(CColor(0,100,0));
    torus->GetMaterial()->SetMode(PHONG);
    torus->GetMaterial()->SetReflectivity(100);
    torus->GetMaterial()->SetTransparency(75);
    //torus->GetMaterial()->SetEnvMap(t);
    sc->AddObject(torus);
    
    CObject* hf = f.Field3D(10,0.5f);
    hf->GetMaterial()->CopyFrom(torus->GetMaterial());
    hf->GetMaterial()->SetMode(WIREFRAME);
    hf->GetMaterial()->SetColor(CColor(255,100,0));
    
    hf->Scale(3.0f,3.0f,3.0f);
    sc->AddObject(hf);
    
    CLight* light = new CLight();
    light->SetDirection(CVector(0.0f,0.0f,100.0f));
    light->highlightSheen = 144;
    light->highlightSpread = 120;
    light->diffuse = CColor(255,255,255);
    light->specular  = CColor(255,255,255);
    sc->AddLight(light);
    
    return sc;
}

int main(int argc, const char * argv[]) {
    CScene* scene = InitScene();
    
    CCamera camera;
    camera.SetPos(0,0,-5);
    camera.LookAt(0.0f,0.0f,0.0f);
    
    CCanvas canvas(GWidth, GHeight);
    scene->Render(&canvas, &camera);
    
    // Write PPM
    std::ofstream ppm("test.ppm");
    ppm << "P3" << std::endl;
    ppm << GWidth << " " << GHeight << std::endl;
    ppm << "255" << std::endl;
    
    for(int y=0; y<GHeight; y++)
    {
        for(int x=0; x<GWidth; x++)
        {
            CColor pixel = canvas.At(x,y);
            ppm << (int)pixel.GetRed() << " " << (int)pixel.GetGreen() << " " << (int)pixel.GetBlue() << " ";
        }
        
        ppm << std::endl;
    }
    return 0;
}
