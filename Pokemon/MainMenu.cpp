#include "MainMenu.h"
#include "DataLoadManager.h"
#include "InputManager.h"
#include "UIManager.h"
#include "RunManager.h"

MainMenu::MainMenu()
	: curSelect(1), state(MainMenuState::Main), BaseClass()
{ }

void MainMenu::DrawMain(Graphics & g)
{
	// 우측 메뉴 배경 이미지
	UIManager::DrawDialogUI_IDX(g, COL - 4, 0, 4, ROW);

	// 하단 배경색
	SolidBrush brush(Color(248, 248, 248));
	g.FillRectangle(&brush, 0, (INT)((ROW - 2.5f) * MUL), (COL - 4) * MUL, (INT)(2.5f * MUL));

	// 메뉴 항목
	Font* font = DataLoadManager::GetFontB();
	SolidBrush strBrush(Color(255, 0, 0, 0));

	StringFormat fm;
	fm.SetAlignment(StringAlignmentCenter);
	fm.SetLineAlignment(StringAlignmentCenter);

	for (int i = 0; i < MENU_COUNT; ++i)
	{
		RectF menuItmeRect((COL - 4) * MUL, MUL + MENU_H * i, 4 * MUL, MENU_H);
		g.DrawString(MENU[i], -1, font, menuItmeRect, &fm, &strBrush);
	}

	RectF menuDescriptionRect(MUL, (INT)((ROW - 2.5f) * MUL), (COL - 5) * MUL, (INT)(2.5f * MUL));

	fm.SetAlignment(StringAlignmentNear);
	fm.SetLineAlignment(StringAlignmentCenter);

	g.DrawString(MENU_DESCREIPTION[curSelect - 1], -1, font, menuDescriptionRect, &fm, &strBrush);

	int pointSize = 4;
	g.FillRectangle(&strBrush, (int)((COL - 3.5f) * MUL), MUL + MENU_H * (curSelect - 1), pointSize * SCREEN_MUL, pointSize * SCREEN_MUL);
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
			break;

		case MainMenu::Pokemon:
			break;

		case MainMenu::Bag:
		{
			state = MainMenuState::Main;
			RunManager::SetTarget(gm->bagMenu);
		}
		break;

		case MainMenu::Pokegear:
			break;

		case MainMenu::Player:
			break;

		case MainMenu::Report:
			break;

		case MainMenu::Option:
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