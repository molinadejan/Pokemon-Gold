#include "MapCreator.h"
#include <ctime>
#include <json/json.h>
#include <fstream>
#include <string>
#include <cstdio>

#include "Converter.hpp"

MapCreator::MapCreator()
	: cameraPos{ 0, 0 }, curSelectPos{0, 0}, mapImage(NULL), coliImage(NULL)
{ 
	mapData.ID = "";
	mapData.mapSize = { 0, 0 };
}

bool MapCreator::PosInGrid(POINT pos)
{
	if (pos.x < rect.left || pos.x > rect.right || pos.y < rect.top || pos.y > rect.bottom || pos.x / 16 >= mapData.mapSize.x || pos.y / 16 >= mapData.mapSize.y)
		return false;

	return true;
}

void MapCreator::DrawToCollider(int moveable, int x, int y)
{
	Graphics g(coliImage);
	g.SetCompositingMode(CompositingMode::CompositingModeSourceCopy);

	if (moveable == 1)
	{
		SolidBrush brush(Color(0, 255, 255, 255));
		g.FillRectangle(&brush, x, y, 16, 16);
	}
	else
	{
		SolidBrush brush(Color(100, 255, 0, 0));
		g.FillRectangle(&brush, x, y, 16, 16);
	}
}

void MapCreator::DrawToMap(Image *img, int x, int y, int srcx, int srcy)
{
	Graphics g(mapImage);
	g.DrawImage(img, x, y, srcx, srcy, 16, 16, Unit::UnitPixel);
}

void MapCreator::SelectTile(POINT mPos)
{
	mPos.x += cameraPos.x;
	mPos.y += cameraPos.y;

	if(PosInGrid(mPos))
	{
		curSelectPos.x = mPos.x - mPos.x % 16;
		curSelectPos.y = mPos.y - mPos.y % 16;

		int idxX = curSelectPos.x / 16;
		int idxY = mapData.mapSize.y - curSelectPos.y / 16 - 1;

		if (tm->GetIsSelect())
		{
			POINT src = mapData.tiles[idxY][idxX].tilePos = tm->GetCurSelectPos();

			//DrawToMap(tm->GetTileset(), curSelectPos.x, curSelectPos.y, src.x, src.y);

			Graphics g(mapImage);
			g.DrawImage(tm->GetTileset(), curSelectPos.x, curSelectPos.y, src.x, src.y, 16, 16, Unit::UnitPixel);
		}
	}
}

void MapCreator::SelectCollider(POINT mPos)
{
	mPos.x += cameraPos.x;
	mPos.y += cameraPos.y;

	if (PosInGrid(mPos))
	{
		curSelectPos.x = mPos.x - mPos.x % 16;
		curSelectPos.y = mPos.y - mPos.y % 16;

		int idxX = curSelectPos.x / 16;
		int idxY = mapData.mapSize.y - curSelectPos.y / 16 - 1;

		Tile &curTile = mapData.tiles[idxY][idxX];

		curTile.moveable = curTile.moveable == 1 ? 0 : 1;
		DrawToCollider(curTile.moveable, curSelectPos.x, curSelectPos.y);
	}
}

void MapCreator::ViewDrag(HWND hWnd)
{
	cameraPos.x -= newPos.x - oldPos.x;
	cameraPos.y -= newPos.y - oldPos.y;

	if (cameraPos.x < 0) cameraPos.x = 0;
	if (cameraPos.y < 0) cameraPos.y = 0;

	oldPos = newPos;
}

void MapCreator::SetSreenSize(HWND hWnd)
{
	GetClientRect(hWnd, &rect);
}

void MapCreator::DrawGrid(Graphics *graphic)
{
	Pen pen(Color(100, 100, 100, 100));

	int startX, startY;

	if (cameraPos.x % 16 == 0) startX = 0;
	else startX = 16 - cameraPos.x % 16;

	if (cameraPos.y % 16 == 0) startY = 0;
	else startY = 16 - cameraPos.y % 16;

	// 세로선
	for (int i = startX; i <= rect.right && cameraPos.x + i <= mapData.mapSize.x * 16; i += 16)
		graphic->DrawLine(&pen, i, 0, i, mapData.mapSize.y * 16 - cameraPos.y);

	// 가로선
	for (int i = startY; i <= rect.bottom && cameraPos.y + i <= mapData.mapSize.y * 16; i += 16)
		graphic->DrawLine(&pen, 0, i, mapData.mapSize.x * 16 - cameraPos.x, i);
}

