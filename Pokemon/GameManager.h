#pragma once

#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include "framework.h"

using namespace Gdiplus;

class GamePlay;
class MainMenu;
class BagMenu;
class BagItemSelect;
class BagItemToss;
class BagItemTossConfirm;
class BattleScreen;
class Intro;
class GameStart;
class CSound;

class GameManager
{
public:

	GamePlay *gamePlay;
	MainMenu *mainMenu;
	BagMenu *bagMenu;
	BagItemSelect *bagItemSelect;
	BagItemToss* bagItemToss;
	BagItemTossConfirm* bagItemTossConfirm;
	BattleScreen* battleScreen;
	Intro *intro;
	GameStart* gameStart;

public:

	GameManager();
	~GameManager();

	void Init();
};


#endif