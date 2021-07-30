#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "framework.h"

using namespace Gdiplus;

class Player
{
private:

	Point tilePos;
	Point nextTilePos;

	PointF worldPos;

	Point moveDir;

	float speed;
	bool isMoving;

public:

	Player();
	~Player();

	Point GetTilePos() const { return tilePos; }
	PointF GetWorldPos() const { return worldPos; }

	void DrawPlayer(Graphics &g, PointF origin);
	void MovePlayer(Point dir);
};

#endif // !__PLAYER_H__