void MapCreator::DrawBack(Graphics* graphic)
{
	SolidBrush brush(Color(255, 255, 255));
	graphic->FillRectangle(&brush, 0, 0, rect.right, rect.bottom);
}

void MapCreator::DrawMap(Graphics* graphic)
{
	if(mapImage != NULL)
		graphic->DrawImage(mapImage, 0, 0, cameraPos.x, cameraPos.y, mapImage->GetWidth() - cameraPos.x, mapImage->GetHeight() - cameraPos.y, Unit::UnitPixel);
}

void MapCreator::DrawCollider(Graphics* graphic)
{
	if (coliImage != NULL)
		graphic->DrawImage(coliImage, 0, 0, cameraPos.x, cameraPos.y, coliImage->GetWidth() - cameraPos.x, coliImage->GetHeight() - cameraPos.y, Unit::UnitPixel);
}

void MapCreator::InitMap(int x, int y)
{
	if (mapImage != NULL)
		delete mapImage;

	mapImage = new Bitmap(x, y, PixelFormat32bppARGB);

	Graphics g(mapImage);
	g.Clear(Color(255, 200, 200, 200));
}

void MapCreator::InitMap(TCHAR * filepath)
{
	if (mapImage != NULL)
		delete mapImage;

	mapImage = new Bitmap(filepath);
}

void MapCreator::InitCollider(int x, int y)
{
	if (coliImage != NULL)
		delete coliImage;

	coliImage = new Bitmap(x, y , PixelFormat32bppARGB);

	Graphics g(coliImage);
	g.Clear(Color(0, 255, 255, 255));
}

void MapCreator::Draw(HDC hdc)
{
	HDC memDC;
	HBITMAP oldBit, newBit;

	memDC = CreateCompatibleDC(hdc);

	newBit = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
	oldBit = (HBITMAP)SelectObject(memDC, newBit);

	Graphics *graphic = new Graphics(memDC);
	
	DrawBack(graphic);
	DrawMap(graphic);
	DrawCollider(graphic);
	DrawGrid(graphic);
	
	/*Pen pen(Color(255, 0, 0));
	graphic->DrawRectangle(&pen, curSelectPos.x - cameraPos.x, curSelectPos.y - cameraPos.y, 15, 15);*/

	delete graphic;

	BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBit);
	DeleteObject(newBit);

	DeleteDC(memDC);
}

void MapCreator::MapCreate(TCHAR *id, int x, int y)
{
	std::wstring wID(id);
	std::string sID(wID.begin(), wID.end());

	mapData.ID = sID;
	mapData.mapSize = { x, y };
	mapData.tiles = vector<vector<Tile>>(y, vector<Tile>(x, Tile()));

	InitMap(x * 16, y * 16);
	InitCollider(x * 16, y * 16);
}

void MapCreator::FileOpen(TCHAR * filename)
{
	TCHAR imgName[256];
	_stprintf_s(imgName, _T("Files\\%s.png"), filename);

	TCHAR dataName[256];
	_stprintf_s(dataName, _T("Files\\%s.mapData"), filename);

	Json::Value root;
	std::ifstream readFile(dataName);

	readFile >> root;
	readFile.close();

	JsonToMap(mapData, root);

	InitMap(imgName);
	InitCollider(mapData.mapSize.x * 16, mapData.mapSize.y * 16);

	cameraPos = curSelectPos = oldPos = newPos = { 0, 0 };

	for (int i = 0; i < mapData.mapSize.y; ++i)
		for (int j = 0; j < mapData.mapSize.x; ++j)
			DrawToCollider(mapData.tiles[i][j].moveable, j * 16, (mapData.mapSize.y - i - 1) * 16);
}

void MapCreator::FileSave(TCHAR* filename)
{
	if (mapImage == NULL)
		return;

	TCHAR imgName[256];
	_stprintf_s(imgName, _T("Files\\%s.png"), filename);

	TCHAR dataName[256];
	_stprintf_s(dataName, _T("Files\\%s.mapData"), filename);

	CLSID png_sid;
	GetEncoderClsid(L"image/png", &png_sid);
	mapImage->Save(imgName, &png_sid, NULL);

	Json::Value root;
	MapToJson(mapData, root);

	std::ofstream writeFile(dataName);

	Json::StreamWriterBuilder writer;
	string str = Json::writeString(writer, root);

	writeFile << str;
	writeFile.close();
}
