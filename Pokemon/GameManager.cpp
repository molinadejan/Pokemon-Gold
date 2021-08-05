#include "GameManager.h"
#include "GamePlay.h"
#include "MainMenu.h"
#include "GameFadeInOut.h"
#include "BagMenu.h"
#include "RunManager.h"

GameManager:: GameManager() { }

GameManager::~GameManager() 
{
	delete gamePlay;
	delete mainMenu;
	delete gameFadeInOut;
	delete bagMenu;
}

void GameManager::Init()
{
	gamePlay = new GamePlay();
	mainMenu = new MainMenu();
	gameFadeInOut = new GameFadeInOut();
	bagMenu = new BagMenu();

	gamePlay->SetManager(this);
	mainMenu->SetManager(this);
	gameFadeInOut->SetManager(this);
	bagMenu->SetManager(this);

	gamePlay->ResourceInit();
	mainMenu->ResourceInit();
	gameFadeInOut->ResourceInit();
	bagMenu->ResourceInit();

	RunManager::SetTarget(gamePlay);
}


