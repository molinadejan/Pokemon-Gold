#include "PokemonCalculator.h"

int CalHP(int HP, int level, int NOT_USE)
{
	float ret = (HP * 2 + 15) * 0.5f + 10 + level;
	return (int)ret;
}

int CalStat(int stat, int level, int NOT_USE)
{
	float ret = (stat * 2 + 15) * 0.5f + 5;
	return (int)ret;
}
