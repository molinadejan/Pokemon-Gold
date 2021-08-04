#include "GameManager.h"

GameManager:: GameManager() { }

GameManager::~GameManager() 
{
	delete gamePlay;
	delete mainMenu;
}

void GameManager::Init()
{
	gamePlay = new GamePlay();
	mainMenu = new MainMenu();
	gameFadeInOut = new GameFadeInOut();

	gamePlay->SetManager(this);
	mainMenu->SetManager(this);
	gameFadeInOut->SetManager(this);

	RunManager::SetTarget(gamePlay);
}


