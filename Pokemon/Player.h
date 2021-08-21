#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "framework.h"
#include "Datas.h"

using namespace Gdiplus;

class Player
{
private:
	enum DIR
	{
		LEFT,
		RIGHT,
		UP,
		DOWN
	};

private:

	// 0 : left, 1 : right, 2 : up, 3 : down
	vector<Rect>* walkAnim[4];
	const float FRAME_TIME = 0.15f;

private:

	DIR curDir;

	Image* playerImg;

	Point  pos;
	PointF posF;

	Point nextTilePos;
	Point moveDir;
	Point inputDir;

	float speed;
	bool  isMoving;

	float distance;
	int   frameCount;
	float frameChangeTime;

public:

	Player();
	~Player();

	Point GetPos() const { return pos; }
	PointF GetPosF() const { return posF; }

	void SetPos(int x, int y) { pos = { x, y }; posF = { (REAL)x, (REAL)y }; }
	void SetPos(Point _pos) { pos = _pos; posF = { (REAL)_pos.X, (REAL)_pos.Y }; }

	bool GetIsMoving() const { return isMoving; }

	bool isOnDoor(Map* &m, MovePoint* &mp);
	bool isOnCarpet(Map* &m, MovePoint* &mp);
	bool IsOnNMap(Map *& m, Map *&nMap);

	void MovingPlayer();

	void DrawPlayer(Graphics &g);
	void MovePlayer(Map*& m, Point dir);

	void FrameUpdate();
};

#endif // !__PLAYER_H__
