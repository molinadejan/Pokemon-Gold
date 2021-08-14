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

BattleScreen::BattleScreen()
{
	battleMenuDialogSwitch = false;
	battleMenuSwitch = false;
	battleMenuCursorSwitch = false;
	battleMenuSkillCursorSwitch = false;
	fightMenuDialogSwitch = false;
	fightMenuSwitch = false;
	skillInfoSwitch = false;
	enemyPokemonInfoSwitch = false;
	playerPokemonInfoSwitch = false;
	playerInfoSwitch = false;
	enemyInfoSwtich = false;
	animationSwitch = false;
	dialogShowSwitch = false;
}

void BattleScreen::InitWildBattle(int pokemonID, int level)
{
	battleType = Wild;

	enemyPokemon = new PokemonIndiv(pokemonID, level);
	playerPokemon = DM::GetPlayerData()->pokemonInBag[0];

	curMenuSelect = 0;
	curSkillSelect = 0;

	player = new MovingObject();
	enemy = new MovingObject();

	dialogShow = new DialogShow();
	anim = new AnimationObject();

	playerBattleData = new PokemonBattleData();
	enemyBattleData = new PokemonBattleData();
	tweeningObject = new TweeningObject();

	updateQ.push(&BattleScreen::Step1);
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

		delete playerBattleData;
		delete enemyBattleData;
		delete tweeningObject;
	}
	else if (battleType == Trainer)
	{

	}
}

// 각종 초기화
bool BattleScreen::Step1()
{
	player->SetImage(battleUI);
	player->SetPos(R(10 * MUL), R(3 * MUL));
	player->SetScreenSize(3 * MUL, 3 * MUL);
	player->SetImagePos(Rect(9 * PIXEL, 4 * PIXEL, 3 * PIXEL, 3 * PIXEL));
	player->MoveToInit(PointF(R(0.5f * MUL), R(3 * MUL)), 1.2f);
	player->Start();

	enemy->SetImage(pokemonPic);
	enemy->SetPos(R(-3 * MUL), R(0));
	enemy->SetScreenSize(3 * MUL, 3 * MUL);
	enemy->SetImagePos(DM::GetFrontPokemonImageRect(enemyPokemon->id));
	enemy->MoveToInit(PointF(R(6.5f * MUL), R(0)), 1.2f);
	enemy->Start();

	updateQ.push(&BattleScreen::Step2);

	return true;
}

bool BattleScreen::Step2()
{
	// 좌우에서 플레이어와 적이 이동
	if (player->IsPlaying())
	{
		player->MoveTo();
		enemy->MoveTo();

		return false;
	}

	updateQ.push(&BattleScreen::Step3);

	return true;
}

bool BattleScreen::Step3()
{
	dialogShow->Reset();
	dialogShow->Push(TransString(NULL, "wonder"));
	dialogShow->Push(TransString(NULL, "wild_encounter", 1, TokenChange("pokemon_name", DM::GetPokemonDesc(enemyPokemon->id)->name)));
	dialogShow->SetIsAuto(false);
	dialogShow->Start();

	dialogShowSwitch = true;

	player->MoveToInit(PointF(R(-3 * MUL), R(3 * MUL)), 0.5f);
	player->Start();

	updateQ.push(&BattleScreen::DialogShowing);
	updateQ.push(&BattleScreen::Step4);

	return true;
}

bool BattleScreen::Step4()
{
	if (player->IsPlaying())
	{
		player->MoveTo();
		return false;
	}

	enemyPokemonInfoSwitch = true;
	updateQ.push(&BattleScreen::Step5);

	return true;
}

bool BattleScreen::Step5()
{
	dialogShow->Reset();
	dialogShow->Push(TransString(NULL, "pokemon_dispatch", 1, TokenChange("pokemon_name", DM::GetPokemonDesc(playerPokemon->id)->name)));
	dialogShow->SetIsAuto(true);
	dialogShow->Start();

	anim->Reset();
	anim->SetImage(battleUI);
	anim->SetPos(0.5f * MUL, 3.5f * MUL);
	anim->SetScreenSize(3 * MUL, 3 * MUL);
	anim->SetImagePosVec(DM::GetAnimRect("pokemon_dispatch"));
	anim->Start();

	updateQ.push(&BattleScreen::DialogShowing);
	updateQ.push(&BattleScreen::Step6);

	dialogShowSwitch = true;

	return true;
}

