#include "MapCreator.h"
#include <ctime>

MapCreator::MapCreator()
	: cameraPos{ 0, 0 }, mapSize{ 25, 25 }, tiles(vector<vector<Color>>(25, vector<Color>(25)))
{ 
	srand((unsigned int)time(NULL));

	for (int i = 0; i < 25; ++i)
		for (int j = 0; j < 25; ++j)
			tiles[j][i] = Color(rand() % 256, rand() % 256, rand() % 256);
}

bool MapCreator::ViewDrag()
{
	static int dragCnt = 0;

	if (GetAsyncKeyState(VK_MENU) & 0x8001 && GetAsyncKeyState(VK_LBUTTON) & 0x8001)
	{
		if (dragCnt < 5)
			++dragCnt;

		if (dragCnt == 1)
			GetCursorPos(&oldPos);

		GetCursorPos(&newPos);

		cameraPos.x -= newPos.x - oldPos.x;
		cameraPos.y -= newPos.y - oldPos.y;

		if (cameraPos.x < 0) cameraPos.x = 0;
		if (cameraPos.y < 0) cameraPos.y = 0;

		oldPos = newPos;

		return true;
	}
	else dragCnt = 0;

	return false;
}

void MapCreator::SetSreenSize(HWND hWnd)
{
	GetClientRect(hWnd, &rect);
}

void MapCreator::DrawGrid(Graphics * g)
{
	Pen pen(Color(100, 100, 100, 100));

	int startX, startY;

	if (cameraPos.x % 16 == 0) startX = 0;
	else startX = 16 - cameraPos.x % 16;

	if (cameraPos.y % 16 == 0) startY = 0;
	else startY = 16 - cameraPos.y % 16;

	// 세로선
	for (int i = startX; i <= rect.right && cameraPos.x + i <= mapSize.x * 16; i += 16)
		g->DrawLine(&pen, i, 0, i, mapSize.y * 16 - cameraPos.y);

	// 가로선
	for (int i = startY; i <= rect.bottom && cameraPos.y + i <= mapSize.y * 16; i += 16)
		g->DrawLine(&pen, 0, i, mapSize.x * 16 - cameraPos.x, i);
}

void MapCreator::Draw(HDC hdc)
{
	HDC memDC;
	HBITMAP oldBit, newBit;

	memDC = CreateCompatibleDC(hdc);

	newBit = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
	oldBit = (HBITMAP)SelectObject(memDC, newBit);

	Graphics *graphic = new Graphics(memDC);
	
	SolidBrush brush(Color(255, 255, 255));
	graphic->FillRectangle(&brush, 0, 0, rect.right, rect.bottom);

	DrawGrid(graphic);

	delete graphic;

	BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBit);
	DeleteObject(newBit);

	DeleteDC(memDC);
}

void MapCreator::Update()
{
	ViewDrag();
}
