#include "MyUtils.h"
#include "DataLoadManager.h"

bool operator==(const Point & p1, const Point & p2)
{
	return p1.X == p2.X && p1.Y == p2.Y;
}

PointF operator*(const Point& p1, const float& f)
{
	return PointF(p1.X * f, p1.Y * f);
}

Point operator*(const Point & p1, const int & i)
{
	return Point(p1.X * i, p1.Y * i);
}

bool IsIn(Point worldPos, Point origin, Point mapSize)
{
	if (worldPos.X < origin.X || worldPos.X >= origin.X + mapSize.X || worldPos.Y < origin.Y || worldPos.Y >= origin.Y + mapSize.Y)
		return false;

	return true;
}

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

void Clamp(float & num, float min, float max)
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