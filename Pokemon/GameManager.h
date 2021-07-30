#pragma once

#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "framework.h"
#include "Player.h"

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

private:

	void InitGdiPlus();
	void SetScreen(HWND hWnd);
	void DrawMap(Graphics &g, PointF origin);

public:

	GameManager();
	~GameManager();

	void Init(HWND hWnd);
	void Update();
	void Draw(HWND hWnd);
};

#endif