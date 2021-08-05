#include "MyUtils.h"
#include "DataLoadManager.h"

//bool IsIn(Point pos, int originX, int originY, int w, int h)
//{
//	if (pos.X < originX || pos.X >= originX + w || pos.Y < originY || pos.Y >= originY + h)
//		return false;
//
//	return true;
//}

bool operator==(const Point & p1, const Point & p2)
{
	return p1.X == p2.X && p1.Y == p2.Y;
}

PointF operator*(const Point& p1, const float& f)
{
	return PointF(p1.X * f, p1.Y * f);
}

bool IsIn(Point worldPos, Point origin, Point mapSize)
{
	if (worldPos.X < origin.X || worldPos.X >= origin.X + mapSize.X || worldPos.Y < origin.Y || worldPos.Y >= origin.Y + mapSize.Y)
		return false;

	return true;
}

//bool IsIn(Point pos, int mapSizeX, int mapSizeY)
//{
//	if(pos.X < 0 || pos.X >= mapSizeX || pos.Y < 0 || pos.Y >= mapSizeY)
//		return false;
//
//	return true;
//}

bool IsIn(Point localPos, Point mapSize)
{
	if (localPos.X < 0 || localPos.X >= mapSize.X || localPos.Y < 0 || localPos.Y >= mapSize.Y)
		return false;

	return true;
}

void Clamp(int & num, int min, int max)
{
	if (min > max)
	{
		Clamp(num, max, min);
		return;
	}

	if (num < min)
		num = min;

	if (num > max)
		num = max;
}

Tile* GetTile(Map* m, Point pos)
{
	if (IsIn(pos, m->mapSize))
		return &(m->tiles[pos.Y][pos.X]);

	Point worldPos = pos + m->worldPos;

	for (const string& n : m->neighbors)
	{
		Map* nMap = DataLoadManager::GetMapData(n);
		Point nLocal = worldPos - nMap->worldPos;

		if (IsIn(nLocal, nMap->mapSize))
			return &(nMap->tiles[nLocal.Y][nLocal.X]);
	}

	return NULL;
}

Map* GetNMap(Map* m, Point pos)
{
	Point worldPos = pos + m->worldPos;

	for (const string& nID : m->neighbors)
	{
		Map* n = DataLoadManager::GetMapData(nID);

		if (IsIn(worldPos, n->worldPos, n->mapSize))
			return n;
	}

	return NULL;
}