bool BattleScreen::Step6()
{
	if (anim->IsPlaying())
	{
		animationSwitch = true;
		anim->Update();

		if (anim->GetRemainCount() == 1)
		{
			player->SetImage(pokemonPic);
			player->SetPos(R(0.5f * MUL), R(3 * MUL));
			player->SetImagePos(DM::GetBehindPokemonImageRect(playerPokemon->id));
		}

		return false;
	}

	animationSwitch = false;
	dialogShowSwitch = false;
	battleMenuDialogSwitch = true;
	battleMenuSwitch = true;
	battleMenuCursorSwitch = true;

	playerPokemonInfoSwitch = true;

	updateQ.push(&BattleScreen::Step7);
	return true;
}

bool BattleScreen::Step7()
{
	dialogShowSwitch = false;
	battleMenuSwitch = true;
	battleMenuCursorSwitch = true;
	battleMenuDialogSwitch = true;

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
		{
			updateQ.push(&BattleScreen::Step8);

			battleMenuSwitch = false;
			battleMenuCursorSwitch = false;

			fightMenuDialogSwitch = true;
			fightMenuSwitch = true;
			skillInfoSwitch = true;
			battleMenuSkillCursorSwitch = true;

			return true;
		}
		else if (curMenuSelect == 1)
			;
		else if (curMenuSelect == 2)
			;
		else if (curMenuSelect == 3)
		{
			//dialogShow->Reset();
			//dialogShow->Push(TransString(NULL, "run_success"));
			//dialogShow->Start();

			//curState = RunSuccess;
		}
	}

	return false;
}

bool BattleScreen::Step8()
{
	if (GET_KEY_UP && curSkillSelect > 0)
		--curSkillSelect;
	else if (GET_KEY_DOWN && curSkillSelect < 3 && playerPokemon->skills[curSkillSelect + 1] != -1)
		++curSkillSelect;

	if (GET_KEY_Z)
	{
		if (playerPokemon->pps[curSkillSelect] > 0)
		{
			int enemySelectSkillIdx;

			--playerPokemon->pps[curSkillSelect];

			// 이부분 수정 필요

			do
			{
				enemySelectSkillIdx = rand() % 4;
			} while (enemyPokemon->skills[enemySelectSkillIdx] == -1);

			playerSelectSkillID = playerPokemon->skills[curSkillSelect];
			enemySelectSkillID = enemyPokemon->skills[enemySelectSkillIdx];

			if (playerPokemon->SPE_stat > enemyPokemon->SPE_stat)
			{
				battleQ.push(PlayerTurn);
				battleQ.push(EnemyTurn);
			}
			else
			{
				battleQ.push(EnemyTurn);
				battleQ.push(PlayerTurn);
			}

			updateQ.push(&BattleScreen::Step9);
			return true;
		}
	}

	if (GET_KEY_X)
	{
		battleMenuSwitch = true;
		battleMenuCursorSwitch = true;

		fightMenuDialogSwitch = false;
		fightMenuSwitch = false;
		skillInfoSwitch = false;
		battleMenuSkillCursorSwitch = false;

		updateQ.push(&BattleScreen::Step7);

		return true;
	}

	return false;
}

bool BattleScreen::Step8_5()
{


	return true;
}

