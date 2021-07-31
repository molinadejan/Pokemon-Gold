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

	void SetPos(int x, int y) { pos = { x, y }; posF = { (REAL)x, (REAL)y }; }
	void SetPos(Point _pos) { pos = _pos; posF = { (REAL)_pos.X, (REAL)_pos.Y }; }
	//void SetPosF(float x, float y) { posF = { x, y }; }

	bool GetIsMoving() const { return isMoving; }

	void DrawPlayer(Graphics &g, PointF origin);
	void MovePlayer(Point dir);
};

#endif // !__PLAYER_H__
