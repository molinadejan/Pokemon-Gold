#pragma once

#ifndef __GAMEFADEINOUT_H__
#define __GAMEFADEINOUT_H__

#include "framework.h"
#include "BaseClass.h"
#include "GameManager.h"

using namespace Gdiplus;

class GameManager;

class GameFadeInOut : public BaseClass
{
private:

	const float FADETIME = 0.4f;

private:

	GameManager* gm;
	float fadeTimer;

public:

	GameFadeInOut();
	~GameFadeInOut() = default;
	
	void SetManager(GameManager* _gm);

	void Draw(Graphics& g) override;
	void Update() override;
};

#endif
