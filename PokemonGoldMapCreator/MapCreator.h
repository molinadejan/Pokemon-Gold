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

	Point cameraPos;
	Point oldPos;
	Point newPos;

	Point curSelectPos;

	Map mapData;

	Bitmap *mapImage;
	Bitmap *coliImage;
	Bitmap *mpImage;

	bool isSelect;

	bool PosInGrid(Point pos);

	void DrawToCollider(int moveable, int x, int y);
	void DrawToMap(Image* img, int x, int y, int srcx, int srcy);
	void EraseToMap(int x, int y);
	void DrawToMp(int isPoint, int x, int y);

	void DrawGrid(Graphics* graphic);
	void DrawBack(Graphics* graphic);
	void DrawMap(Graphics* graphic);
	void DrawCollider(Graphics* graphic);
	void DrawMp(Graphics* graphic);
	void DrawCurSelect(Graphics* graphic);

	void InitMap(int x, int y);
	void InitMap(TCHAR *filepath);
	void InitCollider(int x, int y);
	void InitMp(int x, int y);

public:
	MapCreator();

	void SetOldPos(Point p) { oldPos = p; }
	void SetNewPos(Point p) { newPos = p; }

	void SetTilesetManager(TilesetManager *_tm) { tm = _tm; }

	void SelectTile(Point mPos);
	void SetTile(Point mPos);
	void EraseTile(Point mPos);
	void SetCollider(Point mPos);
	void SetMp(Point mPos);

	Tile* GetSelectTile();
	MovePoint* GetMP();
	Map* GetMap() { return &mapData; }

	void SetSreenSize(HWND hWnd);
	void Draw(HDC hdc);
	void ViewDrag(HWND hWnd);

	void MapCreate(TCHAR *id, int x, int y);
	void FileOpen(TCHAR* filename);
	void FileSave(TCHAR* filename);

	string GetMapID() const { return mapData.ID; }
};

#endif // !__MAPCREATOR_H__
