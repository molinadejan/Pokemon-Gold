#pragma once

#ifndef __MYUTILS_H__
#define __MYUTILS_H__

#include <vector>
#include <string>
#include "framework.h"

using std::string;
using std::vector;

using namespace Gdiplus;

bool operator==(const Point& p1, const Point& p2);
PointF operator*(const Point& p1, const float& f);
Point operator*(const Point& p1, const int& i);

bool IsIn(Point worldPos, Point origin, Point mapSize);
bool IsIn(Point localPos, Point mapSize);

void Clamp(int& num, int min, int max);
void Clamp(float& num, float min, float max);

#endif // !__MYUTILS_H__
