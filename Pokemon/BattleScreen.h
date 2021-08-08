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

private:

	Image* battleUI;
	Image* pokemonPic;

	BattleType battleType;

	PokemonIndiv* indiv;
	//PokemonBattleData* battleData;

private:

	void DeleteData();

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
