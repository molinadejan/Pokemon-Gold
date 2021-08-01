#include "Player.h"
#include "MyUtils.h"
#include <cmath>

Player::Player()
	: pos{ 0, 0 }, posF{ (REAL)pos.X, (REAL)pos.Y }, moveDir{ 0, 0 }, speed(3.0f), isMoving(false) { }

Player::~Player() { }

void Player::DrawPlayer(Graphics &g)
{
	SolidBrush brush(Color(255, 0, 0));
	Rect r((COL / 2) * PIXEL * SCREEN_MUL, (ROW / 2) * PIXEL * SCREEN_MUL, PIXEL * SCREEN_MUL, PIXEL * SCREEN_MUL);
	g.FillRectangle(&brush, r);
}

void Player::MovePlayer(Point dir, Map* m)
{
	if (dir.X != 0 && dir.Y != 0) dir.X = 0;

	if (isMoving)
	{
		posF.X += moveDir.X * speed * Timer::DeltaTime();
		posF.Y += moveDir.Y * speed * Timer::DeltaTime();

		if (fabs(posF.X - nextTilePos.X) <= 0.05f && fabs(posF.Y - nextTilePos.Y) <= 0.05f)
		{
			posF = { (REAL)nextTilePos.X , (REAL)nextTilePos.Y };
			pos = nextTilePos;

			isMoving = false;
		}
	}
	else
	{
		if (dir.X == 0 && dir.Y == 0) 
			return;

		Point nextPos = pos + dir;

		// Map에 Gettile메서드 하나 만들자
		if (IsIn(nextPos, m->mapSize) && m->tiles[nextPos.Y][nextPos.X].moveable == 0)
		{
			moveDir = dir;
			nextTilePos = pos + dir;
			isMoving = true;
		}
	}
}
