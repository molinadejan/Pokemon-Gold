#include "GameStart.h"
#include "GdiplusElement.h"
#include "InputManager.h"
#include "RunManager.h"
#include "UIManager.h"
#include "GdiplusElement.h"
#include "TransDatas.h"
#include "DataLoadManager.h"
#include "SoundManager.h"
#include <fstream>

using std::fstream;

GameStart::GameStart() { }

void GameStart::Init()
{
	dialogImg = DM::GetDialogBase();

	fstream openFile("data/save/save.json");

	if (openFile.is_open())
	{
		isSaveFile = true;
		openFile.close();
	}
	else isSaveFile = false;

	curSelectMenu = 0;
	menuCount = isSaveFile ? 2 : 1;

	SM::ChangeBgmWithoutFade("gameStart", true);
}

void GameStart::Reset()
{

}

void GameStart::Update()
{
	if (GET_KEY_UP && curSelectMenu > 0)
		--curSelectMenu;
	else if (GET_KEY_DOWN && curSelectMenu < menuCount - 1)
		++curSelectMenu;

	if (GET_KEY_Z)
	{
		PlayerData* data = new PlayerData();
		SM::PlayEffect("button");

		if (isSaveFile)
		{

		}
		else
		{
			data->locationID = "player_room";
			data->pos = { 1, 4 };
			data->pokemonInBag.push_back(new PokemonIndiv(1, 16));

			DM::SetPlayerData(data);

			for (int i = 1; i <= 60; ++i)
				DM::AddItemToInventory(i, rand() % 99 + 1);

			RunManager::SetTarget(gm->gamePlay);
		}
	}

	if (GET_KEY_X)
		RunManager::SetTarget(gm->intro, 2.0f);
}

void GameStart::Draw(Graphics & g)
{
	g.FillRectangle(WHITE, 0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
	UIManager::DrawDialogUI_IDX(g, 0, 0, 8, isSaveFile ? 3 : 2);

	if (isSaveFile)
	{
		for (int i = 0; i < 2; ++i)
		{
			TransString(buffer, "game_start_menu_" + std::to_string(i));
			g.DrawString(buffer, -1, FONT_BIG, menuRects[i], LEFT_ALIGN, BLACK);
		}
	}
	else
	{
		TransString(buffer, "game_start_menu_1");
		g.DrawString(buffer, -1, FONT_BIG, menuRects[0], LEFT_ALIGN, BLACK);
	}

	g.DrawImage(dialogImg, cursorRects[curSelectMenu], 3 * PIXEL, 0, PIXEL, PIXEL, UnitPixel);
}
