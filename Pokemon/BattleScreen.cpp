#include "BattleScreen.h"
#include "framework.h"
#include "GdiplusElement.h"
#include "DataLoadManager.h"
#include "InputManager.h"
#include "RunManager.h"
#include "GamePlay.h"
#include "UIManager.h"

void BattleScreen::InitWildBattle(int pokemonID, int level)
{
	battleType = Wild;

	indiv = new PokemonIndiv(pokemonID, level);
	//battleData = new PokemonBattleData(pokemonID);
}

void BattleScreen::DeleteData()
{
	if (battleType == Wild)
	{
		delete indiv;
		//delete battleData;
	}
	else if (battleType == Trainer)
	{

	}
}

void BattleScreen::InitTrainerBattle(int trainerID)
{

}

void BattleScreen::ResourceInit()
{
	battleUI = DM::GetBattleUI();
	pokemonPic = DM::GetPokemonPicture();
}

void BattleScreen::Update()
{
	if (IM::GetKeyUp('O'))
	{
		DeleteData();
		RunManager::SetTarget(gm->gamePlay);
	}
}

void BattleScreen::Draw(Graphics & g)
{
	g.FillRectangle(WHITE, 0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);

	UIManager::DrawDialogUI_IDX(g, 0, 6, COL, 3);

	// Draw Player;
	Rect playerRect(MUL, 3 * MUL, 3 * MUL, 3 * MUL);
	g.DrawImage(battleUI, playerRect, 9 * PIXEL, 4 * PIXEL, 3 * PIXEL, 3 * PIXEL, UnitPixel);

	// Draw Wild Monster
	Rect pokemonRect(6 * MUL, 0, 3 * MUL, 3 * MUL);

	int x = (indiv->id - 1) % 10;
	int y = (indiv->id - 1) / 10;

	g.DrawImage(pokemonPic, pokemonRect, x * POKE_PIXEL, y * POKE_PIXEL, POKE_PIXEL, POKE_PIXEL, UnitPixel);

	// draw info bar
	Rect barRect(4 * MUL, 5 * MUL, 6 * MUL, MUL);
	g.DrawImage(battleUI, barRect, 0, 2 * PIXEL, 6 * PIXEL, PIXEL, UnitPixel);

	for (int i = 0; i < 6; ++i)
	{
		Rect barRect(5 * MUL + 8 * SCREEN_MUL + 8 * i * SCREEN_MUL, 5 * MUL + 4 * SCREEN_MUL, 7 * SCREEN_MUL, 7 * SCREEN_MUL);
		g.DrawImage(battleUI, barRect, 32, 48, 7, 7, UnitPixel);
	}
}

