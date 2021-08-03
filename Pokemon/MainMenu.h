#pragma once

#ifndef __GAMEPLAYMAINMENU_H__
#define __GAMEPLAYMAINMENU_H__

#include "framework.h"
#include "BagMenu.h"

using namespace Gdiplus;

class MainMenu
{
public:
	enum MainMenuState
	{
		Main = 0,
		PokeDex = 1,
		Pokemon = 2,
		Bag = 3,
		Pokegear = 4,
		Player = 5,
		Report = 6,
		Option = 7,
		Exit = 8
	};


private:
	const int MENU_COUNT = 8;

private:

	int curSelect;
	MainMenuState state;

	BagMenu bagMenu;

private:

	void DrawMain(Graphics &g);
	void UpdateMain();

public:

	MainMenu();

	MainMenuState GetState();

	void Init();
	void DrawMainMenu(Graphics &g);
	void UpdateMainMenu();
};

#endif // !__GAMEPLAYMAINMENU_H__

