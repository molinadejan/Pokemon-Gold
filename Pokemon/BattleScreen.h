#pragma once

#ifndef __BATTLESCREEN_H__
#define __BATTLESCREEN_H__

#include "BaseClass.h"
#include "Datas.h"
#include "MovingObject.h"
#include "DialogShow.h"
#include "AnimationObject.h"
#include "ValueVariation.h"

#include <queue>

using std::queue;

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
		EncounterAnimation,
		Init,
		InitToEncounter,
		Encounter,
		EncounterToDispatch,
		Dispatch,
		DispatchToSelectMenu,
		SelectMenu,
		FightMenu,
		FightMenuToFightProcess,
		FightProcess,
		RunSuccess,
	};

	enum BattleMenuState
	{
		Fight, 
		Pokemon,
		Bag,
		Run,
	};

	enum BattleTurn
	{
		PlayerTurn,
		EnemyTurn
	};

private:

	RectF dialogRect = { R(0.5f * MUL), R(6.1f * MUL), R(9 * MUL), R(3 * MUL) };

	const Rect playerRect = { MUL, 3 * MUL, 3 * MUL, 3 * MUL };
	const Rect enemyRect = { 6 * MUL, 0, 3 * MUL, 3 * MUL };

	const Rect enemyPokemonInfoRect = { 0, 0, 6 * MUL, 2 * MUL };
	const Rect playerPokemonInfoRect = { 4 * MUL, 4 * MUL, 6 * MUL, 2 * MUL };

	const Rect playerInfoRect = { 4 * MUL, 5 * MUL, 6 * MUL, MUL };
	const Rect enemyInfoRect = { 0, MUL, 6 * MUL, MUL };

	// 0 : fight, 1 : pokemon, 2 : bag, 3 : run
	const RectF battleMenuRect[4] = { {R(4.8f * MUL), R(6.6f * MUL), R(3 * MUL), R(MUL)} ,
									  {R(7.3f * MUL), R(6.6f * MUL), R(3 * MUL), R(MUL)} ,
									  {R(4.8f * MUL), R(7.6f * MUL), R(3 * MUL), R(MUL)} ,
									  {R(7.3f * MUL), R(7.6f * MUL), R(3 * MUL), R(MUL)} };

	const Rect battleMenuCursorRect[4] = { {INT(4.5f * MUL), INT(6.75f * MUL), INT(MUL), INT(MUL)} ,
										   {INT(7.0f * MUL), INT(6.75f * MUL), INT(MUL), INT(MUL)} ,
									       {INT(4.5f * MUL), INT(7.75f * MUL), INT(MUL), INT(MUL)} ,
									       {INT(7.0f * MUL), INT(7.75f * MUL), INT(MUL), INT(MUL)} };

	const RectF playerPokemonNameRect  = { R(4.0f * MUL), R(3.95f * MUL), R(3 * MUL)   , R(MUL) };
	const RectF playerPokemonLevelRect = { R(7.5f * MUL), R(3.95f * MUL), R(1.5f * MUL), R(MUL) };
	const RectF playerPokemonCurHPRect = { R(5.5f * MUL), R(5.1f  * MUL), R(1.5f * MUL), R(0.6f * MUL) };
	const RectF playerPokemonMaxHPRect = { R(7.5f * MUL), R(5.1f  * MUL), R(1.5f * MUL), R(0.6f * MUL) };

	const RectF enemyPokemonNameRect = { 0, R(0.45f * MUL), R(3 * MUL), R(MUL) };
	const RectF enemyPokemonLevelRect = { R(3.5f * MUL), R(0.45f * MUL), R(1.5f * MUL), R(MUL) };

	const RectF skillRect[4] = { { R(0.8f * MUL), R(4.6f * MUL), R(3 * MUL), R(MUL) } ,
								 { R(0.8f * MUL), R(5.6f * MUL), R(3 * MUL), R(MUL) } ,
								 { R(0.8f * MUL), R(6.6f * MUL), R(3 * MUL), R(MUL) } ,
								 { R(0.8f * MUL), R(7.6f * MUL), R(3 * MUL), R(MUL) } };

	const Rect skillCursorRect[4] = { { INT(0.5f * MUL), INT(4.8f * MUL), INT(MUL), INT(MUL) } ,
									  { INT(0.5f * MUL), INT(5.8f * MUL), INT(MUL), INT(MUL) } ,
									  { INT(0.5f * MUL), INT(6.8f * MUL), INT(MUL), INT(MUL) } ,
									  { INT(0.5f * MUL), INT(7.8f * MUL), INT(MUL), INT(MUL) } };

	const RectF maxPPRect = { R(7.0f * MUL), R(6.5f * MUL), R(2.5f * MUL), R(MUL) };
	const RectF skillTypeRect = { R(4.5f * MUL), R(6.8f * MUL), R(5.0f * MUL), R(1.5f * MUL) };
	const RectF skillTypeNameRect = { R(7.0f * MUL), R(7.5f * MUL), R(3.0f * MUL), R(MUL) };

