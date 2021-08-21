#pragma once

#ifndef __GAMEPLAY_H__
#define __GAMEPLAY_H__

#include "Player.h"
#include "Datas.h"
#include "BaseClass.h"

class GamePlay : public BaseClass
{
private:

	Player* player;
	Map* curData;

	Image* encounterImg;
	vector<Rect>* encounterRect;
	int frameCnt;

	bool isMapChange;
	bool isFirstLoad;

	int checkCnt;
	bool isEncounter; 
	int tp;

private:

	void DrawMap(Graphics &g);
	void DrawDebug(Graphics &g);
	void DrawEncounterAnimation(Graphics& g);

	void _Encounter();
	void UpdatePlayer();

public:

	GamePlay();
	~GamePlay() = default;

	void Init() override;
	void Update() override;
	void Draw(Graphics &g) override;
};

#endif