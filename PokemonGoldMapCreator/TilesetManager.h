#pragma once

#ifndef __TILESETMANAGER_H__
#define __TILESETMANAGER_H__

#include "framework.h"

using namespace Gdiplus;

class TilesetManager
{
private:

	RECT rect;
	RECT totalRect;

	Image *tileset;
	
	POINT curSelectPos;
	bool isSelect;

	void DrawSelect(Graphics *graphic);
	void DrawGrid(Graphics *graphic);
	void DrawTileset(Graphics *graphic);

public:

	TilesetManager();
	~TilesetManager();

	void LoadTileset(HWND hWnd);
	void SetSreenSize(HWND hWnd);

	void SetIsSelect(bool b);
	void SelectTile(HWND hWnd);

	void Draw(HWND hWnd, HDC hdc);
	void Update(HWND hWnd);

	Image* GetTileset();
};

#endif // !__TILESETMANAGER_H__