bool BattleScreen::Step9()
{
	dialogShow->Reset();
	dialogShow->Start();
	dialogShow->SetIsAuto(true);
	dialogShowSwitch = true;

	if (battleQ.empty())
	{
		updateQ.push(&BattleScreen::Step7);
		return true;
	}
	else if (battleQ.front() == PlayerTurn)
	{
		dialogShow->Push(TransString(NULL, "player_pokemon_attack", 2, TokenChange("pokemon_name", DM::GetPokemonDesc(playerPokemon->id)->name),
			TokenChange("skill_name", DM::GetSkillDesc(playerSelectSkillID)->name)));

		SkillData* sData = DM::GetSkillData(playerSelectSkillID);

		int x = playerBattleData->hit_rank - enemyBattleData->hit_rank;
		float hitRatio = sData->ar * CalHitRateRank(x);

		if (GetRandom(hitRatio))
		{
			updateQ.push(&BattleScreen::DialogShowing);
			updateQ.push(&BattleScreen::Step10);
		}
		else
		{
			dialogShow->Push(TransString(NULL, "pokemon_attack_miss", 1, TokenChange("pokemon_name", DM::GetPokemonDesc(playerPokemon->id)->name)));
			updateQ.push(&BattleScreen::DialogShowing);
			updateQ.push(&BattleScreen::Step9);
			battleQ.pop();
		}
	}
	else if (battleQ.front() == EnemyTurn)
	{
		dialogShow->Push(TransString(NULL, "enemy_pokemon_attack", 2, TokenChange("pokemon_name", DM::GetPokemonDesc(enemyPokemon->id)->name),
			TokenChange("skill_name", DM::GetSkillDesc(enemySelectSkillID)->name)));

		SkillData* sData = DM::GetSkillData(enemySelectSkillID);

		int x = enemyBattleData->hit_rank - playerBattleData->hit_rank;
		float hitRatio = sData->ar * CalHitRateRank(x);

		if (GetRandom(hitRatio))
		{
			updateQ.push(&BattleScreen::DialogShowing);
			updateQ.push(&BattleScreen::Step10);
		}
		else
		{
			dialogShow->Push(TransString(NULL, "enemy_pokemon_attack_miss", 1, TokenChange("pokemon_name", DM::GetPokemonDesc(enemyPokemon->id)->name)));
			updateQ.push(&BattleScreen::DialogShowing);
			updateQ.push(&BattleScreen::Step9);
			battleQ.pop();
		}
	}

	battleMenuDialogSwitch = false;
	fightMenuDialogSwitch = false;
	fightMenuSwitch = false;
	skillInfoSwitch = false;
	battleMenuSkillCursorSwitch = false;

	return true;
}

bool BattleScreen::Step10()
{
	/*if (battleQ.front() == PlayerTurn)
	{
		int vital = GetRandom(CalVitalRank(playerBattleData->vital_rank)) ? 2 : 1;
		int damage = CalDamage(playerSelectSkillID, playerPokemon, enemyPokemon, vital);
		int newHP = enemyPokemon->hp - damage;
		newHP = newHP < 0 ? 0 : newHP;

		tweeningObject->SetTarget(&(enemyPokemon->hp));
		tweeningObject->SetGoalValue(newHP);
		tweeningObject->Start();

		enemy->TwinkleStart();
	}
	else
	{
		int vital = GetRandom(CalVitalRank(enemyBattleData->vital_rank)) ? 2 : 1;
		int damage = CalDamage(enemySelectSkillID, enemyPokemon, playerPokemon, vital);
		int newHP = playerPokemon->hp - damage;
		newHP = newHP < 0 ? 0 : newHP;

		tweeningObject->SetTarget(&(playerPokemon->hp));
		tweeningObject->SetGoalValue(newHP);
		tweeningObject->Start();

		player->TwinkleStart();
	}*/

	updateQ.push(&BattleScreen::Step11);

	return true;
}

