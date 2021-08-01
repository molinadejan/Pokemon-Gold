#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용을 Windows 헤더에서 제외합니다.
// Windows 헤더 파일
#include <windows.h>
// C 런타임 헤더 파일입니다.
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

// json
#include <json/json.h>

// string to TCHAR
#include <atlstr.h>

const int SCREEN_MUL = 4;
const int PIXEL = 16;

const int ROW = 11;
const int COL = 11;

const int SCREEN_SIZE_X = PIXEL * COL * SCREEN_MUL;
const int SCREEN_SIZE_Y = PIXEL * ROW * SCREEN_MUL;