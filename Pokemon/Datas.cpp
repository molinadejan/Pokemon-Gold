#include "Datas.h"
#include "PokemonCalculator.h"
#include "DataLoadManager.h"

Tile::Tile() 
	: pos{ 0, 0 }, tilePos{ -1, -1 }, moveable(0), interactID(-1) { }

Map::Map()
	: ID(""), worldPos{ 0, 0 }, mapSize{ -1, -1 } { }

Map::Map(string _ID, int x, int y) : ID(_ID), worldPos{ 0, 0 }, mapSize{ x, y }
{
	tiles = vector<vector<Tile>>(y, vector<Tile>(x, Tile()));
	neighbors = vector<string>();
	movePoints = vector<MovePoint>();

	for (int i = 0; i < y; ++i)
		for (int j = 0; j < x; ++j)
			tiles[i][j].pos = { j, i };
}

Tile* Map::GetTile(const Point& localPos)
{
	if(localPos.X < 0 || localPos.Y < 0 || localPos.X >= mapSize.X || localPos.Y >= mapSize.Y)
		return NULL;

	return &(tiles[localPos.Y][localPos.X]);
}

MovePoint* Map::GetMovePoint(const Point& localPos)
{
	for (int i = 0; i < (int)movePoints.size(); ++i)
		if (movePoints[i].pos.X == localPos.X && movePoints[i].pos.Y == localPos.Y)
			return &(movePoints[i]);

	return NULL;
}

Point MovePoint::GetDir()
{
	if (moveType % 4 == 0) return Point( 0, -1);

	if (moveType % 4 == 1) return Point(-1,  0);

	if (moveType % 4 == 2) return Point( 0,  1);

	if (moveType % 4 == 3) return Point( 1,  0);

	return Point(0, 0);
}

bool MovePoint::isDoor()
{
	return moveType >= 4;
}

bool MovePoint::isCarpet()
{
	return moveType < 4;
}

// 具积器南阁 俺眉 单捞磐 积己
PokemonIndiv::PokemonIndiv(int _id, int _level)
{
	id = _id;

	PokemonData* data = DM::GetPokemonData(_id);
	level = _level + rand() % 3 - 1;
	exp = 0;
	gender = rand() % 2;

	hp = CalHP(data->HP, level);

	ATK_stat = CalStat(data->ATK, level);
	DEF_stat = CalStat(data->DEF, level);
	SPA_stat = CalStat(data->SPA, level);
	SPD_stat = CalStat(data->SPD, level);
	SPE_stat = CalStat(data->SPE, level);

	statusEffect = 0;

	skills[0] = skills[1] = skills[2] = skills[3] = -1;
	pps[0] = pps[1] = pps[2] = pps[3] = 0;

	int skillCnt = 0;

	for (const auto& e : data->learn_skill)
	{
		if (e.first <= level)
			skills[skillCnt++] = e.second;

		if (skillCnt == 3)
			break;
	}

	for (int i = 0; i < 4; ++i)
	{
		if (skills[i] != -1)
		{
			SkillData* data = DM::GetSkillData(skills[i]);
			pps[i] = data->pp;
		}
	}
}

PokemonBattleData::PokemonBattleData()
	: ATK_rank(0), DEF_rank(0), SPA_rank(0), SPD_rank(0), SPE_rank(0), hit_rank(0), vital_rank(0)
{ }

void PokemonBattleData::Reset()
{
	ATK_rank = 0;
	DEF_rank = 0;
	SPA_rank = 0;
	SPD_rank = 0;
	SPE_rank = 0;
	hit_rank = 0;
	vital_rank = 0;
}
