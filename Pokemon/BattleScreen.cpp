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
	curState = InitToEncounter;

	enemyPokemon = new PokemonIndiv(pokemonID, level);

	playerPokemon = DM::GetPlayerData()->pokemonInBag[0];

	curMenuSelect = 0;
	curSkillSelect = 0;

	player = new MovingObject(battleUI, PointF(R(10 * MUL), R(3 * MUL)), Point(3 * MUL, 3 * MUL), Rect(9 * PIXEL, 4 * PIXEL, 3 * PIXEL, 3 * PIXEL));
	enemy = new MovingObject(pokemonPic, PointF(R(-3 * MUL), R(0)), Point(3 * MUL, 3 * MUL), DM::GetFrontPokemonImageRect(enemyPokemon->id));
	dialogShow = new DialogShow();
	anim = new AnimationObject(battleUI, PointF(R(0.5f * MUL), R(3.5f * MUL)), Point(3 * MUL, 3 * MUL), DM::GetAnimRect("pokemon_dispatch"));


	player->MoveToInit(PointF(R(0.5f * MUL), R(3 * MUL)), 1.2f);
	enemy->MoveToInit(PointF(R(6.5f * MUL), R(0)), 1.2f);

	dialogShow->Push(TransString(NULL, "wonder"));
	dialogShow->Push(TransString(NULL, "wild_encounter", 1, TokenChange("pokemon_name", DM::GetPokemonDesc(enemyPokemon->id)->name)));

	player->Start();
	enemy->Start();
}

void BattleScreen::InitTrainerBattle(int trainerID)
{
	battleType = Trainer;
	curState = Encounter;
}

