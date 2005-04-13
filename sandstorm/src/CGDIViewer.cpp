#include "../include/Sandstorm.h"

CGDIViewer::CGDIViewer() {
	_hwnd = 0;
	_oldUserData = 0;
	_onCloseQuit = false;
	_scene = 0;
	_canvas = 0;
	_camera = 0;
	_autoRotation = false;
	_mouseDrags = false;
	_showFPS = false;
	_allowKeys = false;
	memset(fpsb,0,10);
	fps_index = 0;
	_antialias = false;
	_postEffect = 0;
	_preEffect = 0;
	_postEffectEnabled = false;
	_preEffectEnabled = false;
}

CGDIViewer::~CGDIViewer() {
	if(_hwnd!=0) {
		::SetWindowLong(_hwnd,GWL_USERDATA,_oldUserData);
		::DestroyWindow(_hwnd);
		_hwnd = 0;
	}

	if(_canvas!=0) {
		delete _canvas;
		_canvas = 0;
	}

	_camera = 0;
}



CScene* CGDIViewer::GetScene() {
	return _scene;
}

void CGDIViewer::SetMouseDrags(bool md) {
	_mouseDrags = md;
}

void CGDIViewer::SetAllowKeys(bool k) {
	_allowKeys = k;
}

void CGDIViewer::SetShowFPS(bool f) {
	_showFPS = f;
}

void CGDIViewer::SetAutoRotation(bool autor) {
	_autoRotation = autor;
}

void CGDIViewer::SetOnClose(bool exit) {
	_onCloseQuit = exit;
}

void CGDIViewer::SetPostEffect(CPostEffect* ef) {
	_postEffect = ef;
	if(ef==0) {
		_postEffectEnabled = false;
	}
}

void CGDIViewer::SetPostEffectEnabled(bool en) {
	_postEffectEnabled = en;
}

void CGDIViewer::SetPreEffect(CPreEffect* ef) {
	_preEffect = ef;
	if(ef==0) {
		_preEffectEnabled = false;
	}
}

void CGDIViewer::SetPreEffectEnabled(bool en) {
	_preEffectEnabled = en;
	_canvas->SetDisableClear(en);
}

LRESULT CGDIViewer::KeyUp(WPARAM wParam, LPARAM lParam) {
	if(_allowKeys) {
		switch(wParam) {
			case VK_TAB:
				_showFPS = !_showFPS;
				break;
			case VK_ESCAPE:
				Close();
				break;
			case VK_F2:
				if(_scene!=0) {
					_scene->SetAllMaterialMode(PHONG|ENVMAP|WIREFRAME);
				}
				break;
			case VK_F3:
				if(_scene!=0) {
					_scene->SetAllMaterialMode(FLAT);
				}
				break;
			case VK_F4:
				if(_scene!=0) {
					_scene->SetAllMaterialMode(PHONG);
				}
				break;
			case VK_F5:
				if(_scene!=0) {
					_scene->SetAllMaterialMode(PHONG|ENVMAP);
				}
				break;
			case VK_F6:
				if(_scene!=0) {
					_scene->SetAllMaterialMode(PHONG|ENVMAP|TEXTURED);
				}
				break;
			case VK_F7:
				SetPostEffectEnabled (!_postEffectEnabled);
				break;
			case 0x41:
				_autoRotation = !_autoRotation;
			}
		}
		return 0;
}

LRESULT CGDIViewer::KeyDown(WPARAM wParam, LPARAM lParam) {
	if(_allowKeys) {
		switch(wParam) {
			case VK_UP:
				if(_scene!=0) {
					_scene->Rotate(-0.1f,0.0f,0.0f);
				}
				break;
			case VK_DOWN:
				if(_scene!=0) {
					_scene->Rotate(0.1f,0.0f,0.0f);
				}
				break;
			case VK_LEFT:
				if(_scene!=0) {
					_scene->Rotate(0.0f,0.1f,0.0f);
				}
				break;
			case VK_RIGHT:
				if(_scene!=0) {
					_scene->Rotate(0.0f,-0.1f,0.0f);
				}
				break;
			case 0x58:
				if(_scene!=0) {
					_scene->Scale(1.1f);
				}
				break;
			case 0x5A:
				if(_scene!=0) {
					_scene->Scale(0.9f);
				}
				break;
			case 0x46:
				_camera->SetFov(_camera->GetFov()+10);
				break;
			case 0x47:
				_camera->SetFov(_camera->GetFov()-10);
				break;
			case 0x45:
				_postEffectEnabled = !_postEffectEnabled;
				break;
			case 0x40:
				_autoRotation = !_autoRotation;
				break;
			case 0x56:
				SetPreEffectEnabled(!_preEffectEnabled);
		}
	}

	return 0;
}

