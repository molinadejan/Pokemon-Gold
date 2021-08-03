#include "MainMenu.h"
#include "DataLoadManager.h"
#include "InputManager.h"
#include "BagMenu.h"

void MainMenu::DrawMain(Graphics & g)
{
	Image* ui = DataLoadManager::GetUI_menu();

	Rect rect((COL - 4) * PIXEL * SCREEN_MUL, 0, ui->GetWidth() * SCREEN_MUL, ui->GetHeight() * SCREEN_MUL);
	g.DrawImage(ui, rect);

	SolidBrush brush(Color(255, 255, 255));
	g.FillRectangle(&brush, 0, (ROW - 2) * PIXEL * SCREEN_MUL, (COL - 4) * PIXEL * SCREEN_MUL, 2 * PIXEL * SCREEN_MUL);

	Font* font = DataLoadManager::GetFontB();

	TCHAR buffer[256];
	SolidBrush strBrush(Color(255, 0, 0, 0));

	_stprintf_s(buffer, _T("도감\n포켓몬\n가방\n포켓기어\n플레이어\n레포트\n설정\n닫기"));

	RectF rectF1((COL - 3) * PIXEL * SCREEN_MUL, PIXEL * SCREEN_MUL, 3 * PIXEL * SCREEN_MUL, SCREEN_SIZE_Y);
	g.DrawString(buffer, -1, font, rectF1, NULL, &strBrush);

	g.FillRectangle(&strBrush, (int)((COL - 3.5f) * PIXEL * SCREEN_MUL), PIXEL * SCREEN_MUL + 12 * (curSelect - 1) * SCREEN_MUL + 8, 4 * SCREEN_MUL, 4 * SCREEN_MUL);
}

void MainMenu::UpdateMain()
{
	if (InputManager::GetKeyUp(VK_DOWN) && curSelect < MENU_COUNT)
		++curSelect;
	else if (InputManager::GetKeyUp(VK_UP) && curSelect > 1)
		--curSelect;

	if (InputManager::GetZ())
		state = (MainMenuState)curSelect;
}

MainMenu::MainMenuState MainMenu::GetState()
{
	return state;
}

MainMenu::MainMenu()
	: curSelect(1)
{ }

void MainMenu::Init()
{
	state = MainMenuState::Main;
}

void MainMenu::DrawMainMenu(Graphics& g)
{
	switch (state)
	{
		case MainMenuState::Main:
			DrawMain(g);
			break;

		case MainMenuState::Bag:
			bagMenu.DrawBag(g);
			break;
	}
}

void MainMenu::UpdateMainMenu()
{
	switch (state)
	{
		case MainMenu::Main:
			UpdateMain();
			break;

		case MainMenu::PokeDex:
			break;

		case MainMenu::Pokemon:
			break;

		case MainMenu::Bag:

			if (InputManager::GetX())
				state = MainMenuState::Main;

			bagMenu.UpdateBag();

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
			break;
	}
}
