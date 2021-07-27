#include "MapCreator.h"
#include <ctime>

MapCreator::MapCreator()
	: cameraPos{ 0, 0 }, mapSize{ 0, 0 }, curSelectPos{0, 0}
{ 
	srand((unsigned int)time(NULL));
}

void MapCreator::SetOldPos(POINT p)
{
	oldPos = p;
}

void MapCreator::SetNewPos(POINT p)
{
	newPos = p;
}

void MapCreator::SetTilesetManager(TilesetManager * _tm)
{
	tm = _tm;
}

void MapCreator::SetMapSize(int x, int y)
{
	mapSize = { x, y };
	tiles = vector<vector<Tile>>(y, vector<Tile>(x, Tile()));
}

void MapCreator::SelectTile(POINT mPos)
{
	mPos.x += cameraPos.x;
	mPos.y += cameraPos.y;

	if (mPos.x >= rect.left && mPos.x <= rect.right && mPos.y >= rect.top && mPos.y <= rect.bottom
		&& mPos.x / 16 <= mapSize.x && mPos.y / 16 <= mapSize.y)
	{
		curSelectPos.x = mPos.x - mPos.x % 16;
		curSelectPos.y = mPos.y - mPos.y % 16;
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
	for (int i = startX; i <= rect.right && cameraPos.x + i <= mapSize.x * 16; i += 16)
		graphic->DrawLine(&pen, i, 0, i, mapSize.y * 16 - cameraPos.y);

	// 가로선
	for (int i = startY; i <= rect.bottom && cameraPos.y + i <= mapSize.y * 16; i += 16)
		graphic->DrawLine(&pen, 0, i, mapSize.x * 16 - cameraPos.x, i);
}

void MapCreator::DrawBack(Graphics * graphic)
{
	SolidBrush brush(Color(255, 255, 255));
	graphic->FillRectangle(&brush, 0, 0, rect.right, rect.bottom);
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
	DrawGrid(graphic);

	
	Pen pen(Color(255, 0, 0));
	graphic->DrawRectangle(&pen, curSelectPos.x - cameraPos.x, curSelectPos.y - cameraPos.y, 15, 15);
	

	delete graphic;

	BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBit);
	DeleteObject(newBit);

	DeleteDC(memDC);
}

void MapCreator::Update(HWND hWnd)
{

}
