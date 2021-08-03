#pragma once

#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "framework.h"
#include "Player.h"
#include "Datas.h"
#include "MainMenu.h"

using namespace Gdiplus;

class GameManager
{
private:
	enum STATE
	{
		INTRO,
		LOADORNEW,
		GAMEPLAY,
		GAMEPLAYFADE,
		GAMEPLAYMAINMENU,
	};

private:

	const float FADETIME = 0.4f;

private:

	STATE state;

	Player player;
	Map* curData;

	MainMenu mainMenu;

	bool isMapChange;
	float fadeTimer;

private:

	void SetScreen(HWND hWnd);

	void DrawMap(Graphics &g, PointF origin);
	void DrawDebug(Graphics &g);
	void DrawGamePlay(Graphics &g);

	void UpdateSceneChange();
	void UpdatePlayer();

public:

	GameManager();
	~GameManager();

	void Init(HWND hWnd);
	void Update();
	void Draw(HWND hWnd);
};

#endif