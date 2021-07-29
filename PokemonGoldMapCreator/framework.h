#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
#include <windows.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>

// GDI+
#include <ObjIdl.h>
#include <gdiplus.h>
#pragma comment(lib, "Gdiplus.lib")

// delatTime
#include "Timer.h"
#include <cmath>

//#pragma comment(lib, "./lib/InputManager.lib")
//#include "./lib/header/InputManager.h"

#define WM_SELECT_TILE WM_USER + 1