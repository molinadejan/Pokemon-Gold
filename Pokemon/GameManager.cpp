#include "GameManager.h"
#include "InputManager.h"
//#include "Converter.h"
#include "MyUtils.h"
#include "DataLoadManager.h"

#include <fstream>

// ª˝º∫¿⁄, º“∏Í¿⁄ //
GameManager::GameManager() : curData(NULL), state(STATE::INTRO) { }

GameManager::~GameManager() 
{
	GdiplusShutdown(token);
}

// private ∏‚πˆ «‘ºˆ //
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
	Image* img = DataLoadManager::GetMapImage(curData->ID);

	Rect expansion(INT(-origin.X * PIXEL * SCREEN_MUL), INT(-origin.Y * PIXEL * SCREEN_MUL), img->GetWidth() * SCREEN_MUL, img->GetHeight() * SCREEN_MUL);
	g.DrawImage(img, expansion);

	for(string& nID : curData->neighbors)
	{
		Image *nImg = DataLoadManager::GetMapImage(nID);
		Map* n = DataLoadManager::GetMapData(nID);

		Point diff = curData->worldPos - n->worldPos;

		Rect expansion2((INT)(-(origin.X + diff.X) * PIXEL * SCREEN_MUL), (INT)(-(origin.Y + diff.Y) * PIXEL * SCREEN_MUL), nImg->GetWidth() * SCREEN_MUL, nImg->GetHeight() * SCREEN_MUL);
		g.DrawImage(nImg, expansion2);
	}
}

void GameManager::DrawDebug(Graphics & g)
{
	TCHAR buffer[32];
	_tcscpy_s(buffer, CA2T(curData->ID.c_str()));

	Font font(&FontFamily(L"Arial"), 16, FontStyleBold, UnitPoint);
	SolidBrush strBrush(Color(255, 255, 255, 255));

	RectF rectF1(0, 0, 128, 32);
	g.DrawString(buffer, -1, &font, rectF1, NULL, &strBrush);

	_stprintf_s(buffer, _T("%d %d"), player.GetPos().X, player.GetPos().Y);

	RectF rectF2(0, 32, 128, 32);
	g.DrawString(buffer, -1, &font, rectF2, NULL, &strBrush);
}

void GameManager::DrawGamePlay(Graphics &g)
{
	PointF playerPos = player.GetPosF();
	PointF mapOrigin(playerPos.X - REAL(COL / 2) , playerPos.Y - REAL(ROW / 2));

	DrawMap(g, mapOrigin);
	player.DrawPlayer(g);

	DrawDebug(g);
}


// public ∏‚πˆ «‘ºˆ //
void GameManager::Init(HWND hWnd)
{
	InitGdiPlus();
	SetScreen(hWnd);
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
			player.SetPos(0, 2);
			curData = DataLoadManager::GetMapData("map0");
			state = STATE::GAMEPLAY;
		}
		break;

		case STATE::GAMEPLAY:
		{
			int h = InputManager::GetHorizontal();
			int v = InputManager::GetVertical();

			if (!player.GetIsMoving())
			{
				Point pos = player.GetPos();

				// ¡ˆø™¿Ã πŸ≤Óæ˙¥¬¡ˆ √º≈©
				if(!IsIn(pos, curData->mapSize))
				{
					Point worldPos = pos + curData->worldPos;

					for (string &nID : curData->neighbors)
					{
						Map *n = DataLoadManager::GetMapData(nID);

						if (IsIn(worldPos, n->worldPos, n->mapSize))
						{
							curData = n;
							player.SetPos(worldPos - curData->worldPos);
							break;
						}
					}
				}
			}

			player.MovePlayer({ h, v }, curData);
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

	// «»ºø »Â∑¡¡¸ πÊ¡ˆ
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
