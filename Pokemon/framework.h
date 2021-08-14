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

#include <cmath>

// string to TCHAR
#include <atlstr.h>

const int SCREEN_MUL = 5;
const int PIXEL = 16;
const int POKE_PIXEL = 56;

const int MUL = SCREEN_MUL * PIXEL;

const int ROW = 9;
const int COL = 10;

const int SCREEN_SIZE_X = PIXEL * COL * SCREEN_MUL;
const int SCREEN_SIZE_Y = PIXEL * ROW * SCREEN_MUL;