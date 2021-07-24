#pragma once

#ifndef __MAPCREATOR_H__
#define __MAPCREATOR_H__

#include <windows.h>
#include "framework.h"

#include <vector>

using namespace Gdiplus;
using std::vector;

class MapCreator
{
private:

	RECT rect;

	POINT cameraPos;
	POINT mapSize;

	POINT oldPos;
	POINT newPos;

	vector<vector<Color>> tiles;

	bool ViewDrag();

public:
	MapCreator();

	void SetSreenSize(HWND hWnd);

	void DrawGrid(Graphics* g);
	void Draw(HDC hdc);

	void Update();
};

#endif // !__MAPCREATOR_H__
