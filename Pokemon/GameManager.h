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
		GAMEPLAYFADE,
	};

private:

	const float FADETIME = 0.4f;

private:

	ULONG_PTR token;
	STATE state;
	Player player;
	Map* curData;

	bool isMapChange;
	float fadeTimer;

private:

	void InitGdiPlus();
	void SetScreen(HWND hWnd);

	void FadeInOut();

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