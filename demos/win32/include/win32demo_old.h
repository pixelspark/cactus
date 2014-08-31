#ifndef __CACTUS_WIN32DEMO_H
#define __CACTUS_WIN32DEMO_H


#include <windows.h>
#undef RGB
#include "../../include/cactus.h"
#include "../../include/tweakfpu.h"

LRESULT CALLBACK windowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void InitScene(CScene* sc);
void AntiAlias();
HBITMAP LoadImageFromResource(HINSTANCE,int);
HBITMAP LoadImageFromResource(HINSTANCE,const char*);
void WriteInfo();

#endif