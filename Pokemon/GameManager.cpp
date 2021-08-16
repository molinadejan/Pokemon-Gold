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
#include "CSound.h"
#include "SoundManager.h"

GameManager:: GameManager() { }

GameManager::~GameManager() 
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

void GameManager::Init()
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

	gamePlay->SetManager(this);
	mainMenu->SetManager(this);
	bagMenu->SetManager(this);
	bagItemSelect->SetManager(this);
	bagItemToss->SetManager(this);
	bagItemTossConfirm->SetManager(this);
	battleScreen->SetManager(this);
	intro->SetManager(this);
	gameStart->SetManager(this);

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


