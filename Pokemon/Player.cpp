#include "Player.h"
#include <cmath>

Player::Player()
	: pos{ 0, 0 }, posF{ pos.X, pos.Y }, moveDir{ 0, 0 }, speed(3.0f), isMoving(false) { }

Player::~Player() { }

void Player::DrawPlayer(Graphics &g, PointF origin)
{
	SolidBrush brush(Color(255, 0, 0));
	Rect r(origin.X, origin.Y, PIXEL * SCREEN_MUL, PIXEL * SCREEN_MUL);
	g.FillRectangle(&brush, r);
}

void Player::MovePlayer(Point dir)
{
	if (dir.X != 0 && dir.Y != 0) dir.X = 0;

	if (isMoving)
	{
		posF.X += moveDir.X * speed * Timer::DeltaTime();
		posF.Y += moveDir.Y * speed * Timer::DeltaTime();

		if (fabs(posF.X - nextTilePos.X) <= 0.05f && fabs(posF.Y - nextTilePos.Y) <= 0.05f)
		{
			posF.X = nextTilePos.X;
			posF.Y = nextTilePos.Y;

			pos.X = (int)nextTilePos.X;
			pos.Y = (int)nextTilePos.Y;

			isMoving = false;
		}
	}
	else
	{
		if (dir.X == 0 && dir.Y == 0) 
			return;

		moveDir = dir;

		nextTilePos.X = pos.X + dir.X;
		nextTilePos.Y = pos.Y + dir.Y;

		isMoving = true;
	}
}
