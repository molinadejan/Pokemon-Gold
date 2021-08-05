#include "MainMenu.h"
#include "DataLoadManager.h"
#include "InputManager.h"
#include "UIManager.h"
#include "RunManager.h"

MainMenu::MainMenu()
	: curSelect(1), state(MainMenuState::Main)
{ }

void MainMenu::DrawMain(Graphics & g)
{
	// 우측 메뉴 배경 이미지
	UIManager::DrawDialogUI_IDX(g, COL - 4, 0, 4, ROW);

	g.FillRectangle(white, 0, (INT)((ROW - 2.5f) * MUL), (COL - 4) * MUL, (INT)(2.5f * MUL));

	// 메뉴 항목

	for (int i = 0; i < MENU_COUNT; ++i)
	{
		RectF menuItmeRect((COL - 4) * MUL, MUL + MENU_H * i, 4 * MUL, MENU_H);
		g.DrawString(MENU[i], -1, fontB, menuItmeRect, centerAlign, black);
	}

	RectF menuDescriptionRect(MUL, (INT)((ROW - 2.5f) * MUL), (COL - 5) * MUL, (INT)(2.5f * MUL));

	g.DrawString(MENU_DESCREIPTION[curSelect - 1], -1, fontB, menuDescriptionRect, leftAlign, black);

	int pointSize = 4;
	g.FillRectangle(black, (int)((COL - 3.5f) * MUL), MUL + MENU_H * (curSelect - 1), pointSize * SCREEN_MUL, pointSize * SCREEN_MUL);
}

void MainMenu::Update()
{
	switch (state)
	{
		case MainMenu::Main:
		{
			if (InputManager::GetKeyUp(VK_DOWN) && curSelect < MENU_COUNT)
				++curSelect;
			else if (InputManager::GetKeyUp(VK_UP) && curSelect > 1)
				--curSelect;

			if (InputManager::GetZ())
				state = (MainMenuState)curSelect;

			if (InputManager::GetEnter() || InputManager::GetX())
				RunManager::SetTarget(gm->gamePlay);
		}
		break;

		case MainMenu::PokeDex:
		{
			state = MainMenuState::Main;
		}
		break;

		case MainMenu::Pokemon:
		{
			state = MainMenuState::Main;
		}
		break;

		case MainMenu::Bag:
		{
			state = MainMenuState::Main;
			RunManager::SetTarget(gm->bagMenu);
		}
		break;

		case MainMenu::Pokegear:
		{
			state = MainMenuState::Main;
		}
		break;

		case MainMenu::Player:
		{
			state = MainMenuState::Main;
		}
		break;

		case MainMenu::Report:
		{
			state = MainMenuState::Main;
		}
		break;

		case MainMenu::Option:
		{
			state = MainMenuState::Main;
		}
		break;

		case MainMenu::Exit:
		{
			state = MainMenuState::Main;
			RunManager::SetTarget(gm->gamePlay);
		}
		break;
	}
}

void MainMenu::Draw(Graphics& g)
{
	gm->gamePlay->Draw(g);
	DrawMain(g);
}