void BattleScreen::Reset()
{
	if (battleType == Wild)
	{
		delete enemyPokemon;

		delete enemy;
		delete player;
		delete dialogShow;
		delete anim;
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

void BattleScreen::DrawBattleMenu(Graphics & g)
{
	for (int i = 0; i < 4; ++i)
	{
		TransString(buffer, "battle_menu_" + std::to_string(i));
		g.DrawString(buffer, -1, FONT_BIG, battleMenuRect[i], LEFT_ALIGN, BLACK);
	}
}

void BattleScreen::DrawMenuCursor(Graphics & g)
{
	g.DrawImage(battleUI, battleMenuCursorRect[curMenuSelect], 6 * PIXEL, 3 * PIXEL, PIXEL, PIXEL, UnitPixel);
}

void BattleScreen::DrawSkillCursor(Graphics & g)
{
	g.DrawImage(battleUI, skillCursorRect[curSkillSelect], 6 * PIXEL, 3 * PIXEL, PIXEL, PIXEL, UnitPixel);
}

void BattleScreen::DrawFightMenuDialog(Graphics & g)
{
	UIManager::DrawDialogUI_IDX(g, 0.0f, 4.0f, 4.5f, 5.0f);
}

void BattleScreen::DrawFightMenu(Graphics & g)
{
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
}

void BattleScreen::DrawSkillInfo(Graphics & g)
{
	int id = playerPokemon->skills[curSkillSelect];

	SkillData* data = DM::GetSkillData(id);

	int curpp = playerPokemon->pps[curSkillSelect];
	_stprintf_s(buffer, _T("%2d/%2d"), curpp, data->pp);
	g.DrawString(buffer, -1, FONT_BIG, maxPPRect, RIGHT_ALIGN, BLACK);
	
	_stprintf_s(buffer, _T("기술타입/"));
	g.DrawString(buffer, -1, FONT_BIG, skillTypeRect, LEFT_ALIGN, BLACK);
	
	TransString(buffer, "type_" + std::to_string(data->type));
	g.DrawString(buffer, -1, FONT_BIG, skillTypeNameRect, LEFT_ALIGN, BLACK);
}

void BattleScreen::DrawEnemyPokemonInfo(Graphics & g)
{
	g.DrawImage(battleUI, enemyPokemonInfoRect, 6 * PIXEL, 0, 6 * PIXEL, 2 * PIXEL, UnitPixel);

	int id = enemyPokemon->id;

	PokemonDesc* desc = DM::GetPokemonDesc(id);
	PokemonData* data = DM::GetPokemonData(id);

	_tcscpy_s(buffer, desc->name.length() + 1, CA2T(desc->name.c_str()));
	g.DrawString(buffer, -1, FONT_MEDIUM, enemyPokemonNameRect, RIGHT_ALIGN, BLACK);

	_stprintf_s(buffer, _T("%d"), enemyPokemon->level);
	g.DrawString(buffer, -1, FONT_MEDIUM, enemyPokemonLevelRect, LEFT_ALIGN, BLACK);

	int maxHP = CalHP(data->HP, enemyPokemon->level);
	int curHP = enemyPokemon->hp;

	float ratio = curHP / (float)maxHP;

	Rect hpRect = { 2 * MUL, 1 * MUL, INT(3 * MUL * ratio), MUL };

	g.DrawImage(battleUI, hpRect, 10 * PIXEL, 3 * PIXEL, PIXEL, PIXEL, UnitPixel);
}

void BattleScreen::DrawPlayerPokemonInfo(Graphics & g)
{
	g.DrawImage(battleUI, playerPokemonInfoRect, 0, 0, 6 * PIXEL, 2 * PIXEL, UnitPixel);

	int id = playerPokemon->id;

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

	int maxHP = CalHP(data->HP, playerPokemon->level);
	int curHP = playerPokemon->hp;

	float ratio = curHP / (float)maxHP;

	Rect hpRect = {6 * MUL, 4 * MUL, INT(3 * MUL * ratio), MUL};

	g.DrawImage(battleUI, hpRect, 8 * PIXEL, 3 * PIXEL, PIXEL, PIXEL, UnitPixel);
}

void BattleScreen::DrawPlayerInfo(Graphics & g)
{
	g.DrawImage(battleUI, playerInfoRect, 0, 2 * PIXEL, 6 * PIXEL, PIXEL, UnitPixel);
}

void BattleScreen::DrawEnemyInfo(Graphics & g)
{
	g.DrawImage(battleUI, enemyInfoRect, 6 * PIXEL, 2 * PIXEL, 6 * PIXEL, PIXEL, UnitPixel);
}

//void BattleScreen::DrawPlayerPokemon(Graphics & g)
//{
//	int id = playerPokemon->id;
//
//	PokemonDesc* desc = DM::GetPokemonDesc(id);
//	PokemonData* data = DM::GetPokemonData(id);
//	
//	_tcscpy_s(buffer, desc->name.length() + 1, CA2T(desc->name.c_str()));
//	g.DrawString(buffer, -1, FONT_MEDIUM, playerPokemonNameRect, RIGHT_ALIGN, BLACK);
//
//	_stprintf_s(buffer, _T("%d"), playerPokemon->level);
//	g.DrawString(buffer, -1, FONT_MEDIUM, playerPokemonLevelRect, LEFT_ALIGN, BLACK);
//
//	_stprintf_s(buffer, _T("%d"), playerPokemon->hp);
//	g.DrawString(buffer, -1, FONT_MEDIUM, playerPokemonCurHPRect, RIGHT_ALIGN, BLACK);
//
//	_stprintf_s(buffer, _T("%d"), CalHP(data->HP, playerPokemon->level));
//	g.DrawString(buffer, -1, FONT_MEDIUM, playerPokemonMaxHPRect, RIGHT_ALIGN, BLACK);
//}
//
//void BattleScreen::DrawEnemyPokemon(Graphics & g)
//{
//	int id = enemyPokemon->id;
//
//	PokemonDesc* desc = DM::GetPokemonDesc(id);
//	PokemonData* data = DM::GetPokemonData(id);
//
//	_tcscpy_s(buffer, desc->name.length() + 1, CA2T(desc->name.c_str()));
//	g.DrawString(buffer, -1, FONT_MEDIUM, enemyPokemonNameRect, RIGHT_ALIGN, BLACK);
//
//	_stprintf_s(buffer, _T("%d"), enemyPokemon->level);
//	g.DrawString(buffer, -1, FONT_MEDIUM, enemyPokemonLevelRect, LEFT_ALIGN, BLACK);
//}

void BattleScreen::DrawPlayer(Graphics & g)
{
	g.DrawImage(battleUI, playerRect, 9 * PIXEL, 4 * PIXEL, 3 * PIXEL, 3 * PIXEL, UnitPixel);
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
		case InitToEncounter:
		{
			player->MoveTo();
			enemy->MoveTo();

			if (!player->IsPlaying())
			{
				dialogShow->Start();
				curState = Encounter;
			}
		}
		break;

		case Encounter:
		{
			if(dialogShow->IsPlaying())
				dialogShow->Update();
			else if (!dialogShow->IsPlaying() && dialogShow->RemainCount() > 0)
			{
				if (GET_KEY_Z || GET_KEY_X)
					dialogShow->Start();
			}
			else if (!dialogShow->IsPlaying() && dialogShow->RemainCount() == 0)
			{
				if (GET_KEY_Z || GET_KEY_X)
				{
					player->MoveToInit(PointF(R(-3 * MUL), R(3 * MUL)), 0.5f);
					player->Start();

					dialogShow->Reset();
					dialogShow->Push(TransString(NULL, "pokemon_dispatch", 1, TokenChange("pokemon_name", DM::GetPokemonDesc(playerPokemon->id)->name)));
					dialogShow->Start();

					curState = EncounterToDispatch;
				}
			}
		}
		break;

		case EncounterToDispatch:
		{
			if(player->IsPlaying())
				player->MoveTo();
			else
			{
				if (dialogShow->IsPlaying())
					dialogShow->Update();
				else if (!dialogShow->IsPlaying() && dialogShow->RemainCount() > 0)
				{
					if (GET_KEY_Z || GET_KEY_X)
						dialogShow->Start();
				}
				else if (!dialogShow->IsPlaying() && dialogShow->RemainCount() == 0)
				{
					anim->Start();

					player->SetImage(pokemonPic);
					player->SetPos(R(0.5f * MUL), R(3 * MUL));
					player->SetImagePos(DM::GetBehindPokemonImageRect(playerPokemon->id));

					curState = Dispatch;
				}
			}
		}
		break;

		case Dispatch:
		{
			anim->Update();

			if (GET_KEY_Z || GET_KEY_X || !anim->IsPlaying())
			{
				dialogShow->Reset();
				dialogShow->Push("                 ");
				dialogShow->Start();

				curState = DispatchToSelectMenu;
			}
		}
		break;

		case DispatchToSelectMenu:
		{
			dialogShow->Update();

			if (!dialogShow->IsPlaying())
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
				{
					dialogShow->Reset();
					dialogShow->Push(TransString(NULL, "run_success"));
					dialogShow->Start();

					curState = RunSuccess;
				}
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
			dialogShow->Update();

			if (!dialogShow->IsPlaying() && GET_KEY_Z)
			{
				Reset();
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
		case InitToEncounter:
		{
			DrawBackground(g);

			player->Draw(g);
			enemy->Draw(g);

			DrawMainDialog(g);
		}
		break;

		case Encounter:
		{
			DrawBackground(g);
			DrawMainDialog(g);

			player->Draw(g);
			enemy->Draw(g);

			DrawPlayerInfo(g);

			dialogShow->Draw(g);
		}
		break;

		case EncounterToDispatch:
		{
			DrawBackground(g);
			DrawMainDialog(g);

			player->Draw(g);
			enemy->Draw(g);

			dialogShow->Draw(g);

			DrawEnemyPokemonInfo(g);
		}
		break;

		case Dispatch:
		{
			DrawBackground(g);

			if (anim->IsPlaying())
				anim->Draw(g);
			else
				player->Draw(g);

			enemy->Draw(g);

			DrawMainDialog(g);
			DrawEnemyPokemonInfo(g);
			dialogShow->Draw(g);
		}
		break;

		case DispatchToSelectMenu:
		{
			DrawBackground(g);
			player->Draw(g);
			enemy->Draw(g);
			DrawEnemyPokemonInfo(g);

			DrawMainDialog(g);
		}
		break;

		case SelectMenu:
		{
			DrawBackground(g);
			DrawMainDialog(g);

			player->Draw(g);
			enemy->Draw(g);

			DrawBattleMenuDialog(g);

			DrawEnemyPokemonInfo(g);
			DrawPlayerPokemonInfo(g);

			DrawBattleMenu(g);
			DrawMenuCursor(g);
		}
		break;

		case FightMenu:
		{
			DrawBackground(g);

			player->Draw(g);
			enemy->Draw(g);

			DrawEnemyPokemonInfo(g);
			DrawPlayerPokemonInfo(g);

			DrawFightMenuDialog(g);
			DrawBattleMenuDialog(g);

			DrawFightMenu(g);
			DrawSkillCursor(g);

			DrawSkillInfo(g);
		}
		break;

		case RunSuccess:
		{
			DrawBackground(g);

			player->Draw(g);
			enemy->Draw(g);

			DrawEnemyPokemonInfo(g);
			DrawPlayerPokemonInfo(g);

			DrawMainDialog(g);

			dialogShow->Draw(g);
		}
		break;
	}
}

