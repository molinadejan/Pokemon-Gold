#pragma once

#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "framework.h"
#include "RunManager.h"
#include "GamePlay.h"
#include "BaseClass.h"
#include "MainMenu.h"
#include "GameFadeInOut.h"

using namespace Gdiplus;

class GamePlay;
class MainMenu;
class GameFadeInOut;

class GameManager
{
public:

	GamePlay *gamePlay;
	MainMenu *mainMenu;
	GameFadeInOut *gameFadeInOut;

public:

	GameManager();
	~GameManager();

	void Init();
};


#endif