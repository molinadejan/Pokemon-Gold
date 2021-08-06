#include "MainMenu.h"
#include "DataLoadManager.h"
#include "InputManager.h"
#include "UIManager.h"
#include "RunManager.h"
#include "TransDatas.h"

using std::to_string;
using std::wstring;

MainMenu::MainMenu()
	: curSelect(1), state(MainMenuState::Main)
{ }

void MainMenu::ResourceInit()
{
	BaseClass::ResourceInit();
	dialog = DataLoadManager::GetUI_Dialog_Base();
}

void MainMenu::DrawMain(Graphics & g)
{
	// 우측 메뉴 UI
	UIManager::DrawDialogUI_IDX(g, COL - 4, 0, 4, ROW);

	// 하단 UI
	g.FillRectangle(white, 0, (INT)((ROW - 2.5f) * MUL), (COL - 4) * MUL, (INT)(2.5f * MUL));

	// 메뉴 항목
	for (int i = 0; i < MENU_COUNT; ++i)
	{
		TransString(buffer, "main_menu_" + to_string(i));
		g.DrawString(buffer, -1, fontB, GetMenuItemRect(i), leftAlign, black);
	}

	// 메뉴 설명
	TransString(buffer, "main_menu_desc_" + to_string(curSelect - 1));
	g.DrawString(buffer, -1, fontB, menuDescRect, leftAlign, black);

	// 커서
	g.DrawImage(dialog, GetCursorRect(curSelect), 3 * PIXEL, 0, PIXEL, PIXEL, UnitPixel);
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