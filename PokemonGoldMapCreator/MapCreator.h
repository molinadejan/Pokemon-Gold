#pragma once

#ifndef __MAPCREATOR_H__
#define __MAPCREATOR_H__

#include <windows.h>
#include "framework.h"
#include "Datas.h"
#include "TilesetManager.h"

#include <vector>

using namespace Gdiplus;
using std::vector;

class MapCreator
{
private:
	TilesetManager* tm;

	RECT rect;

	POINT cameraPos;
	POINT mapSize;

	POINT oldPos;
	POINT newPos;

	POINT curSelectPos;

	vector<vector<Tile>> tiles;

	void DrawGrid(Graphics* graphic);
	void DrawBack(Graphics* graphic);

public:
	MapCreator();

	void SetOldPos(POINT p);
	void SetNewPos(POINT p);

	void SetTilesetManager(TilesetManager *_tm);
	void SetMapSize(int x, int y);

	void SelectTile(POINT mPos);

	void SetSreenSize(HWND hWnd);
	void Draw(HDC hdc);
	void ViewDrag(HWND hWnd);
	void Update(HWND hWnd);
};

#endif // !__MAPCREATOR_H__
