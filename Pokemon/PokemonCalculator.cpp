#include "PokemonCalculator.h"
#include <algorithm>
#include <cmath>

int CalHP(int HP, int level, int NOT_USE)
{
	float ret = (HP * 2 + 15 + 100) * level / 100.0f + 10;
	return (int)ret;
}

int CalStat(int stat, int level, int NOT_USE)
{
	float ret = (stat * 2 + 15) * level / 100.0f + 5;
	return (int)ret;
}

float CalStatRank(int x)
{
	return (2 + max(0, x)) / (float)(2 + min(0, x));
}

float CalHitRateRank(int x)
{
	return (3 + max(0, x)) / (float)(3 + min(0, x));
}

float CalVitalRank(int x)
{
	float ret = 0.5f;

	if (x == 0)
		ret = 1 / 16;
	else if (x == 1)
		ret = 1 / 8;
	else if (x == 2)
		ret = 1 / 4;
	else if (x == 3)
		ret = 1 / 3;
	
	return ret * 100;
}

bool GetRandom(float x)
{
	int random = rand() % 10000;
	float randomF = random / 100.0f;

	return randomF <= x;
}

int CalPower(int skillPower, float tool)
{
	return int(skillPower * tool);
}

int CalATK(int ATKStat, int rank, float tool)
{
	return int(ATKStat * CalStatRank(rank) * tool);
}

int CalDEF(int DEFStat, int rank, float suicideBomb, float tool)
{
	return int(DEFStat * CalStatRank(rank) * suicideBomb * tool);
}

AttackInfo CalDamage(int skillID, PokemonIndiv* attackPoke, PokemonIndiv* hitPoke, int vital, float tool, float NOT_USE2)
{
	SkillData* sData = DM::GetSkillData(skillID);

	PokemonData* aData = DM::GetPokemonData(attackPoke->id);
	PokemonData* hData = DM::GetPokemonData(hitPoke->id);

	int power = 0, attack = 0, def = 0;

	if (sData->cc == 0)
	{
		power = CalPower(sData->power, tool);
		attack = CalATK(attackPoke->ATK_stat);
		def = CalDEF(hitPoke->DEF_stat);
	}
	else if (sData->cc == 1)
	{
		power = CalPower(sData->power, tool);
		attack = CalATK(attackPoke->SPA_stat);
		def = CalDEF(hitPoke->SPD_stat);
	}
	else if (sData->cc == 2)
	{

	}

	float stab = 1.0f;

	if (sData->type == aData->type1 || sData->type == aData->type2)
		stab = 1.5f;

	int damage = int(power * attack * (attackPoke->level * 2 * 0.2f + 2));
	damage = int(damage / (float)def / 50.0f * vital * 2);

	float type1Revise = DM::GetTypeRevision(sData->type, hData->type1);
	float type2Revise = hData->type2 == -1 ? 1.0f : DM::GetTypeRevision(sData->type, hData->type2);

	damage = int(damage * stab * type1Revise * type2Revise);

	float random = (rand() % 16 + 85) / 255.0f;

	damage = (int)(damage * random);

	if (damage == 0)
		damage = 1.0f;

	AttackInfo ret;

	ret.damage = damage;
	
	if (type1Revise * type2Revise == 0)
		ret.effect = 0;
	else if (type1Revise * type2Revise > 1.5f)
		ret.effect = 2;
	else
		ret.effect = 1;

	if (vital == 2)
		ret.vital = true;
	else
		ret.vital = false;

	return ret;
}

int CalExp(float battleType, int id, int enemyLevel, int s)
{

	float ret = battleType * DM::GetPokemonData(id)->base_exp * enemyLevel;
	ret /= (7 * s);

	return (int)ret;
}

int CalGrowthType0(int level)
{
	float ret = 0.8f * std::pow(level, 3);
	return (int)ret;
}

int CalGrowthType1(int level)
{
	return (int)std::pow(level, 3);
}

int CalGrowthType2(int level)
{
	float ret = 8.3f * std::pow(level, 3) - 15.0f * std::pow(level, 2) + 100 * level - 140;

	if (ret < 0) ret = 10;

	return (int)ret;
}

int CalGrowthType3(int level)
{
	float ret = 1.25f * std::pow(level, 3);
	return (int)ret;
}

int CalNextExp(int id, int nextLevel)
{
	int type = DM::GetPokemonData(id)->exp_growth_group;

	if (type == 0)
		return CalGrowthType0(nextLevel);
	else if (type == 1)
		return CalGrowthType1(nextLevel);
	else if (type == 2)
		return CalGrowthType2(nextLevel);
	else if (type == 3)
		return CalGrowthType3(nextLevel);

	return 1;
}
