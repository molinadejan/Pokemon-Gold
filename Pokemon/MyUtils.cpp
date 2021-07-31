#include "MyUtils.h"

//bool IsIn(Point pos, int originX, int originY, int w, int h)
//{
//	if (pos.X < originX || pos.X >= originX + w || pos.Y < originY || pos.Y >= originY + h)
//		return false;
//
//	return true;
//}

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