private:

	Image* battleUI;
	Image* pokemonPic;

	BattleType battleType;
	BattleState curState;

	PokemonIndiv* enemyPokemon;
	PokemonIndiv* playerPokemon;

	PokemonBattleData* playerBattleData;
	PokemonBattleData* enemyBattleData;

	int curMenuSelect;
	int curSkillSelect;

	MovingObject* player;
	MovingObject* enemy;
	AnimationObject* anim;
	DialogShow* dialogShow;

	ValueVariation* valueVariation;

	//int battleCount;
	int playerSelectSkillID;
	int enemySelectSkillID;

	AttackInfo playerAttackInfo;
	AttackInfo enemyAttackInfo;

	//BattleTurn battleTurn;
	queue<BattleTurn> battleQ;
	queue<bool(BattleScreen::*)()> updateQ;

private:

	bool Step1();
	bool Step2();
	bool Step3();
	bool Step3_5();
	bool Step4();
	bool Step5();
	bool Step5_5();
	bool Step6();
	bool Step7();
	bool Step8();
	bool Step9();
	bool Step9_5();
	bool Step10();
	bool Step10_5();
	bool Step10_7();
	bool Step11();
	bool Step12();
	bool Step13();
	bool Step14();
	//bool Step15();
	//bool Step16();


	bool DialogShowing();

	void DrawBackground(Graphics& g);
	void DrawMainDialog(Graphics& g);

	void DrawPlayer(Graphics& g);
	void DrawEnemy(Graphics& g);

	bool battleMenuDialogSwitch;
	void DrawBattleMenuDialog(Graphics& g);

	bool battleMenuSwitch;
	void DrawBattleMenu(Graphics& g);

	bool battleMenuCursorSwitch;
	void DrawMenuCursor(Graphics& g);

	bool battleMenuSkillCursorSwitch;
	void DrawSkillCursor(Graphics& g);

	bool fightMenuDialogSwitch;
	void DrawFightMenuDialog(Graphics& g);

	bool fightMenuSwitch;
	void DrawFightMenu(Graphics& g);

	bool skillInfoSwitch;
	void DrawSkillInfo(Graphics& g);

	bool enemyPokemonInfoSwitch;
	void DrawEnemyPokemonInfo(Graphics& g);

	bool playerPokemonInfoSwitch;
	void DrawPlayerPokemonInfo(Graphics& g);

	bool playerInfoSwitch;
	void DrawPlayerInfo(Graphics& g);

	bool enemyInfoSwtich;
	void DrawEnemyInfo(Graphics& g);

	bool animationSwitch;
	void DrawAnimation(Graphics& g);

	bool dialogShowSwitch;
	void DrawDialogShow(Graphics& g);

public:

	void InitWildBattle(int pokemonID, int level);
	void InitTrainerBattle(int trainerID);

public:

	BattleScreen();
	~BattleScreen() = default;

	void Reset() override;
	void ResourceInit() override;
	void Update() override;
	void Draw(Graphics& g) override;
};

#endif // !__BATTLESCREEN_H__
