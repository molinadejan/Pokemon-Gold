#pragma once

#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "framework.h"
#include "BagMenu.h"
#include "BaseClass.h"
#include "GameManager.h"

using namespace Gdiplus;

class GameManager;

class MainMenu : public BaseClass
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
	const TCHAR* MENU[8] = { _T("도감"), _T("포켓몬"), _T("가방"), _T("포켓기어"), _T("플레이어"), _T("레포트"), _T("설정"), _T("닫기") };
	const int MENU_H = ((ROW - 2) * MUL) / MENU_COUNT;

private:

	GameManager* gm;

	int curSelect;
	MainMenuState state;

private:

	void DrawMain(Graphics &g);

public:

	MainMenu();
	~MainMenu() = default;

	void SetManager(GameManager* _gm);
	void Draw(Graphics &g) override;
	void Update() override;
};

#endif // !__GAMEPLAYMAINMENU_H__

