#pragma once

#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "framework.h"
#include "Datas.h"

using namespace Gdiplus;

class Player
{
private:

	const int   DIR_RIGHT_IDX            = 0;
	const int   DIR_LEFT_IDX             = 2;
	const int   DIR_DOWN_IDX             = 4;
	const int   DIR_UP_IDX               = 7;

	const int   DIR_HORIZONTAL_FRAME_CNT = 2;
	const int   DIR_VERTICAL_FRAME_CNT   = 4;

	const int   MAX_FRAME                = 4;
	const float FRAME_TIME               = 0.16f;

private:

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
	//void SetPosF(float x, float y) { posF = { x, y }; }

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
