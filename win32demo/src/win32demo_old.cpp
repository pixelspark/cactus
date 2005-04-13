#include <fstream>
#include <iostream>

#include "../include/win32demo.h"
#include "../resource.h"
#undef WIDTH
#undef HEIGHT

// 400x300
#define WIDTH 400
#define HEIGHT 300

#define FILE_INVALID 1
#define OK 2


CScene scene;
CCamera cam;
HBITMAP hbm;
HBITMAP BitmapBuffer; //our BitMap Buffer 
int* screen; //where our Bitmap dat WILL Be (ie NOT is) 
CCanvas canvas(WIDTH,HEIGHT);
CObject* torus;
int oldx, oldy;
bool autorotation;
int fpsb[10];
int fps_index;
float scale;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
	// windows vars
	FPUTweak p;
	WNDCLASSEX windowClass;
	HWND windowHandle;
	MSG msg;

	oldx = 0;
	oldy = 0;
	scale = 1.0f;
	autorotation = true;
	fps_index = 0;
	for(int a=0;a<10;a++) {
		fpsb[a] = 0;
	}

	// build the scene
	scene.SetSize(HEIGHT,WIDTH);
	InitScene(&scene);
	cam.SetPos(0,0,-10);

	windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	windowClass.cbClsExtra = 0;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.lpfnWndProc = (WNDPROC)windowProc;
	windowClass.lpszClassName = "CactusWnd";
	windowClass.lpszMenuName = NULL;
	windowClass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.style = 0;

	if(!::RegisterClassEx(&windowClass)) {
		::MessageBox(NULL, "The window class could not be registered. Close some programs or restart your computer, it might work then.","Error", MB_OK|MB_ICONEXCLAMATION);
		return 0;
	}

	windowHandle = ::CreateWindowEx(WS_EX_STATICEDGE, windowClass.lpszClassName, "Cactus Demo", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, WIDTH, HEIGHT, NULL, NULL, hInstance, NULL);
	if(windowHandle==0) {
		::MessageBox(NULL, "The window could not be created.","Error", MB_OK|MB_ICONEXCLAMATION);
	}

	SendMessage(windowHandle,WM_SETICON,ICON_BIG,(long)LoadIcon(hInstance,MAKEINTRESOURCE(IDI_ICON)));

	int xres = WIDTH;
	int yres = HEIGHT;

	BITMAPINFO* bmInfo = (BITMAPINFO*)new BYTE[sizeof(BITMAPINFO)+256*4]; 
	bmInfo->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
	bmInfo->bmiHeader.biWidth = xres; //desired width 
	bmInfo->bmiHeader.biHeight = -yres; //height 
	bmInfo->bmiHeader.biPlanes = 1; //has to be 1 
	bmInfo->bmiHeader.biBitCount = 32; 
	bmInfo->bmiHeader.biCompression = BI_RGB; //uncompressed 
	bmInfo->bmiHeader.biSizeImage = 0; 
	bmInfo->bmiHeader.biClrImportant = 0; 
	bmInfo->bmiHeader.biClrUsed = 0; 
	bmInfo->bmiHeader.biXPelsPerMeter = 0; 
	bmInfo->bmiHeader.biYPelsPerMeter = 0; 
	BitmapBuffer = CreateDIBSection(NULL, bmInfo, DIB_RGB_COLORS, (LPVOID *)&screen, NULL, 0);
	canvas.UseBuffer(screen);
	
	ShowWindow(windowHandle, SW_SHOW);
	UpdateWindow(windowHandle);

	RECT rect;
	rect.bottom = HEIGHT;
	rect.top = 0;
	rect.left = 0;
	rect.right = WIDTH;

	bool flag = true;

	while(flag) {
		if(PeekMessage(&msg,NULL,0,0,PM_NOREMOVE)!=0) {
			if(GetMessage(&msg,NULL,0,0) >0) {
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			else {
				flag = false;
			}
		}	
		else {
			if(autorotation) {
				scene.Rotate(0.05f,0.05f,0.05f);
			}
			InvalidateRect(windowHandle,&rect,FALSE);
		}
	}

	DeleteObject(BitmapBuffer);
	delete bmInfo;
	return 0;
}

