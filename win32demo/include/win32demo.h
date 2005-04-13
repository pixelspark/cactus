#ifndef __SANDSTORM_MAIN_H
#define __SANDSTORM_MAIN_H

#include "../../include/cactus.h"
#undef RGB
#include "../../sandstorm/include/sandstorm.h"

#include <windows.h>

using namespace cactus;

CScene* InitScene();
LRESULT CALLBACK windowProc(HWND,UINT,WPARAM,LPARAM);


#endif