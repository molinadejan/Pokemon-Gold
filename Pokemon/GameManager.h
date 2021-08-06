#pragma once

#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "framework.h"

using namespace Gdiplus;

class GamePlay;
class MainMenu;
class GameFadeInOut;
class BagMenu;
class BagItemSelect;
class BagItemToss;
class BagItemTossConfirm;

class GameManager
{
public:

	GamePlay *gamePlay;
	MainMenu *mainMenu;
	GameFadeInOut *gameFadeInOut;
	BagMenu *bagMenu;
	BagItemSelect *bagItemSelect;
	BagItemToss* bagItemToss;
	BagItemTossConfirm* bagItemTossConfirm;

public:

	GameManager();
	~GameManager();

	void Init();
};


#endif