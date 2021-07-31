#pragma once

#ifndef __MYUTILS_H__
#define __MYUTILS_H__

#include "framework.h"

using namespace Gdiplus;

//bool IsIn(Point pos, int originX, int originY, int w, int h);
bool IsIn(Point worldPos, Point origin, Point mapSize);

//bool IsIn(Point pos, int mapSizeX, int mapSizeY);
bool IsIn(Point localPos, Point mapSize);

#endif // !__MYUTILS_H__
