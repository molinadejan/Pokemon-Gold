#include "PokemonCalculator.h"
#include <algorithm>

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

int CalDamage(int skillID, PokemonIndiv* attackPoke, PokemonIndiv* hitPoke, int vital, float tool, float NOT_USE2)
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

	int ret = int(power * attack * (attackPoke->level * 2 * 0.2f + 2));
	ret = int(ret / (float)def / 50.0f * vital * 2);

	float type1Revise = DM::GetTypeRevision(sData->type, hData->type1);
	float type2Revise = hData->type2 == -1 ? 1.0f : DM::GetTypeRevision(sData->type, hData->type2);

	ret = int(ret * stab * type1Revise * type2Revise);

	float random = (rand() % 39 + 217) * 100.0f / 255.0f / 255.0f;

	ret = (int)(ret * random);

	return ret;
}
