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

class GameManager
{
private:

	class Game
	{
		friend GameManager;

	private:

		Game() = default;
		~Game() = default;

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

	private:

		void Init();
		void Reset();
	};

public:

	static Game game;

private:

	GameManager() = delete;
	~GameManager() = delete;

public:

	static void Init() { game.Init(); }
	static void Reset() { game.Reset(); }
};

#define GM GameManager

#endif