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
	
	Point curSelectPos;
	bool isSelect;

	void DrawSelect(Graphics *graphic);
	void DrawGrid(Graphics *graphic);
	void DrawTileset(Graphics *graphic);

public:

	TilesetManager();
	~TilesetManager();

	bool GetIsSelect() const { return isSelect; }

	Point GetCurSelectPos() const { return curSelectPos; }
	Image* GetTileset() const { return tileset; }

	void LoadTileset(HWND hWnd);
	void SetSreenSize(HWND hWnd);

	void SetIsSelect(bool b);
	void SelectTile(HWND hWnd);

	void Draw(HWND hWnd, HDC hdc);
};

#endif // !__TILESETMANAGER_H__
