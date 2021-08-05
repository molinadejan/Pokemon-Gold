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

struct InventoryData
{
	int code;
	int type;
	int count;

	InventoryData() : code(-1), type(-1), count(0) { }
	InventoryData(int _code, int _type, int _count) : code(_code), type(_type), count(_count) { }
};

struct PlayerData
{
	int money;

	// 0 : tool, 1 : ball, 2 : important, 3 : machine
	vector<InventoryData> iData[4];
};

#endif // !__DATAS_H__

