#pragma once

#ifndef __MYUTILS_H__
#define __MYUTILS_H__

#include <vector>
#include <string>
#include "Datas.h"
#include "framework.h"


using std::string;
using std::vector;
using namespace Gdiplus;

bool operator==(const Point& p1, const Point& p2);
PointF operator*(const Point& p1, const float& f);
Point operator*(const Point& p1, const int& i);

//bool IsIn(Point pos, int originX, int originY, int w, int h);

bool IsIn(Point worldPos, Point origin, Point mapSize);

//bool IsIn(Point pos, int mapSizeX, int mapSizeY);

bool IsIn(Point localPos, Point mapSize);

void Clamp(int& num, int min, int max);
void Clamp(float& num, float min, float max);

Tile* GetTile(Map *m, Point pos);

Map* GetNMap(Map* m, Point pos);

#endif // !__MYUTILS_H__
