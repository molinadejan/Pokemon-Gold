#pragma once

#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "BaseClass.h"

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
	const TCHAR* MENU_DESCREIPTION[8] = { _T("포켓몬의 비밀이\n기록되어져 있다"), _T("같이 있는\n포켓몬의 상태"), _T("도구를 집어넣는\n포켓 낚시배낭"), _T("트레이너의 여행에\n도움이 되는 툴"), 
		_T("현재\n당신의 상태"), _T("잠시 쉬는 동안\n상태를 기록"), _T("시합의 룰 등의\n여러가지 변경"), _T("이 메뉴를 닫는다") };

	const int MENU_H = ((ROW - 2) * MUL) / MENU_COUNT;
	
	const RectF menuDescRect = { R(MUL), R((ROW - 2.5f) * MUL), R((COL - 5) * MUL), R(2.5f * MUL) };

	Rect GetCursorRect(int i) { return Rect((int)((COL - 4) * MUL), MUL + MENU_H * (i - 1), MUL, MUL); }
	RectF GetMenuItemRect(int i) { return RectF(R((COL - 3) * MUL), R(MUL + MENU_H * i), R(4 * MUL), R(MENU_H)); }

private:

	int curSelect;
	MainMenuState state;
	Image* dialog;

private:

	void DrawMain(Graphics &g);

public:

	MainMenu();
	~MainMenu() = default;

	void ResourceInit() override;
	void Draw(Graphics &g) override;
	void Update() override;
};

#endif // !__GAMEPLAYMAINMENU_H__

