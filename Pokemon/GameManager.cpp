#define MAX_STYLE_SIZE 20
#define MAX_FACEANDSTYLE_SIZE (LF_FACESIZE + MAX_STYLE_SIZE + 2)

#include "GameManager.h"
#include "InputManager.h"
#include "MyUtils.h"
#include "DataLoadManager.h"

#include <fstream>
#include <cmath>
#include <strsafe.h>

// ������, �Ҹ��� //
GameManager::GameManager() : curData(NULL), state(STATE::INTRO), isMapChange(false), fadeTimer(0.0f) { }
GameManager::~GameManager() { }

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

	Rect expansion((INT)round(-origin.X * PIXEL * SCREEN_MUL), (INT)round(-origin.Y * PIXEL * SCREEN_MUL), img->GetWidth() * SCREEN_MUL, img->GetHeight() * SCREEN_MUL);
	g.DrawImage(img, expansion);

	for(string& nID : curData->neighbors)
	{
		Image *nImg = DataLoadManager::GetMapImage(nID);
		Map* n = DataLoadManager::GetMapData(nID);

		Point diff = curData->worldPos - n->worldPos;

		Rect expansion2((INT)round(-(origin.X + diff.X) * PIXEL * SCREEN_MUL), (INT)round(-(origin.Y + diff.Y) * PIXEL * SCREEN_MUL), nImg->GetWidth() * SCREEN_MUL, nImg->GetHeight() * SCREEN_MUL);
		g.DrawImage(nImg, expansion2);
	}
}

void GameManager::DrawDebug(Graphics & g)
{
	Font* font = DataLoadManager::GetFontS();

	TCHAR buffer[128];
	_tcscpy_s(buffer, CA2T(curData->ID.c_str()));

	SolidBrush strBrush(Color(255, 255, 255, 255));

	RectF rectF1(0, 0, 64 * SCREEN_MUL, 8 * SCREEN_MUL);
	g.DrawString(buffer, -1, font, rectF1, NULL, &strBrush);

	_stprintf_s(buffer, _T("���� ��ǥ : %d %d"), player.GetPos().X, player.GetPos().Y);

	RectF rectF2(0, 8 * SCREEN_MUL, 64 * SCREEN_MUL, 8 * SCREEN_MUL);
	g.DrawString(buffer, -1, font, rectF2, NULL, &strBrush);

	_stprintf_s(buffer, _T("���� ��ǥ : %d %d"), player.GetPos().X + curData->worldPos.X, player.GetPos().Y + curData->worldPos.Y);

	RectF rectF3(0, 16 * SCREEN_MUL, 64 * SCREEN_MUL, 8 * SCREEN_MUL);
	g.DrawString(buffer, -1, font, rectF3, NULL, &strBrush);
}

void GameManager::DrawGamePlay(Graphics &g)
{
	PointF playerPos = player.GetPosF();
	PointF mapOrigin(playerPos.X - REAL(COL / 2) , playerPos.Y - REAL(ROW / 2));

	DrawMap(g, mapOrigin);
	player.DrawPlayer(g);

	if (state == STATE::GAMEPLAYFADE)
	{
		int tp = 255 * ((FADETIME - fadeTimer) / (FADETIME));
		SolidBrush brush(Color(tp, 0, 0, 0));
		g.FillRectangle(&brush, 0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
	}
	else if (state == STATE::GAMEPLAYMAINMENU)
	{
		mainMenu.DrawMainMenu(g);
	}

	DrawDebug(g);
}

void GameManager::UpdateSceneChange()
{
	fadeTimer += Timer::DeltaTime();

	if (fadeTimer > FADETIME)
	{
		fadeTimer = 0.0f;
		state = STATE::GAMEPLAY;
	}
}

void GameManager::UpdatePlayer()
{
	player.FrameUpdate();

	if (player.GetIsMoving())
	{
		player.MovingPlayer();
	}
	else
	{
		//// Move To Neighbor Map ////
		Map* nMap = NULL;

		if (player.IsOnNMap(curData, nMap))
		{
			player.SetPos(player.GetPos() + curData->worldPos - nMap->worldPos);
			curData = nMap;
			return;
		}

		//// Move To Door
		MovePoint* mpDoor = NULL;

		if (player.isOnDoor(curData, mpDoor))
		{
			if (isMapChange)
			{
				player.MovePlayer(curData, mpDoor->GetDir());
				isMapChange = false;
			}
			else
			{
				curData = DataLoadManager::GetMapData(mpDoor->targetID);
				player.SetPos(mpDoor->targetPos);
				isMapChange = true;

				state = STATE::GAMEPLAYFADE;
			}

			return;
		}

		isMapChange = false;

		//// Input
		Point inputDir(InputManager::GetHorizontal(), InputManager::GetVertical());

		if (inputDir == Point(0, 0))
			return;

		//// Move On Carpet
		MovePoint* mpCarpet = NULL;

		if (player.isOnCarpet(curData, mpCarpet))
		{
			if (mpCarpet->GetDir() == inputDir)
			{
				curData = DataLoadManager::GetMapData(mpCarpet->targetID);
				player.SetPos(mpCarpet->targetPos);
				isMapChange = true;

				state = STATE::GAMEPLAYFADE;
				return;
			}
		}

		//// Move Player
		player.MovePlayer(curData, inputDir);
	}
}

// public ��� �Լ� //
void GameManager::Init(HWND hWnd)
{
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
			UpdatePlayer();

			if (InputManager::GetEnter() && !player.GetIsMoving())
			{
				mainMenu.Init();
				state = STATE::GAMEPLAYMAINMENU;
			}
		}
		break;

		case STATE::GAMEPLAYFADE:
		{
			UpdateSceneChange();
		}
		break;

		case STATE::GAMEPLAYMAINMENU:
		{
			if ((InputManager::GetEnter() && mainMenu.GetState() == MainMenu::MainMenuState::Main) || 
				(InputManager::GetX() && mainMenu.GetState() == MainMenu::MainMenuState::Main) ||
				 mainMenu.GetState() == MainMenu::MainMenuState::Exit)
				state = STATE::GAMEPLAY;

			mainMenu.UpdateMainMenu();
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

	// �ȼ� ����� ����
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
		case STATE::GAMEPLAYFADE:
		case STATE::GAMEPLAYMAINMENU:
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
