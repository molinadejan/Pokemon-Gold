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

	// 0 : �̵� �Ұ���
	// 1 : �̵� ����
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
};

struct Map
{
	string ID;
	Point worldPos;
	Point mapSize;
	vector<vector<Tile>> tiles;
	vector<string> neighbors;
	vector<MovePoint> movePoints;

	// �ʿ��� �����ϴ� ���ϸ� ���̵�
	// vector<???> pokeData;

	// �ʿ��� �����ϴ� ���Ǿ� ���̵�
	// vector<???> npcData

	Map();
	Map(string _ID, int x, int y);
	Tile* GetTile(Point localPos);
};

#endif // !__DATAS_H__

