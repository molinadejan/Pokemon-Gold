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

	// 0 : �̵� �Ұ���
	// 1 : �̵� ����
	int moveable;
	int interactID;

	// bool isPokeMon?

	Tile() : pos{ 0, 0 }, tilePos{ -1, -1 }, moveable(0), interactID(-1) { }
};

struct MovePoint
{
	string targetID;
	POINT pos;
	POINT targetPos;
	int moveType;
};

struct Map
{
	string ID;
	POINT worldPos;
	POINT mapSize;
	vector<vector<Tile>> tiles;
	vector<string> neighbors;
	vector<MovePoint> movePoints;

	// �ʿ��� �����ϴ� ���ϸ� ���̵�
	// vector<???> pokeData;

	// �ʿ��� �����ϴ� ���Ǿ� ���̵�
	// vector<???> npcData

	Map() : ID(""), worldPos{ 0, 0 }, mapSize{ -1, -1 } { }

	Map(string _ID, int x, int y) : ID(_ID), worldPos{ 0, 0 }, mapSize{ x, y }
	{
		tiles = vector<vector<Tile>>(y, vector<Tile>(x, Tile()));
		neighbors = vector<string>();
		movePoints = vector<MovePoint>();

		for (int i = 0; i < y; ++i)
			for (int j = 0; j < x; ++j)
				tiles[i][j].pos = { j, i };
	}
};

#endif // !__DATAS_H__

