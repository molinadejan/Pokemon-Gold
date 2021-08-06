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

