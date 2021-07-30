#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "framework.h"

using namespace Gdiplus;

class Player
{
private:

	Point pos;
	PointF posF;

	Point nextTilePos;
	Point moveDir;

	float speed;
	bool isMoving;

public:

	Player();
	~Player();

	Point GetPos() const { return pos; }
	PointF GetPosF() const { return posF; }

	void SetPos(int x, int y) { pos = { x, y }; }
	void SetPosF(float x, float y) { posF = { x, y }; }

	void DrawPlayer(Graphics &g, PointF origin);
	void MovePlayer(Point dir);
};

#endif // !__PLAYER_H__
