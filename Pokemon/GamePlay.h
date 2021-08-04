#pragma once

#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

#include "framework.h"
#include "Player.h"
#include "Datas.h"
#include "MainMenu.h"
#include "BaseClass.h"
#include "GameManager.h"

using namespace Gdiplus;

class GameManager;

class GamePlay : public BaseClass
{
private:

	GameManager* gm;

	Player player;
	Map* curData;

	bool isMapChange;

private:

	void DrawMap(Graphics &g, PointF origin);
	void DrawDebug(Graphics &g);

	void UpdatePlayer();

public:

	GamePlay();
	~GamePlay();

	void SetManager(GameManager* _gm);
	void Update() override;
	void Draw(Graphics &g) override;
};

#endif