void AntiAlias() {

}

LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
		HDC hdc;
		DWORD fps,time2;

	 switch(msg) {
        case WM_CLOSE:
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
		case WM_MOUSEMOVE:
			if(wParam==MK_LBUTTON) {
				POINTS f;
				f = MAKEPOINTS(lParam);
				
				float dx = (float)(f.y-oldy)/50;
				float dy = (float)(oldx-f.x)/50;

				oldx = f.x;
				oldy = f.y;

				autorotation = false;
				scene.Rotate(dx,dy,0);
			}
			else if(wParam==MK_RBUTTON) {
				POINTS f;
				f = MAKEPOINTS(lParam);

				if(f.y<oldy) {
					scene.Scale(1.1f);
					scale *=1.1f;
				}
				else if(f.y>oldy) {
					scene.Scale(0.9f);
					scale *=0.9f;
				}
				else {
					// nothing
				}
				oldx = f.x;
				oldy = f.y;
			}
			else {
				autorotation = true;
			}
			break;
		case WM_PAINT: {
			DWORD time = GetTickCount();
			scene.Render(&canvas, &cam);

			// paint da f*cking canvas
			PAINTSTRUCT ps;
			hdc = BeginPaint(hwnd,&ps);

			// paint here
			HDC bitmapDC = CreateCompatibleDC(hdc); //HDC heb je vast all 
			SelectObject(bitmapDC, BitmapBuffer);  
			//BitBlt(hdc,0,0,canvas.GetWidth(),canvas.GetHeight(), bitmapDC,0,0,SRCCOPY); //of what BLITTER dan ook) 
			StretchBlt(hdc,0,0,canvas.GetWidth(),canvas.GetHeight(),bitmapDC,0,0,WIDTH,HEIGHT,SRCCOPY);
			DeleteObject(bitmapDC);

			// EndPaint balances off the BeginPaint call.
			time2 = (GetTickCount()-time);

			// frame time counter
			if(fps_index==9) {
				fps_index = 0;
			}
			else {
				fps_index++;
			}
			fpsb[fps_index] = time2;

			// calculate FPS
			DWORD sum = fpsb[1]+fpsb[2]+fpsb[3]+fpsb[4]+fpsb[5]+fpsb[6]+fpsb[7]+fpsb[8]+ fpsb[9];
			fps = 10000/(sum!=0?sum:1);
			//fps = sum;
			char buffer[33];
			itoa(fps,buffer,10);
			TextOut(hdc,10,10,buffer,strlen(buffer));

			EndPaint(hwnd,&ps);
			}
		case WM_KEYUP:
			if(wParam==VK_F1) {
				MessageBox(hwnd,"Cactus 3D Engine\r\nWritten by Tommy van der Vorst, 2002-2003\r\n\r\nThis is a port of the original idx3dIII engine made by Peter Walser. Visit www.idx3d.ch. \r\nBugs or feature requests can be sent to tommy@vandervorst-bs.nl.","About",MB_OK);
			}
			else if(wParam==VK_F2) {
				// flatshade-mode
				torus->_material.SetMode(FLAT);
			}
			else if(wParam==VK_F3) {
				torus->_material.SetMode(PHONG);
			}
			else if(wParam==VK_F4) {
				torus->_material.SetMode(WIREFRAME);
			}
			else if(wParam==VK_F5) {
				torus->_material.SetMode(PHONG|ENVMAP);
			}
			else if(wParam==VK_F6) {
				torus->_material.SetTransparency(75);
			}
			else if(wParam==VK_F7) {
				torus->_material.SetTransparency(0);
			}
			else if(wParam==VK_F9) {
				torus->_material.SetReflectivity(torus->_material.GetReflectivity()+10);
			}
			else if(wParam==VK_F8) {
				WriteInfo();
			}
			else if(wParam==VK_F12) {
				torus->_material.SetReflectivity(torus->_material.GetReflectivity()-10);
			}

			break;
		break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

HBITMAP LoadImageFromResource(HINSTANCE hInstance, const char* name) {
    return (HBITMAP)LoadImage (hInstance, name,IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
}

HBITMAP LoadImageFromResource(HINSTANCE hInst, int id) {
	return (HBITMAP)LoadImage (hInst, MAKEINTRESOURCE (id),IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
}

CTexture LoadTexture(HINSTANCE hInstance, int id) {
	HBITMAP bmp =LoadImageFromResource(hInstance,id);
	
	SIZE sz;
	//GetBitmapDimensionEx(bmp,&sz);
	sz.cx =256;
	sz.cy = 256;

	HDC dc  = CreateCompatibleDC(NULL);
	HDC bitmapDC = CreateCompatibleDC(dc); //HDC heb je vast all 
	SelectObject(bitmapDC, bmp);  
	BitBlt(dc,0,0,sz.cx,sz.cy, bitmapDC,0,0,SRCCOPY); //of what BLITTER dan ook) 

	
	// in HDC dc zit nu de bitmapdata, maak er maar een DIBje van
	BITMAPINFO bmi;
	bmi.bmiHeader.biBitCount = 32;
	bmi.bmiHeader.biClrImportant = 0;
	bmi.bmiHeader.biClrUsed = 0;
	bmi.bmiHeader.biCompression = BI_RGB;
	bmi.bmiHeader.biHeight = sz.cy;
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biSizeImage = 0;
	bmi.bmiHeader.biWidth = sz.cx;
	bmi.bmiHeader.biXPelsPerMeter = 0;
	bmi.bmiHeader.biYPelsPerMeter = 0;
	
	int* data = new int[sz.cx*sz.cy];
	GetDIBits(dc,bmp, 0, sz.cy, data, &bmi, DIB_RGB_COLORS);

	CTexture t(sz.cx,sz.cy);
	t.Put(data);

	delete[] data;
	return t;
}

int GetMatMode() {
	int mode = torus->_material.GetMode();

	return mode;
}

void WriteInfo() {
	std::ofstream fout( "results.txt", 0);

	fout << "Cactus win32demo.exe running with DLL version: " << GetCactusVersion() << "\r\n";
	fout << "Last 10 framerates:\r\n";
	for(int a=0;a<10;a++) {
		fout << fpsb[a] << ",";
	}
	fout << "\r\n";
	fout << "Scale: "<< scale << "\r\n";
	fout << "Vertices: "<< (scene.CountVertices()) << "\r\n";
	fout << "Triangles: " << (scene.CountTriangles()) << "\r\n";
	fout << "Mode: ";

	int mode = GetMatMode();
	fout << "(" << mode << ") ";

	if(mode&FLAT>0) {
		fout << "Flatshading ";
	}
	if(mode&PHONG>0) {
		fout << "Phongshading ";
	}
	if(mode&ENVMAP>0) {
		fout << "Environment Mapping ";
	}
	if(mode&TEXTURED>0) {
		fout << "Texturing ";
	}
	if(mode&WIREFRAME>0) {
		fout << "Wireframe ";
	}

    fout.close();
}


void InitScene(CScene* sc) {
	CObjectFactory f;
	CTexture t = LoadTexture(GetModuleHandle(NULL),IDB_CHROME);

	
	torus = f.TorusKnot(4,3,0.28f,1.2f,0.48f,0.8f,90,8);
	torus->_material.SetColor(CColor(100,0,0));
	torus->_material.SetEnvMap(t);

	torus->_material.SetMode(PHONG|ENVMAP);
	torus->_material.SetReflectivity(100);
	torus->_material.SetTransparency(75);
	sc->AddObject(torus);
	
	
	/*MeshImporter mi("model.3ds");
	if(mi.LoadFromFile(sc)==FILE_INVALID) {
		MessageBox(NULL,"Import failed.","Error",MB_OK|MB_ICONERROR);
	}
	else {
		int vertices = sc->CountVertices();
		char buffer[33];
		itoa(vertices,buffer,10);
		MessageBox(NULL,buffer,buffer,MB_OK);
	}*/

	CLight* light = new CLight();
	light->SetDirection(CVector(0.0f,0.0f,100.0f));
	light->highlightSheen = 144;
	light->highlightSpread = 120;
	light->diffuse = CColor(255,255,255);
	light->specular  = CColor(255,255,255);
	sc->AddLight(light);

	//sc->Scale(1/2,1/2,1/2);
}