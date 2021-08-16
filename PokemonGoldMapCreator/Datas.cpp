#include "Datas.h"

Tile::Tile() 
	: pos{ 0, 0 }, tilePos{ -1, -1 }, moveable(0), interactID(-1), isPokemon(0) { }

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