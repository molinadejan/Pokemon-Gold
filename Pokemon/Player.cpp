#include "Player.h"
#include <cmath>

Player::Player()
	: tilePos{ 0, 0 }, worldPos{ tilePos.X, tilePos.Y }, moveDir{ 0, 0 }, speed(4.0f), isMoving(false) { }

Player::~Player() { }

void Player::DrawPlayer(Graphics &g, PointF origin)
{
	SolidBrush brush(Color(255, 0, 0));
	Rect r(origin.X, origin.Y, PIXEL * SCREEN_MUL, PIXEL * SCREEN_MUL);
	g.FillRectangle(&brush, r);
}

void Player::MovePlayer(Point dir)
{
	/*worldPos.X += dir.X * speed * Timer::DeltaTime();
	worldPos.Y += dir.Y * speed * Timer::DeltaTime();*/

	if (dir.X != 0 && dir.Y != 0) dir.X = 0;

	if (isMoving)
	{
		worldPos.X += moveDir.X * speed * Timer::DeltaTime();
		worldPos.Y += moveDir.Y * speed * Timer::DeltaTime();

		if (fabs(worldPos.X - nextTilePos.X) <= 0.025f && fabs(worldPos.Y - nextTilePos.Y) <= 0.025f)
		{
			worldPos.X = nextTilePos.X;
			worldPos.Y = nextTilePos.Y;

			tilePos.X = nextTilePos.X;
			tilePos.Y = nextTilePos.Y;

			isMoving = false;
		}
	}
	else
	{
		if (dir.X == 0 && dir.Y == 0) 
			return;

		moveDir = dir;

		nextTilePos.X = tilePos.X + dir.X;
		nextTilePos.Y = tilePos.Y + dir.Y;

		isMoving = true;
	}
}
