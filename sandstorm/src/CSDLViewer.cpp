// ---------------------------------------------------------------------------------------------------------------------------------------------------
// Sandstorm is the Windows Platform Layer for Cactus. It provides classes that can be used to show Cactus3d output
// to a window, without having to worry about how to load a bitmap or how to create a window.
// ---------------------------------------------------------------------------------------------------------------------------------------------------
#include "../include/Sandstorm.h"

CSDLViewer::CSDLViewer(int w, int h, bool fullscreen, CScene* sc, CCamera* cam): _canvas(w,h) {
	if(SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO)<0) {
		throw SDL_GetError();
	}

	_width = w;
	_scene = sc;
	_camera = cam;
	_height = h;
	_oldY = _height/2;
	_oldX = _width/2;
	_selectedObject = 0;
	_designMode = false;
	
	_surface = SDL_SetVideoMode(w, h, 32,SDL_HWSURFACE|(fullscreen?SDL_FULLSCREEN:0));
	if(_surface==0) {
		throw "Could not create SDL surface";
	}

	_scene->SetSize(_height,_width);
	_canvas.UseBuffer((int*)_surface->pixels);
	_canvas.SetDisableClear(true);
}

CSDLViewer::~CSDLViewer() {
	SDL_Quit();
}

bool CSDLViewer::GetDesignMode() {
	return _designMode;
}

void CSDLViewer::SetDesignMode(bool des) {
	_designMode = des;
	_scene->GetRenderer()->SetPopulateIDBuffer(des);
}

void CSDLViewer::OnMouseDrag(float dx, float dy, bool buttonDown) {
	if(buttonDown) {
		if(_selectedObject==0||!_designMode) {
			_scene->Rotate(dx/50,dy/50,0.0f);
		}
		else {
			_selectedObject->Rotate(dx/50,dy/50,0.0f);
		}
		Draw();
	}
}

bool CSDLViewer::OnQuit() {
	return true; /* Return true if we want to quit, false if we don't want to */
}

void CSDLViewer::OnWheelDown() {
	_camera->Shift(0.0f,0.0f,-0.3f);
	Draw();
}

void CSDLViewer::OnWheelUp() {
	_camera->Shift(0.0f,0.0f,0.3f);
	Draw();
}

void CSDLViewer::OnMouseClick(int x, int y) {
	if(!_designMode) return;

	CTriangle* tri = _scene->GetRenderer()->GetTriangleAt(x,y);

	if(_selectedObject!=0) {
		_selectedObject->GetMaterial()->DisableMode(WIREFRAME);
	}
	_selectedObject = 0;
	
	if(tri!=0) {
		CObject* parent = tri->GetParent();

		if(parent!=0&&_selectedObject!=parent) {
			_selectedObject = parent;
			_selectedObject->GetMaterial()->EnableMode(WIREFRAME);
		}
	}
	Draw();
}

void CSDLViewer::OnKeyDown(int key) {
	if(key==SDLK_F1) {
		_scene->ToggleAllMaterialMode(WIREFRAME);
		Draw();
	}
	else if(key==SDLK_F2) {
		_scene->ToggleAllMaterialMode(PHONG);
		Draw();
	}
	else if(key==SDLK_F3) {
		_scene->ToggleAllMaterialMode(ENVMAP);
		Draw();
	}
	else if(key==SDLK_F4) {
		_scene->ToggleAllMaterialMode(VERTICES);
		Draw();
	}
	else if(key==SDLK_F5) {
		_scene->ToggleAllMaterialMode(FLAT);
		Draw();
	}
	/* Movement */
	else if(key==SDLK_LEFT) {
		if(_selectedObject==0||!_designMode) {
			_camera->Shift(-0.3f,0.0f,0.0f);
		}
		else {
			_selectedObject->Shift(-0.3f,0.0f,0.0f);
		}
		Draw();
	}
	else if(key==SDLK_RIGHT) {
		if(_selectedObject==0||!_designMode) {
			_camera->Shift(0.3f,0.0f,0.0f);
		}
		else {
			_selectedObject->Shift(0.3f,0.0f,0.0f);
		}
		Draw();
	}
	else if(key==SDLK_UP) {
		if(_selectedObject==0||!_designMode) {
			_camera->Shift(0.0f,0.0f,0.3f);
		}
		else {
			_selectedObject->Shift(0.0f,0.0f,0.3f);
		}
		Draw();
	}
	else if(key==SDLK_DOWN) {
		if(_selectedObject==0||!_designMode) {
			_camera->Shift(0.0f,0.0f,-0.3f);
		}
		else {
			_selectedObject->Shift(0.0f,0.0f,-0.3f);
		}
		Draw();
	}
}

void CSDLViewer::Run() {
	SDL_Event event;

	LockSurface();
	while(SDL_WaitEvent(&event)) {
		if(event.type==SDL_QUIT) {
				if(OnQuit()) break;
		}
		else if(event.type==SDL_MOUSEMOTION) {
			/* Drag */
			bool state = ((SDL_GetMouseState(NULL, NULL)&SDL_BUTTON_RIGHT)>0);
			float dx = (float)(event.motion.y-_oldY);
			float dy = (float)(_oldX-event.motion.x);

			OnMouseDrag(dx,dy,state);

			_oldX = event.motion.x;
			_oldY = event.motion.y;
		}
		else if(event.type==SDL_MOUSEBUTTONDOWN) {
			if(event.button.button==SDL_BUTTON_WHEELUP) {
				OnWheelUp();
			}
			else if(event.button.button==SDL_BUTTON_WHEELDOWN) {
				OnWheelDown();
			}
			else if(event.button.button==SDL_BUTTON_LEFT) {
				OnMouseClick(event.button.x, event.button.y);
			}
		}
		else if(event.type==SDL_KEYDOWN) {
			OnKeyDown((int)event.key.keysym.sym);
		}
	}
	UnlockSurface();
}

void CSDLViewer::Draw() {
	DWORD time = GetTickCount();
	SDL_FillRect(_surface,NULL,SDL_MapRGB(_surface->format,0,0,0));
	_scene->Render(&_canvas,_camera);
	SDL_Flip(_surface);
	DWORD elapsed = GetTickCount()-time;

	if(elapsed>0) {
		char buf[33];
		itoa(1000/elapsed,buf,10);
		SDL_WM_SetCaption(buf, 0);
	}
}

void CSDLViewer::LockSurface() {
  if(SDL_MUSTLOCK(_surface)) {
    SDL_LockSurface(_surface);
  }
}

void CSDLViewer::UnlockSurface() {
  if(SDL_MUSTLOCK(_surface)) {
    SDL_UnlockSurface(_surface);
  }
}