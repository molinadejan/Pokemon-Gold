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
	POINT pos;
	POINT tilePos;

	// 0 : 이동 불가능
	// 1 : 이동 가능
	int moveable;
	int interactID;

	Tile() : pos{ 0, 0 }, tilePos{ -1, -1 }, moveable(1), interactID(-1) { }
};

struct Map
{
	string ID;
	POINT worldPos;
	POINT mapSize;
	vector<vector<Tile>> tiles;

	// vector<int> pokeList;

	Map() : ID(""), worldPos{ 0, 0 }, mapSize{ -1, -1 } { }
};

#endif // !__DATAS_H__

