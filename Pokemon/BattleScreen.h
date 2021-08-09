#pragma once

#ifndef __BATTLESCREEN_H__
#define __BATTLESCREEN_H__

#include "BaseClass.h"
#include "Datas.h"

class BattleScreen : public BaseClass
{
public:

	enum BattleType
	{
		Wild,
		Trainer
	};

	enum BattleState
	{
		Encounter,
		Dispatch,
		SelectMenu,
		FightMenu,
		RunSuccess,
	};

	enum BattleMenuState
	{
		Fight, 
		Pokemon,
		Bag,
		Run,
	};

private:

	RectF dialogRect = { R(0.5f * MUL), R(6.1f * MUL), R(9 * MUL), R(3 * MUL) };

	const Rect myRect = { MUL, 3 * MUL, 3 * MUL, 3 * MUL };
	const Rect enemyRect = { 6 * MUL, 0, 3 * MUL, 3 * MUL };

	const Rect enemyPokemonInfoRect = { 0, 0, 6 * MUL, 2 * MUL };
	const Rect playerPokemonInfoRect = { 4 * MUL, 4 * MUL, 6 * MUL, 2 * MUL };

	const RectF enemyPokemonNameRect = { 0, R(0.45f * MUL), R(3 * MUL), R(MUL) };
	const RectF enemyPokemonLevelRect = { R(3.5f * MUL), R(0.45f * MUL), R(1.5f * MUL), R(MUL) };

	const Rect playerInfoRect = { 0, MUL, 6 * MUL, MUL };
	const Rect enemyInfoRect = { 4 * MUL, 5 * MUL, 6 * MUL, MUL };

	// 0 : fight, 1 : pokemon, 2 : bag, 3 : run
	const RectF battleMenuRect[4] = { {R(4.8f * MUL), R(6.6f * MUL), R(3 * MUL), R(MUL)} ,
									  {R(7.3f * MUL), R(6.6f * MUL), R(3 * MUL), R(MUL)} ,
									  {R(4.8f * MUL), R(7.6f * MUL), R(3 * MUL), R(MUL)} ,
									  {R(7.3f * MUL), R(7.6f * MUL), R(3 * MUL), R(MUL)} };

	const Rect battleMenuCursorRect[4] = { {INT(4.5f * MUL), INT(6.75f * MUL), INT(MUL), INT(MUL)} ,
										   {INT(7.0f * MUL), INT(6.75f * MUL), INT(MUL), INT(MUL)} ,
									       {INT(4.5f * MUL), INT(7.75f * MUL), INT(MUL), INT(MUL)} ,
									       {INT(7.0f * MUL), INT(7.75f * MUL), INT(MUL), INT(MUL)} };

	const RectF playerPokemonNameRect  = { R(4 * MUL), R(3.95f * MUL), R(3 * MUL), R(MUL) };
	const RectF playerPokemonLevelRect = { R(7.5f * MUL), R(3.95f * MUL), R(1.5f * MUL), R(MUL) };
	const RectF playerPokemonCurHPRect = { R(5.5f * MUL), R(5.1f * MUL), R(1.5f * MUL), R(0.6f * MUL) };
	const RectF playerPokemonMaxHPRect = { R(7.5f * MUL), R(5.1f * MUL), R(1.5f * MUL), R(0.6f * MUL) };

private:

	Image* battleUI;
	Image* pokemonPic;

	BattleType battleType;
	BattleState curState;

	PokemonIndiv* enemyPokemon;
	PokemonIndiv* playerPokemon;

	int curMenuSelect;
	int curSkillSelect;

private:

	void DeleteData();

	void DrawBackground(Graphics& g);
	void DrawMainDialog(Graphics& g);
	void DrawBattleMenuDialog(Graphics& g);
	void DrawMenuCursor(Graphics& g);

	void DrawFightMenuDialog(Graphics& g);

	void DrawEnemyPokemonInfo(Graphics& g);
	void DrawPlayerPokemonInfo(Graphics& g);

	void DrawPlayerInfo(Graphics& g);
	void DrawEnemyInfo(Graphics& g);

	void DrawPlayerPokemon(Graphics& g);
	void DrawEnemyPokemon(Graphics& g);

	void DrawPlayer(Graphics& g);
	void DrawNPC(Graphics& g);


public:

	void InitWildBattle(int pokemonID, int level);
	void InitTrainerBattle(int trainerID);

public:

	BattleScreen() { };
	~BattleScreen() = default;

	void ResourceInit() override;
	void Update() override;
	void Draw(Graphics& g) override;
};

#endif // !__BATTLESCREEN_H__
