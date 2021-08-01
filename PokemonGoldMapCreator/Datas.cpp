#include "Datas.h"

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

Tile* Map::GetTile(Point localPos)
{
	if(localPos.X < 0 || localPos.Y < 0 || localPos.X >= mapSize.X || localPos.Y >= mapSize.Y)
		return NULL;

	return &(tiles[localPos.Y][localPos.X]);
}
