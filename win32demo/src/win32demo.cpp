#include "../resource.h"
#include "../include/win32demo.h"

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd) {	
	// create scene
	CScene* scene;
	scene = InitScene();
	CCamera camera;
	camera.SetPos(0,0,-10);
	camera.LookAt(0.0f,0.0f,0.0f);
	
	// speed tweak
	CFPUTweak t;

	CSDLViewer viewer(640,480,false,scene,&camera);
	viewer.Draw();
	viewer.Run();
	
	// clean up
	delete scene;
	return 0;
}

LRESULT CALLBACK windowProc(HWND hwnd,UINT msg, WPARAM wParam, LPARAM lParam) {
	CGDIViewer* viewer = (CGDIViewer*) GetWindowLong(hwnd,GWL_USERDATA);

	return viewer->Message(hwnd,msg,wParam,lParam);
}

CScene* InitScene() {
	CScene* sc = new CScene();

	CObjectFactory f;
	CTextureFactory sf;
	CTexture t = CFileLoader::LoadTextureFromResource(GetModuleHandle(NULL),IDB_CHROME);
	CLWOImporter lwo;

	CObject* torus = f.TorusKnot(5,4,0.28f,1.2f,0.48f,0.8f,90,8);

	torus->GetMaterial()->SetColor(CColor(0,100,0,0));
	torus->GetMaterial()->SetMode(PHONG|ENVMAP);
	torus->GetMaterial()->SetReflectivity(100);
	torus->GetMaterial()->SetTransparency(75);
	torus->GetMaterial()->SetEnvMap(t);
	sc->AddObject(torus);

	CObject* hf = f.Field3D(10,0.5f);
	hf->GetMaterial()->CopyFrom(torus->GetMaterial());
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
