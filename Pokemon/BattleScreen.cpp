#include "BattleScreen.h"
#include "framework.h"
#include "GdiplusElement.h"
#include "DataLoadManager.h"
#include "InputManager.h"
#include "RunManager.h"
#include "GamePlay.h"
#include "UIManager.h"
#include "TransDatas.h"
#include "GdiplusElement.h"
#include "PokemonCalculator.h"

void BattleScreen::InitWildBattle(int pokemonID, int level)
{
	battleType = Wild;
	curState = Encounter;

	enemyPokemon = new PokemonIndiv(pokemonID, level);

	playerPokemon = DM::GetPlayerData()->pokemonInBag[0];

	curMenuSelect = 0;
	curSkillSelect = 0;
}

void BattleScreen::InitTrainerBattle(int trainerID)
{
	battleType = Trainer;
	curState = Encounter;
}

void BattleScreen::DeleteData()
{
	if (battleType == Wild)
	{
		delete enemyPokemon;
		//delete battleData;
	}
	else if (battleType == Trainer)
	{

	}
}

void BattleScreen::DrawBackground(Graphics & g)
{
	g.FillRectangle(WHITE, 0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
}

void BattleScreen::DrawMainDialog(Graphics & g)
{
	UIManager::DrawDialogUI_IDX(g, 0, 6, COL, 3);
}

void BattleScreen::DrawBattleMenuDialog(Graphics & g)
{
	UIManager::DrawDialogUI_IDX(g, 4, 6, COL - 4, 3);
}

void BattleScreen::DrawMenuCursor(Graphics & g)
{
	g.DrawImage(battleUI, battleMenuCursorRect[curMenuSelect], 6 * PIXEL, 3 * PIXEL, PIXEL, PIXEL, UnitPixel);
}

void BattleScreen::DrawFightMenuDialog(Graphics & g)
{
	UIManager::DrawDialogUI_IDX(g, 0.0f, 4.0f, 4.5f, 5.0f);
}

void BattleScreen::DrawEnemyPokemonInfo(Graphics & g)
{
	g.DrawImage(battleUI, enemyPokemonInfoRect, 6 * PIXEL, 0, 6 * PIXEL, 2 * PIXEL, UnitPixel);
}

void BattleScreen::DrawPlayerPokemonInfo(Graphics & g)
{
	g.DrawImage(battleUI, playerPokemonInfoRect, 0, 0, 6 * PIXEL, 2 * PIXEL, UnitPixel);
}

void BattleScreen::DrawPlayerInfo(Graphics & g)
{
	g.DrawImage(battleUI, playerInfoRect, 6 * PIXEL, 2 * PIXEL, 6 * PIXEL, PIXEL, UnitPixel);
}

void BattleScreen::DrawEnemyInfo(Graphics & g)
{
	g.DrawImage(battleUI, enemyInfoRect, 0, 2 * PIXEL, 6 * PIXEL, PIXEL, UnitPixel);
}

void BattleScreen::DrawPlayerPokemon(Graphics & g)
{
	int id = playerPokemon->id;

	int x = (id - 1) % 10;
	int y = ((id - 1) / 10) * 2 + 1;

	g.DrawImage(pokemonPic, myRect, x * POKE_PIXEL, y * POKE_PIXEL, POKE_PIXEL, POKE_PIXEL, UnitPixel);

	PokemonDesc* desc = DM::GetPokemonDesc(id);
	PokemonData* data = DM::GetPokemonData(id);
	
	_tcscpy_s(buffer, desc->name.length() + 1, CA2T(desc->name.c_str()));
	g.DrawString(buffer, -1, FONT_MEDIUM, playerPokemonNameRect, RIGHT_ALIGN, BLACK);

	_stprintf_s(buffer, _T("%d"), playerPokemon->level);
	g.DrawString(buffer, -1, FONT_MEDIUM, playerPokemonLevelRect, LEFT_ALIGN, BLACK);

	_stprintf_s(buffer, _T("%d"), playerPokemon->hp);
	g.DrawString(buffer, -1, FONT_MEDIUM, playerPokemonCurHPRect, RIGHT_ALIGN, BLACK);

	_stprintf_s(buffer, _T("%d"), CalHP(data->HP, playerPokemon->level));
	g.DrawString(buffer, -1, FONT_MEDIUM, playerPokemonMaxHPRect, RIGHT_ALIGN, BLACK);

}

void BattleScreen::DrawEnemyPokemon(Graphics & g)
{
	int id = enemyPokemon->id;

	int x = (id - 1) % 10;
	int y = ((id - 1) / 10) * 2;

	g.DrawImage(pokemonPic, enemyRect, x * POKE_PIXEL, y * POKE_PIXEL, POKE_PIXEL, POKE_PIXEL, UnitPixel);

	PokemonDesc* desc = DM::GetPokemonDesc(id);
	PokemonData* data = DM::GetPokemonData(id);

	_tcscpy_s(buffer, desc->name.length() + 1, CA2T(desc->name.c_str()));
	g.DrawString(buffer, -1, FONT_MEDIUM, enemyPokemonNameRect, RIGHT_ALIGN, BLACK);

	_stprintf_s(buffer, _T("%d"), enemyPokemon->level);
	g.DrawString(buffer, -1, FONT_MEDIUM, enemyPokemonLevelRect, LEFT_ALIGN, BLACK);
}

void BattleScreen::DrawPlayer(Graphics & g)
{
	g.DrawImage(battleUI, myRect, 9 * PIXEL, 4 * PIXEL, 3 * PIXEL, 3 * PIXEL, UnitPixel);
}

void BattleScreen::DrawNPC(Graphics & g)
{

}

void BattleScreen::ResourceInit()
{
	battleUI = DM::GetBattleUI();
	pokemonPic = DM::GetPokemonPicture();
}

void BattleScreen::Update()
{
	switch (curState)
	{
		case Encounter:
		{
			if (GET_KEY_Z || GET_KEY_X)
				curState = Dispatch;
		}
		break;

		case Dispatch:
		{
			if (GET_KEY_Z || GET_KEY_X)
				curState = SelectMenu;
		}
		break;

		case SelectMenu:
		{
			if (GET_KEY_RIGHT && (curMenuSelect == 0 || curMenuSelect == 2))
				++curMenuSelect;
			else if (GET_KEY_LEFT && (curMenuSelect == 1 || curMenuSelect == 3))
				--curMenuSelect;
			else if (GET_KEY_DOWN && (curMenuSelect == 0 || curMenuSelect == 1))
				curMenuSelect += 2;
			else if (GET_KEY_UP && (curMenuSelect == 2 || curMenuSelect == 3))
				curMenuSelect -= 2;

			if (GET_KEY_Z)
			{
				if (curMenuSelect == 0)
					curState = FightMenu;
				else if (curMenuSelect == 1)
					;
				else if (curMenuSelect == 2)
					;
				else if (curMenuSelect == 3)
					curState = RunSuccess;
			}
		}
		break;

		case FightMenu:
		{
			if (GET_KEY_UP && curSkillSelect > 0)
				--curSkillSelect;
			else if (GET_KEY_DOWN && curSkillSelect < 3 && playerPokemon->skills[curSkillSelect + 1] != -1)
				++curSkillSelect;

			if (GET_KEY_Z)
			{

			}

			if (GET_KEY_X)
			{
				curState = SelectMenu;
			}
		}
		break;

		case RunSuccess:
		{
			if (GET_KEY_Z)
			{
				DeleteData();
				RunManager::SetTarget(gm->gamePlay);
			}
		}
		break;
	}
}

void BattleScreen::Draw(Graphics & g)
{
	switch (curState)
	{
		case Encounter:
		{
			DrawBackground(g);
			DrawPlayer(g);
			DrawEnemyPokemon(g);
			DrawMainDialog(g);

			DrawPlayerInfo(g);
			DrawEnemyPokemonInfo(g);

			string wild_pokemon_name = DM::GetPokemonDesc(enemyPokemon->id)->name;
			TransString(buffer, "wild_encounter", 1, TokenChange("pokemon_name", wild_pokemon_name));
			g.DrawString(buffer, -1, FONT_BIG, dialogRect, LEFT_ALIGN, BLACK);
		}
		break;

		case Dispatch:
		{
			DrawBackground(g);
			DrawPlayerPokemon(g);
			DrawEnemyPokemon(g);
			DrawMainDialog(g);

			DrawEnemyPokemonInfo(g);
			DrawPlayerPokemonInfo(g);
			
			string my_pokemon_name = DM::GetPokemonDesc(playerPokemon->id)->name;
			TransString(buffer, "pokemon_dispatch", 1, TokenChange("pokemon_name", my_pokemon_name));
			g.DrawString(buffer, -1, FONT_BIG, dialogRect, LEFT_ALIGN, BLACK);
		}
		break;

		case SelectMenu:
		{
			DrawBackground(g);
			DrawPlayerPokemon(g);
			DrawEnemyPokemon(g);
			DrawMainDialog(g);

			DrawBattleMenuDialog(g);

			DrawEnemyPokemonInfo(g);
			DrawPlayerPokemonInfo(g);

			for (int i = 0; i < 4; ++i)
			{
				TransString(buffer, "battle_menu_" + std::to_string(i));
				g.DrawString(buffer, -1, FONT_BIG, battleMenuRect[i], LEFT_ALIGN, BLACK);
			}

			DrawMenuCursor(g);
		}
		break;

		case FightMenu:
		{
			DrawBackground(g);
			DrawPlayerPokemon(g);
			DrawEnemyPokemon(g);

			DrawEnemyPokemonInfo(g);
			DrawPlayerPokemonInfo(g);

			DrawFightMenuDialog(g);
			DrawBattleMenuDialog(g);

			for (int i = 0; i < 4; ++i)
			{
				int id = playerPokemon->skills[i];

				if (id != -1)
				{
					string name = DM::GetSkillDesc(id)->name;
					_tcscpy_s(buffer, name.length() + 1, CA2T(name.c_str()));
				}
				else _stprintf_s(buffer, _T("%c"), '-');

				g.DrawString(buffer, -1, FONT_BIG, skillRect[i], LEFT_ALIGN, BLACK);
			}

			g.DrawImage(battleUI, skillCursorRect[curSkillSelect], 6 * PIXEL, 3 * PIXEL, PIXEL, PIXEL, UnitPixel);
		}
		break;

		case RunSuccess:
		{
			DrawBackground(g);
			DrawPlayerPokemon(g);
			DrawEnemyPokemon(g);

			DrawEnemyPokemonInfo(g);
			DrawPlayerPokemonInfo(g);

			DrawMainDialog(g);

			TransString(buffer, "run_success");
			g.DrawString(buffer, -1, FONT_BIG, dialogRect, LEFT_ALIGN, BLACK);
		}
		break;
	}
}

