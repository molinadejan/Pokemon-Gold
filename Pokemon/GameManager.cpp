#include "GameManager.h"
#include "InputManager.h"
#include "Converter.hpp"

#include <fstream>

// »ý¼ºÀÚ, ¼Ò¸êÀÚ //
GameManager::GameManager() { }

GameManager::~GameManager() 
{
	GdiplusShutdown(token);
}

// private ¸â¹ö ÇÔ¼ö //
void GameManager::InitGdiPlus()
{
	GdiplusStartupInput gpsi;
	GdiplusStartup(&token, &gpsi, NULL);
}

void GameManager::SetScreen(HWND hWnd)
{
	RECT rect;
	SetRect(&rect, 0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
	AdjustWindowRect(&rect, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME, FALSE);
	MoveWindow(hWnd, 100, 100, rect.right - rect.left, rect.bottom - rect.top, TRUE);
}

void GameManager::LoadData(string ID, Map &map)
{
	TCHAR id[64];
	_tcscpy_s(id, CA2T(ID.c_str()));

	TCHAR dataName[256];
	_stprintf_s(dataName, _T("data/map/%s.mapData"), id);

	Json::Value root;
	std::ifstream readFile(dataName);

	if (readFile.is_open())
	{
		readFile >> root;
		readFile.close();

		JsonToMap(map, root);
	}
}

void GameManager::DrawMap(Graphics &g, PointF origin)
{
	TCHAR id[64], imgName[128];

	_tcscpy_s(id, CA2T(curData.ID.c_str()));
	_stprintf_s(imgName, _T("data/map/%s.png"), id);

	Image img(imgName);
	Rect expansion(-origin.X * PIXEL * SCREEN_MUL, -origin.Y * PIXEL * SCREEN_MUL, img.GetWidth() * SCREEN_MUL, img.GetHeight() * SCREEN_MUL);
	g.DrawImage(&img, expansion);

	for (int i = 0; i < curData.neighbors.size(); ++i)
	{
		_tcscpy_s(id, CA2T(curData.neighbors[i].c_str()));
		_stprintf_s(imgName, _T("data/map/%s.png"), id);

		Image tmp(imgName);

		int diffX = curData.worldPos.x - neighborData[i].worldPos.x;
		int diffY = curData.worldPos.y - neighborData[i].worldPos.y;

		Rect expansion2(-(origin.X + diffX) * PIXEL * SCREEN_MUL, -(origin.Y + diffY) * PIXEL * SCREEN_MUL, tmp.GetWidth() * SCREEN_MUL, tmp.GetHeight() * SCREEN_MUL);
		g.DrawImage(&tmp, expansion2);
	}
}

void GameManager::DrawGamePlay(Graphics &g)
{
	PointF playerPos = player.GetPosF();
	playerPos.X -= COL / 2;
	playerPos.Y -= ROW / 2;
	DrawMap(g, playerPos);

	PointF origin((COL / 2) * PIXEL * SCREEN_MUL, (ROW / 2) * PIXEL * SCREEN_MUL);
	player.DrawPlayer(g, origin);
}


// public ¸â¹ö ÇÔ¼ö //
void GameManager::Init(HWND hWnd)
{
	InitGdiPlus();
	SetScreen(hWnd);

	state = STATE::INTRO;
}

void GameManager::Update()
{
	switch (state)
	{
		case STATE::INTRO:
		{
			state = STATE::LOADORNEW;
		}
		break;

		case STATE::LOADORNEW:
		{
			LoadData("map0", curData);

			for (int i = 0; i < curData.neighbors.size(); ++i)
				LoadData(curData.neighbors[i], neighborData[i]);

			state = STATE::GAMEPLAY;
		}
		break;

		case STATE::GAMEPLAY:
		{
			player.MovePlayer({ InputManager::GetHorizontal(), InputManager::GetVertical() });
		}
		break;
	}
}

void GameManager::Draw(HWND hWnd)
{
	HDC hdc, memDC;
	HBITMAP oldBit, newBit;

	PAINTSTRUCT ps;
	hdc = BeginPaint(hWnd, &ps);

	memDC = CreateCompatibleDC(hdc);

	newBit = CreateCompatibleBitmap(hdc, SCREEN_SIZE_X, SCREEN_SIZE_Y);
	oldBit = (HBITMAP)SelectObject(memDC, newBit);

	Graphics graphic(memDC);

	// ÇÈ¼¿ Èå·ÁÁü ¹æÁö
	graphic.SetInterpolationMode(InterpolationMode::InterpolationModeNearestNeighbor);
	graphic.SetPixelOffsetMode(PixelOffsetMode::PixelOffsetModeHalf);

	switch (state)
	{
		case STATE::INTRO:
		{

		}
		break;

		case STATE::LOADORNEW:
		{

		}
		break;

		case STATE::GAMEPLAY:
		{
			DrawGamePlay(graphic);
		}
		break;
	}

	BitBlt(hdc, 0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBit);
	DeleteObject(newBit);

	DeleteDC(memDC);

	EndPaint(hWnd, &ps);
}
