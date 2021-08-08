#pragma once

#ifndef __DATAS_H__
#define __DATAS_H__

#include <string>
#include <vector>

#include "framework.h"

using std::string;
using std::vector;

using namespace Gdiplus;

struct Tile
{
	Point pos;
	Point tilePos;

	// 0 : 이동 불가능
	// 1 : 이동 가능
	int moveable;
	int interactID;

	// bool isPokeMon?

	Tile();
};

struct MovePoint
{
	string targetID;
	Point pos;
	Point targetPos;
	int moveType;

	Point GetDir();

	bool isDoor();
	bool isCarpet();
};

struct Map
{
	string ID;
	Point worldPos;
	Point mapSize;
	vector<vector<Tile>> tiles;
	vector<string> neighbors;
	vector<MovePoint> movePoints;

	// 맵에서 등장하는 포켓몬 아이디
	// vector<???> pokeData;

	// 맵에서 등장하는 엔피씨 아이디
	// vector<???> npcData

	Map();
	Map(string _ID, int x, int y);

	Tile* GetTile(const Point &localPos);
	MovePoint* GetMovePoint(const Point &localPos);
};

struct ItemDesc
{
	int code;
	string name;
	string desc;
	int type;
};

struct InventoryItemData
{
	int code;
	int type;
	int count;

	InventoryItemData() : code(-1), type(-1), count(0) { }
	InventoryItemData(int _code, int _type, int _count) : code(_code), type(_type), count(_count) { }
};

struct PlayerData
{
	int money;

	// 0 : tool, 1 : ball, 2 : important, 3 : machine
	vector<InventoryItemData> iData[4];
};

struct PokemonData
{
	int id;
	int type1;
	int type2;

	int evo_id;
	int height;
	int weight;
	int catch_rate;
	int base_exp;
	int exp_growth_group;

	int HP;
	int ATK;
	int DEF;
	int SPA;
	int SPD;
	int SPE;
};

struct PokemonDesc
{
	int id;
	string name;
	string cc;
};

struct PokemonIndiv
{
	int id;
	int level;
	int exp;
	int hp;

	int ATK_stat;
	int DEF_stat;
	int SPA_stat;
	int SPD_stat;
	int SPE_stat;

	int statusEffect;

	PokemonIndiv(int _id, int _level);
};

struct PokemonBattleData
{
	int id;
	int statusEffect;

	PokemonBattleData(int _id)
		: id(_id), statusEffect(-1) { }
};

#endif // !__DATAS_H__

