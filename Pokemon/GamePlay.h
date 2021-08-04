#pragma once

#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

#include "Player.h"
#include "Datas.h"
#include "BaseClass.h"

class GamePlay : public BaseClass
{
private:

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

	void Update() override;
	void Draw(Graphics &g) override;
};

#endif