#pragma once

#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "framework.h"
#include "Player.h"
#include "Datas.h"

using namespace Gdiplus;

class GameManager
{
private:
	enum STATE
	{
		INTRO,
		LOADORNEW,
		GAMEPLAY,
	};

private:

	ULONG_PTR token;
	STATE state;

	Player player;

	Map* curData;
	//Map* neighborData[4];

private:

	void InitGdiPlus();
	void SetScreen(HWND hWnd);

	void DrawMap(Graphics &g, PointF origin);
	void DrawDebug(Graphics &g);

	void DrawGamePlay(Graphics &g);

public:

	GameManager();
	~GameManager();

	void Init(HWND hWnd);
	void Update();
	void Draw(HWND hWnd);
};

#endif