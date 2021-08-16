#include "MainMenu.h"
#include "DataLoadManager.h"
#include "InputManager.h"
#include "UIManager.h"
#include "RunManager.h"
#include "TransDatas.h"
#include "GdiplusElement.h"
#include "SoundManager.h"

MainMenu::MainMenu()
	: curSelect(0) { }

void MainMenu::DrawMain(Graphics & g)
{
	// 우측 메뉴 UI
	UIManager::DrawDialogUI_IDX(g, COL - 4, 0, 4, ROW);

	// 하단 UI
	g.FillRectangle(WHITE, 0, (INT)((ROW - 2.5f) * MUL), (COL - 4) * MUL, (INT)(2.5f * MUL));

	// 메뉴 항목
	for (int i = 0; i < MENU_COUNT; ++i)
	{
		TransString(buffer, "main_menu_" + std::to_string(i));
		g.DrawString(buffer, -1, FONT_BIG, GetMenuItemRect(i), LEFT_ALIGN, BLACK);
	}

	// 메뉴 설명
	TransString(buffer, "main_menu_desc_" + std::to_string(curSelect));
	g.DrawString(buffer, -1, FONT_BIG, menuDescRect, LEFT_ALIGN, BLACK);

	// 커서
	g.DrawImage(DM::GetDialogBase(), GetCursorRect(curSelect), 3 * PIXEL, 0, PIXEL, PIXEL, UnitPixel);
}

void MainMenu::Update()
{
	if (GET_KEY_DOWN && curSelect < MENU_COUNT - 1)
		++curSelect;
	else if (GET_KEY_UP && curSelect > 0)
		--curSelect;

	if (GET_KEY_Z)
	{
		SM::PlayEffect("button");

		switch (curSelect)
		{
			case PokeDex:
			{
			}
			break;

			case Pokemon:
			{
			}
			break;

			case Bag:
			{
				RunManager::SetTargetWithoutFade(gm->bagMenu);
			}
			break;

			case Pokegear:
			{
			}
			break;

			case Player:
			{
			}
			break;

			case Report:
			{
			}
			break;

			case Option:
			{
			}
			break;

			case Exit:
			{
				RunManager::SetTargetWithoutFade(gm->gamePlay);
			}
			break;
		}
	}

	if (GET_KEY_ENTER || GET_KEY_X)
		RunManager::SetTargetWithoutFade(gm->gamePlay);	
}


void MainMenu::Draw(Graphics& g)
{
	gm->gamePlay->Draw(g);
	DrawMain(g);
}