bool BattleScreen::Step11()
{
	if (!battleQ.empty() && battleQ.front() == PlayerTurn)
	{
		if (enemy->IsTwinkle())
		{
			enemy->Twinkle();
			return false;
		}
	}

	if (tweeningObject->IsPlaying())
	{
		tweeningObject->Update();
		return false;
	}

	if (battleQ.empty())
	{
		dialogShowSwitch = false;
		updateQ.push(&BattleScreen::Step7);
	}
	else if (battleQ.front() == PlayerTurn)
	{
		if (enemyPokemon->hp == 0)
			updateQ.push(&BattleScreen::Step12);
		else if (battleQ.size() > 1)
			updateQ.push(&BattleScreen::Step9);
		else
			updateQ.push(&BattleScreen::Step7);

		battleQ.pop();
	}
	else if (battleQ.front() == EnemyTurn)
	{
		if (playerPokemon->hp == 0)
			updateQ.push(&BattleScreen::Step13);
		else if (battleQ.size() > 1)
			updateQ.push(&BattleScreen::Step9);
		else
			updateQ.push(&BattleScreen::Step7);

		battleQ.pop();
	}

	return true;
}

bool BattleScreen::Step12()
{
	dialogShowSwitch = true;
	dialogShow->Reset();
	dialogShow->SetIsAuto(true);
	dialogShow->Push(TransString(NULL, "enemy_pokemon_fall_down", 1, TokenChange("pokemon_name", DM::GetPokemonDesc(enemyPokemon->id)->name)));

	int exp = CalExp(battleType == Wild ? 1.0f : 1.5f, playerPokemon->id, enemyPokemon->level);

	dialogShow->Push(TransString(NULL, "pokemon_get_exp", 2, TokenChange("pokemon_name", DM::GetPokemonDesc(enemyPokemon->id)->name), TokenChange("exp", std::to_string(exp))));

	updateQ.push(&BattleScreen::DialogShowing);
	updateQ.push(&BattleScreen::Step14);

	return true;
}

bool BattleScreen::Step13()
{
	dialogShow->Reset();
	dialogShow->Push(TransString(NULL, "pokemon_fall_down", 1, TokenChange("pokemon_name", DM::GetPokemonDesc(playerPokemon->id)->name)));

	return true;
}

bool BattleScreen::Step14()
{



	return true;
}

bool BattleScreen::DialogShowing()
{
	if (dialogShow->IsPlaying())
	{
		dialogShow->Update();
		return false;
	}
	else if(!dialogShow->IsPlaying() && dialogShow->RemainCount() > 0)
	{
		if (GET_KEY_Z || GET_KEY_X)
			dialogShow->Start();

		return false;
	}
	else if (!dialogShow->IsPlaying() && dialogShow->RemainCount() == 0)
	{
		if (dialogShow->IsAuto() || GET_KEY_Z || GET_KEY_X)
			return true;

		return false;
	}

	return false;
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
	if (!battleMenuDialogSwitch)
		return;

	UIManager::DrawDialogUI_IDX(g, 4, 6, COL - 4, 3);
}

void BattleScreen::DrawBattleMenu(Graphics & g)
{
	if (!battleMenuSwitch)
		return;

	for (int i = 0; i < 4; ++i)
	{
		TransString(buffer, "battle_menu_" + std::to_string(i));
		g.DrawString(buffer, -1, FONT_BIG, battleMenuRect[i], LEFT_ALIGN, BLACK);
	}
}

void BattleScreen::DrawMenuCursor(Graphics &g)
{
	if (!battleMenuCursorSwitch)
		return;

	g.DrawImage(battleUI, battleMenuCursorRect[curMenuSelect], 6 * PIXEL, 3 * PIXEL, PIXEL, PIXEL, UnitPixel);
}

void BattleScreen::DrawSkillCursor(Graphics &g)
{
	if (!battleMenuSkillCursorSwitch)
		return;

	g.DrawImage(battleUI, skillCursorRect[curSkillSelect], 6 * PIXEL, 3 * PIXEL, PIXEL, PIXEL, UnitPixel);
}

void BattleScreen::DrawFightMenuDialog(Graphics &g)
{
	if (!fightMenuDialogSwitch)
		return;

	UIManager::DrawDialogUI_IDX(g, 0.0f, 4.0f, 4.5f, 5.0f);
}

