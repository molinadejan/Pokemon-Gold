#include "MainMenu.h"
#include "DataLoadManager.h"
#include "InputManager.h"
#include "UIManager.h"
#include "RunManager.h"
#include "TransDatas.h"
#include "GdiplusElement.h"

using std::to_string;
using std::wstring;

MainMenu::MainMenu()
	: curSelect(1), state(Main)
{ }

void MainMenu::ResourceInit()
{
	BaseClass::ResourceInit();
	dialog = DM::GetDialogBase();
}

void MainMenu::DrawMain(Graphics & g)
{
	// 우측 메뉴 UI
	UIManager::DrawDialogUI_IDX(g, COL - 4, 0, 4, ROW);

	// 하단 UI
	g.FillRectangle(WHITE, 0, (INT)((ROW - 2.5f) * MUL), (COL - 4) * MUL, (INT)(2.5f * MUL));

	// 메뉴 항목
	for (int i = 0; i < MENU_COUNT; ++i)
	{
		TransString(buffer, "main_menu_" + to_string(i));
		g.DrawString(buffer, -1, FONT_BIG, GetMenuItemRect(i), LEFT_ALIGN, BLACK);
	}

	// 메뉴 설명
	TransString(buffer, "main_menu_desc_" + to_string(curSelect - 1));
	g.DrawString(buffer, -1, FONT_BIG, menuDescRect, LEFT_ALIGN, BLACK);

	// 커서
	g.DrawImage(dialog, GetCursorRect(curSelect), 3 * PIXEL, 0, PIXEL, PIXEL, UnitPixel);
}

void MainMenu::Update()
{
	switch (state)
	{
		case Main:
		{
			if (GET_KEY_DOWN && curSelect < MENU_COUNT)
				++curSelect;
			else if (GET_KEY_UP && curSelect > 1)
				--curSelect;

			if (GET_KEY_Z)
				state = (MainMenuState)curSelect;

			if (GET_KEY_ENTER || GET_KEY_X)
				RunManager::SetTarget(gm->gamePlay);
		}
		break;

		case PokeDex:
		{
			state = Main;
		}
		break;

		case Pokemon:
		{
			state = Main;
		}
		break;

		case Bag:
		{
			state = Main;
			RunManager::SetTarget(gm->bagMenu);
		}
		break;

		case Pokegear:
		{
			state = Main;
		}
		break;

		case Player:
		{
			state = Main;
		}
		break;

		case Report:
		{
			state = Main;
		}
		break;

		case Option:
		{
			state = Main;
		}
		break;

		case Exit:
		{
			state = Main;
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