#include "GameManager.h"
#include "GamePlay.h"
#include "MainMenu.h"
#include "BagMenu.h"
#include "BagItemSelect.h"
#include "BagItemToss.h"
#include "RunManager.h"
#include "BagItemTossConfirm.h"
#include "BattleScreen.h"
#include "Intro.h"
#include "GameStart.h"
#include "SoundManager.h"

GameManager::Game GameManager::game = GameManager::Game();

void GameManager::Game::Init()
{
	gamePlay = new GamePlay();
	mainMenu = new MainMenu();
	bagMenu = new BagMenu();
	bagItemSelect = new BagItemSelect();
	bagItemToss = new BagItemToss();
	bagItemTossConfirm = new BagItemTossConfirm();
	battleScreen = new BattleScreen();
	intro = new Intro();
	gameStart = new GameStart();

	gamePlay->ResourceInit();
	mainMenu->ResourceInit();
	bagMenu->ResourceInit();
	bagItemSelect->ResourceInit();
	bagItemToss->ResourceInit();
	bagItemTossConfirm->ResourceInit();
	battleScreen->ResourceInit();
	intro->ResourceInit();
	gameStart->ResourceInit();

	RunManager::SetTargetWithoutFade(intro);
}

void GameManager::Game::Reset()
{
	delete gamePlay;
	delete mainMenu;
	delete bagMenu;
	delete bagItemSelect;
	delete bagItemToss;
	delete bagItemTossConfirm;
	delete battleScreen;
	delete intro;
	delete gameStart;
}
