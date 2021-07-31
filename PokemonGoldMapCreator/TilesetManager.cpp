#include "TilesetManager.h"


void TilesetManager::DrawSelect(Graphics *graphic)
{
	if (isSelect)
	{
		Pen pen(Color(255, 0, 0));
		graphic->DrawRectangle(&pen, curSelectPos.X, curSelectPos.Y, 15, 15);
	}
}

void TilesetManager::DrawGrid(Graphics *graphic)
{
	Pen pen(Color(255, 240, 240, 240));

	// 세로선
	for (int i = 0; i <= rect.right; i += 16)
		graphic->DrawLine(&pen, i, 0, i, rect.bottom);

	// 가로선
	for (int i = 0; i <= rect.bottom; i += 16)
		graphic->DrawLine(&pen, 0, i, rect.right, i);
}

void TilesetManager::DrawTileset(Graphics *graphic)
{
	graphic->DrawImage(tileset, 0, 0, tileset->GetWidth(), tileset->GetHeight());
}

TilesetManager::TilesetManager()
	: curSelectPos{ 0, 0 }, isSelect(false)
{  }

TilesetManager::~TilesetManager()
{
	//delete tileset;
}

void TilesetManager::LoadTileset(HWND hWnd)
{
	tileset = new Image(_T("Resource/tileset_day.png"));
}

void TilesetManager::SetSreenSize(HWND hWnd)
{
	SetRect(&totalRect, 0, 0, tileset->GetWidth(), tileset->GetHeight());
	AdjustWindowRect(&totalRect, WS_VISIBLE | WS_OVERLAPPED | WS_THICKFRAME, TRUE);
	MoveWindow(hWnd, 1000, 10, totalRect.right - totalRect.left + 3, totalRect.bottom - totalRect.top + 6, TRUE);
	GetClientRect(hWnd, &rect);
}

void TilesetManager::SetIsSelect(bool b)
{
	isSelect = b;
}

void TilesetManager::SelectTile(HWND hWnd)
{
	POINT mPos;
	GetCursorPos(&mPos);
	ScreenToClient(hWnd, &mPos);

	if (mPos.x >= rect.left && mPos.x <= rect.right && mPos.y >= rect.top && mPos.y <= rect.bottom)
	{
		if (!isSelect)
			isSelect = true;

		curSelectPos.X = mPos.x - mPos.x % 16;
		curSelectPos.Y = mPos.y - mPos.y % 16;
	}
}

void TilesetManager::Draw(HWND hWnd, HDC hdc)
{
	HDC memDC;
	HBITMAP oldBit, newBit;

	memDC = CreateCompatibleDC(hdc);

	newBit = CreateCompatibleBitmap(hdc, rect.right, rect.bottom);
	oldBit = (HBITMAP)SelectObject(memDC, newBit);

	Graphics *graphic = new Graphics(memDC);

	DrawTileset(graphic);
	DrawGrid(graphic);
	DrawSelect(graphic);

	delete graphic;

	BitBlt(hdc, 0, 0, rect.right, rect.bottom, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBit);
	DeleteObject(newBit);

	DeleteDC(memDC);
}
