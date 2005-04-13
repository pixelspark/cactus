#ifndef __SANDSTORM__H
#define __SANDSTORM__H

#include "../../include/cactus.h"
#undef RGB
#include <windows.h>
#include <SDL.h>

using namespace cactus;

// dll thingie
#ifdef SANDSTORM_EXPORTS
	#define SANDSTORM_API __declspec(dllexport)
#else
	#define SANDSTORM_API __declspec(dllimport)
#endif

class SANDSTORM_API CDLLPostEffect: public CPostEffect {
	public:
		CDLLPostEffect(const char* dllName) {
			_module = ::LoadLibrary(dllName);
			if(_module==0) {
				throw "The library could not be loaded. Check filename.";
			}
			_proc = (void(__cdecl*)(int*,int,int)) GetProcAddress(_module,"ProcessImage");
			if(_proc==0) {
				throw "This DLL is not a compatible post effect";
			}
		}
		~CDLLPostEffect() {
			_module = 0;
			_proc = 0;
		}
	private:
		HMODULE _module;
		void (*_proc)(int*,int,int);
};

class SANDSTORM_API CLogger {
	public:
		CLogger();
		void Write(const char* str);
		void WriteError(const char* str);
		~CLogger();
		void operator <<(const char* str);
		void WriteF(const char* fmt,...);
	protected:
		HANDLE _handle;
};

class SANDSTORM_API CGDIViewer {
	public:
		CGDIViewer();
		~CGDIViewer();
		CScene* GetScene();
		void SetMouseDrags(bool md);
		void SetAllowKeys(bool k);
		void SetShowFPS(bool f);
		void SetAutoRotation(bool autor);
		void SetOnClose(bool exit);
		void SetPostEffect(CPostEffect* ef);
		void SetPostEffectEnabled(bool en);
		void SetPreEffect(CPreEffect* ef);
		void SetPreEffectEnabled(bool en);
		LRESULT KeyUp(WPARAM wParam, LPARAM lParam);
		LRESULT KeyDown(WPARAM wParam, LPARAM lParam);
		LRESULT Message(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
		void SetTitle(const char* title);
		void Repaint();
		void Show(int show);
		void Destroy();
		void Close();
		void SetAntialias(bool aa);
		void SetHWND(HWND hwnd,int w, int h, int x, int y,CScene* scene, CCamera* camera);
	protected:
		HWND _hwnd;
		LONG _oldUserData;
		bool _onCloseQuit;
		CScene* _scene;
		CCanvas* _canvas;
		CCamera* _camera;
		BITMAPINFO* bmInfo;
		HBITMAP hbm;
		HBITMAP BitmapBuffer;
		int* screen;
		bool _autoRotation;
		bool _mouseDrags;
		int oldx, oldy;
		int fps_index;
		int fpsb[10];
		bool _showFPS;
		bool _allowKeys;
		bool _antialias;
		bool _postEffectEnabled;
		bool _preEffectEnabled;
		CPostEffect* _postEffect;
		CPreEffect* _preEffect;
};


class SANDSTORM_API CWindowClass {
	public:
		CWindowClass(const char* className,WNDPROC proc) {
			::ZeroMemory(&_class,sizeof(WNDCLASSEX));
			_classRegistered = false;
			_class.lpszClassName = className;

			_class.cbClsExtra = 0;
			_class.cbSize = sizeof(WNDCLASSEX);
			_class.cbWndExtra = 0;
			_class.hbrBackground = (HBRUSH)::GetStockObject(WHITE_BRUSH);
			_class.hCursor = ::LoadCursor(NULL,IDC_ARROW);
			_class.hInstance = GetModuleHandle(NULL);
			_class.lpfnWndProc = proc;
			_class.lpszMenuName = NULL;
			_class.hIconSm = ::LoadIcon(NULL,IDI_APPLICATION);
			_class.hIcon = ::LoadIcon(NULL, IDI_APPLICATION);
			_class.hCursor = ::LoadCursor(NULL, IDC_ARROW);
			_class.style = 0;
		}

		~CWindowClass() {
			_className = 0;
		}

		void Register() {
			if(!_classRegistered) {
				::RegisterClassEx(&_class);
			}
		}

		void Create(CGDIViewer* viewer,int w, int hx, int x, int y,CScene* scene,CCamera* camera) {
			Register();

			HWND h = ::CreateWindowEx(WS_EX_STATICEDGE,_class.lpszClassName,"Uninitialized",WS_OVERLAPPEDWINDOW,CW_USEDEFAULT,CW_USEDEFAULT,640,480,NULL,NULL,NULL,NULL);
			viewer->SetHWND(h,w,hx,x,y,scene,camera);
		}

		WNDCLASSEX* operator-> () {
			return &_class; 
		}
	protected:
		WNDCLASSEX _class;
		bool _classRegistered;
		const char* _className;

};

class SANDSTORM_API CSDLViewer {
	public:
		CSDLViewer(int w, int h, bool fullscreen,CScene* scene, CCamera* camera);
		~CSDLViewer();
		void Draw();
		void Run();
		void SetDesignMode(bool des);
		bool GetDesignMode();

		/* Overloadable event functions */
		virtual void OnMouseDrag(float dx, float dy, bool buttonDown);
		virtual void OnMouseClick(int x, int y);
		virtual void OnKeyDown(int key);
		virtual bool OnQuit();
		virtual void OnWheelUp();
		virtual void OnWheelDown();

		CScene* GetScene() { return _scene; }
		CCanvas* GetCanvas() { return &_canvas; }
		CCamera* GetCamera() { return _camera; }
		CObject* GetSelectedObject() { return _selectedObject; }

	private:
		void LockSurface();
		void UnlockSurface();

		int _width, _height;
		CScene* _scene;
		CCamera* _camera;
		CCanvas _canvas;
		int _oldX, _oldY;
		CObject* _selectedObject;
		bool _designMode;

	protected:
		SDL_Surface* _surface;
};

class SANDSTORM_API CFileLoader {
	public:
		static CTexture LoadTextureFromResource(HINSTANCE hInstance, int id);
	protected:
		static HBITMAP LoadImageFromResource(HINSTANCE hInstance, const char* name);
		static HBITMAP LoadImageFromResource(HINSTANCE hInst, int id);
};

class SANDSTORM_API CMessageLoop {
	public:
		CMessageLoop() {
			ZeroMemory(&_msg,sizeof(MSG));
		}
		
		~CMessageLoop() {
		}

		void Run(CGDIViewer* v) {
			while(true) {
				if(PeekMessage(&_msg,NULL,0,0,PM_NOREMOVE)!=0) {
					if(GetMessage(&_msg,NULL,0,0) >0) {
						TranslateMessage(&_msg);
						DispatchMessage(&_msg);
					}
					else {
						return;
					}
				}
				v->Repaint();
			}
		}
	protected:
		MSG _msg;
};

#endif