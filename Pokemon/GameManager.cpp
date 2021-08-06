#include "GameManager.h"
#include "GamePlay.h"
#include "MainMenu.h"
#include "GameFadeInOut.h"
#include "BagMenu.h"
#include "BagItemSelect.h"
#include "BagItemToss.h"
#include "RunManager.h"
#include "BagItemTossConfirm.h"

GameManager:: GameManager() { }

GameManager::~GameManager() 
{
	delete gamePlay;
	delete mainMenu;
	delete gameFadeInOut;
	delete bagMenu;
	delete bagItemSelect;
	delete bagItemToss;
	delete bagItemTossConfirm;
}

void GameManager::Init()
{
	gamePlay = new GamePlay();
	mainMenu = new MainMenu();
	gameFadeInOut = new GameFadeInOut();
	bagMenu = new BagMenu();
	bagItemSelect = new BagItemSelect();
	bagItemToss = new BagItemToss();
	bagItemTossConfirm = new BagItemTossConfirm();

	gamePlay->SetManager(this);
	mainMenu->SetManager(this);
	gameFadeInOut->SetManager(this);
	bagMenu->SetManager(this);
	bagItemSelect->SetManager(this);
	bagItemToss->SetManager(this);
	bagItemTossConfirm->SetManager(this);

	gamePlay->ResourceInit();
	mainMenu->ResourceInit();
	gameFadeInOut->ResourceInit();
	bagMenu->ResourceInit();
	bagItemSelect->ResourceInit();
	bagItemToss->ResourceInit();
	bagItemTossConfirm->ResourceInit();

	RunManager::SetTarget(gamePlay);
}


