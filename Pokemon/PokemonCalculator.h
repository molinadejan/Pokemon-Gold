#pragma once

#ifndef __POKEMONCALCULATOR_H__
#define __POKEMONCALCULATOR_H__

#include "Datas.h"
#include "DataLoadManager.h"

int CalHP(int HP, int level, int NOT_USE = 0);
int CalStat(int stat, int level, int NOT_USE = 0);

float CalStatRank(int x);
float CalHitRateRank(int x);
float CalVitalRank(int x);

bool GetRandom(float x);

int CalPower(int skillPower, float tool = 1.0f);
int CalATK(int ATKStat, int rank = 0, float tool = 1.0f);
int CalDEF(int DEFStat, int rank = 0, float suicideBomb = 1.0f, float tool = 1.0f);

int CalDamage(int skillID, PokemonIndiv* attackPoke, PokemonIndiv* hitPoke, int vital, float tool = 1.0f, float NOT_USE2 = 0.0f);

#endif // !__POKEMONCALCULATOR_H__