LRESULT CGDIViewer::Message(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT ps;
	HDC dc;

	switch(msg) {
	case WM_CREATE:
		return 0;
	case WM_DESTROY:
		if(_onCloseQuit) {
			PostQuitMessage(0);
		}
		return 0;
	case WM_KEYUP:
		return KeyUp(wParam,lParam);
		break;
	case WM_KEYDOWN:
		return KeyDown(wParam,lParam);
		break;
	case WM_MOUSEMOVE:
		if(_mouseDrags) {
			if(wParam==MK_LBUTTON) {
				POINTS f;
				f = MAKEPOINTS(lParam);
				
				float dx = (float)(f.y-oldy)/50;
				float dy = (float)(oldx-f.x)/50;

				oldx = f.x;
				oldy = f.y;

				_scene->Rotate(dx,dy,0);
			}
			else if(wParam==MK_RBUTTON) {
				POINTS f;
				f = MAKEPOINTS(lParam);

				if(f.y<oldy) {
					_scene->Scale(1.1f);
				}
				else if(f.y>oldy) {
					_scene->Scale(0.9f);
				}
				else {
					// nothing
				}
				oldx = f.x;
				oldy = f.y;
			}
			else {
			}
		}
		return 0;
		break;
	case WM_PAINT:
		if(_canvas!=0&&_scene!=0) {
				DWORD time = GetTickCount();
				if(_preEffectEnabled) {
					_canvas->ApplyEffect(_preEffect);
				}

				_scene->Render(_canvas,_camera);

				if(_postEffectEnabled) {
					_canvas->ApplyEffect(_postEffect);
				}	

				dc = BeginPaint(hwnd,&ps);
				// paint here
				HDC bitmapDC = CreateCompatibleDC(dc);
				SelectObject(bitmapDC, BitmapBuffer);  
					
	
				if(_antialias) {
					SetStretchBltMode(dc,HALFTONE);
					SetBrushOrgEx(dc,0,0,0);
					StretchBlt(dc,0,0,200,200,bitmapDC,0,0,_canvas->GetWidth(),_canvas->GetHeight(),SRCCOPY);
				}
				else {
					BitBlt(dc,0,0,_canvas->GetWidth(),_canvas->GetHeight(), bitmapDC,0,0,SRCCOPY); //of what BLITTER dan ook) 
				}

				DeleteObject(bitmapDC);

				DWORD time2 = (GetTickCount()-time);

				// frame time counter
				if(fps_index==9) {
					fps_index = 0;
				}
				else {
					fps_index++;
				}
				fpsb[fps_index] = time2;

				if(_showFPS) {
					// calculate FPS
					DWORD sum = fpsb[1]+fpsb[2]+fpsb[3]+fpsb[4]+fpsb[5]+fpsb[6]+fpsb[7]+fpsb[8]+ fpsb[9];
					DWORD fps = 10000/(sum!=0?sum:1);
					//fps = sum;
					char buffer[33];
					itoa(fps,buffer,10);
					TextOut(dc,10,10,buffer,strlen(buffer));
				}			
				EndPaint(hwnd,&ps);
				return 0;
		}
		else {
			dc = BeginPaint(hwnd,&ps);
			TextOut(dc,10,10,"Cactus 3D Engine - Initializing...",34);
			EndPaint(hwnd,&ps);
		}
	default:
		return DefWindowProc(hwnd,msg,wParam,lParam);
	}
}

void CGDIViewer::SetTitle(const char* title) {
	if(_hwnd!=0) {
		SetWindowText(_hwnd,title);
	}
}

void CGDIViewer::Repaint() {
	RECT rect;
	rect.bottom = _canvas->GetHeight();
	rect.top = 0;
	rect.left = 0;
	rect.right = _canvas->GetWidth();

	if(_autoRotation) {
		_scene->Rotate(0.05f,0.05f,0.05f);
	}
	InvalidateRect(_hwnd,&rect,FALSE);
}

void CGDIViewer::Show(int show) {
	if(_hwnd!=0) {
		::ShowWindow(_hwnd,show);
	}
}

void CGDIViewer::Destroy() {
	if(_hwnd!=0) {
		::SetWindowLong(_hwnd,GWL_USERDATA,_oldUserData);
		::DestroyWindow(_hwnd);
	}
}

void CGDIViewer::Close() {
	if(_hwnd!=0) {
		::CloseWindow(_hwnd);
	}
}

void CGDIViewer::SetAntialias(bool aa) {
	_antialias = aa;
}

void CGDIViewer::SetHWND(HWND hwnd,int w, int h, int x, int y,CScene* scene, CCamera* camera) {
	::SetWindowLong(_hwnd,GWL_USERDATA,_oldUserData);

	_hwnd = hwnd;
	_scene = scene;
	_camera = camera;
	_oldUserData = ::SetWindowLong(hwnd,GWL_USERDATA,(long)this);

	::SetWindowPos(_hwnd,0,x,y,w,h,0);
	if(_scene!=0) {
		_scene->SetSize(h,w);
	}

	_canvas = new CCanvas(w,h);

	bmInfo = (BITMAPINFO*)new BYTE[sizeof(BITMAPINFO)+256*4]; 
	bmInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
	bmInfo->bmiHeader.biWidth = w; //desired width 
	bmInfo->bmiHeader.biHeight = -h; //height 
	bmInfo->bmiHeader.biPlanes = 1; //has to be 1 
	bmInfo->bmiHeader.biBitCount = 32; 
	bmInfo->bmiHeader.biCompression = BI_RGB; //uncompressed 
	bmInfo->bmiHeader.biSizeImage = 0; 
	bmInfo->bmiHeader.biClrImportant = 0; 
	bmInfo->bmiHeader.biClrUsed = 0; 
	bmInfo->bmiHeader.biXPelsPerMeter = 0; 
	bmInfo->bmiHeader.biYPelsPerMeter = 0; 
	BitmapBuffer = CreateDIBSection(NULL, bmInfo, DIB_RGB_COLORS, (void**)&screen, NULL, 0);
	_canvas->UseBuffer(screen);
}