void BattleScreen::DrawFightMenu(Graphics &g)
{
	if (!fightMenuSwitch)
		return;

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

void BattleScreen::DrawSkillInfo(Graphics &g)
{
	if (!skillInfoSwitch)
		return;

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

void BattleScreen::DrawEnemyPokemonInfo(Graphics &g)
{
	if (!enemyPokemonInfoSwitch)
		return;

	g.DrawImage(battleUI, enemyPokemonInfoRect, 6 * PIXEL, 0, 6 * PIXEL, 2 * PIXEL, UnitPixel);

	int id = enemyPokemon->id;

	PokemonDesc* desc = DM::GetPokemonDesc(id);
	PokemonData* data = DM::GetPokemonData(id);

	_tcscpy_s(buffer, desc->name.length() + 1, CA2T(desc->name.c_str()));
	g.DrawString(buffer, -1, FONT_MEDIUM, enemyPokemonNameRect, RIGHT_ALIGN, BLACK);

	_stprintf_s(buffer, _T("%d"), enemyPokemon->level);
	g.DrawString(buffer, -1, FONT_MEDIUM, enemyPokemonLevelRect, LEFT_ALIGN, BLACK);

	int maxHP = enemyPokemon->maxHP;
	int curHP = enemyPokemon->hp;

	float ratio = curHP / (float)maxHP;

	Rect hpRect = { 2 * MUL, 1 * MUL, INT(3 * MUL * ratio), MUL };

	g.DrawImage(battleUI, hpRect, 10 * PIXEL, 3 * PIXEL, PIXEL, PIXEL, UnitPixel);
}

void BattleScreen::DrawPlayerPokemonInfo(Graphics &g)
{
	if (!playerPokemonInfoSwitch)
		return;

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

	int maxHP = playerPokemon->maxHP;
	int curHP = playerPokemon->hp;

	float ratio = curHP / (float)maxHP;

	Rect hpRect = {6 * MUL, 4 * MUL, INT(3 * MUL * ratio), MUL};

	g.DrawImage(battleUI, hpRect, 8 * PIXEL, 3 * PIXEL, PIXEL, PIXEL, UnitPixel);
}

void BattleScreen::DrawPlayerInfo(Graphics &g)
{
	if (!playerInfoSwitch)
		return;

	g.DrawImage(battleUI, playerInfoRect, 0, 2 * PIXEL, 6 * PIXEL, PIXEL, UnitPixel);
}

void BattleScreen::DrawEnemyInfo(Graphics &g)
{
	if (!enemyInfoSwtich)
		return;

	g.DrawImage(battleUI, enemyInfoRect, 6 * PIXEL, 2 * PIXEL, 6 * PIXEL, PIXEL, UnitPixel);
}

void BattleScreen::DrawPlayer(Graphics &g)
{
	player->Draw(g);
}

void BattleScreen::DrawEnemy(Graphics &g)
{
	enemy->Draw(g);
}

void BattleScreen::DrawAnimation(Graphics &g)
{
	if (!animationSwitch)
		return;

	anim->Draw(g);
}

void BattleScreen::DrawDialogShow(Graphics &g)
{
	if (!dialogShowSwitch)
		return;

	dialogShow->Draw(g);
}

void BattleScreen::ResourceInit()
{
	battleUI = DM::GetBattleUI();
	pokemonPic = DM::GetPokemonPicture();
}

void BattleScreen::Update()
{
	if (!updateQ.empty())
	{
		bool check = (this->*updateQ.front())();
		if (check) updateQ.pop();
	}
}

void BattleScreen::Draw(Graphics & g)
{
	DrawBackground(g);
	DrawMainDialog(g);
	DrawDialogShow(g);

	DrawPlayer(g);
	DrawEnemy(g);
	DrawAnimation(g);

	DrawPlayerPokemonInfo(g);
	DrawEnemyPokemonInfo(g);

	DrawFightMenuDialog(g);

	DrawBattleMenuDialog(g);
	DrawBattleMenu(g);
	DrawMenuCursor(g);

	DrawFightMenu(g);
	DrawSkillCursor(g);

	DrawSkillInfo(g);
}

