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
		TOP,
		DOWN
	};

private:

	const int dir_right_idx = 0;
	const int dir_left_idx = 2;
	const int dir_down_idx = 4;
	const int dir_up_idx = 7;

	const int dir_right_frame_cnt = 2;
	const int dir_left_frame_cnt = 2;
	const int dir_down_frame_cnt = 4;
	const int dir_up_frame_cnt = 4;

	const int MAX_FRAME = 4;
	const float FRAME_TIME = 0.16f;

private:

	Point pos;
	PointF posF;

	Point nextTilePos;
	Point moveDir;

	float speed;
	bool isMoving;

	float distance;
	int frameCount;
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

	void DrawPlayer(Graphics &g);
	void MovePlayer(Point dir, Map* m);

	void FrameUpdate();
};

#endif // !__PLAYER_H__
