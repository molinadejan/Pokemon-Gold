#include "GameManager.h"
#include "InputManager.h"

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

void GameManager::DrawMap(Graphics &g, PointF origin)
{
	Image img(L"data/map/map0.png");
	Rect expansion(-origin.X * PIXEL * SCREEN_MUL, -origin.Y * PIXEL * SCREEN_MUL, img.GetWidth() * SCREEN_MUL, img.GetHeight() * SCREEN_MUL);
	g.DrawImage(&img, expansion);
}


// public ¸â¹ö ÇÔ¼ö //
void GameManager::Init(HWND hWnd)
{
	InitGdiPlus();
	SetScreen(hWnd);

	state = STATE::GAMEPLAY;
}

void GameManager::Update()
{
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

	PointF playerPos = player.GetWorldPos();
	playerPos.X -= COL / 2;
	playerPos.Y -= ROW / 2;
	DrawMap(graphic, playerPos);

	PointF origin((COL / 2) * PIXEL * SCREEN_MUL, (ROW / 2) * PIXEL * SCREEN_MUL);
	player.DrawPlayer(graphic, origin);

	BitBlt(hdc, 0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y, memDC, 0, 0, SRCCOPY);
	SelectObject(memDC, oldBit);
	DeleteObject(newBit);

	DeleteDC(memDC);

	EndPaint(hWnd, &ps);
}
