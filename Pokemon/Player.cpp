#include "Player.h"
#include "MyUtils.h"
#include "DataLoadManager.h"
#include <cmath>

Player::Player()
	: pos{ 0, 0 }, posF{ (REAL)pos.X, (REAL)pos.Y }, moveDir{ 0, 0 }, speed(3.0f), isMoving(false) { }

Player::~Player() { }

void Player::DrawPlayer(Graphics &g)
{
	Image *img = DataLoadManager::GetPlayer_game();
	Rect r((COL / 2) * PIXEL * SCREEN_MUL, (ROW / 2 - 0.25f) * PIXEL * SCREEN_MUL, PIXEL * SCREEN_MUL, PIXEL * SCREEN_MUL);

	int spriteTargetX = 0, curFrameCnt = 0;

	if (moveDir.X == 1)
	{
		spriteTargetX = 0;

		if (isMoving)
			curFrameCnt = frameCount % dir_right_frame_cnt;
		else
			curFrameCnt = 0;
	}
	else if (moveDir.X == -1)
	{
		spriteTargetX = 2;
		
		if (isMoving)
			curFrameCnt = frameCount % dir_left_frame_cnt;
		else
			curFrameCnt = 0;
	}
	else if (moveDir.Y == 1)
	{
		spriteTargetX = 4;

		if (isMoving)
		{
			curFrameCnt = frameCount % dir_up_frame_cnt;
			curFrameCnt = curFrameCnt % 2 == 0 ? 0 : curFrameCnt / 2 + 1;
		}
		else curFrameCnt = 0;
	}
	else if (moveDir.Y == -1)
	{
		spriteTargetX = 7;

		if (isMoving)
		{
			curFrameCnt = frameCount % dir_down_frame_cnt;
			curFrameCnt = curFrameCnt % 2 == 0 ? 0 : curFrameCnt / 2 + 1;
		}
		else curFrameCnt = 0;
	}

	g.DrawImage(img, r, (spriteTargetX + curFrameCnt)* PIXEL, 0, PIXEL, PIXEL, UnitPixel);
}

void Player::MovePlayer(Point dir, Map* m)
{
	if (dir.X != 0 && dir.Y != 0) dir.X = 0;

	if (isMoving)
	{
		posF.X += moveDir.X * speed * Timer::DeltaTime();
		posF.Y += moveDir.Y * speed * Timer::DeltaTime();

		float newDistance = fabs(posF.X - nextTilePos.X) + fabs(posF.Y - nextTilePos.Y);

		if (newDistance < 0.05f || newDistance > distance)
		{
			posF = { (REAL)nextTilePos.X , (REAL)nextTilePos.Y };
			pos = nextTilePos;

			isMoving = false;
		}

		distance = newDistance;
	}
	else
	//if(!isMoving)
	{
		if (dir.X == 0 && dir.Y == 0) 
			return;

		Point nextPos = pos + dir;
		moveDir = dir;

		Tile* tile = m->GetTile(nextPos);

		if (tile != NULL && tile->moveable != 0)
			return;

		nextTilePos = nextPos;

		isMoving = true;
		distance = 1.0f;
	}
}

void Player::FrameUpdate()
{
	if (isMoving)
	{
		frameChangeTime -= Timer::DeltaTime();

		if (frameChangeTime <= 0.0f)
		{
			frameChangeTime = FRAME_TIME;
			++frameCount;
			frameCount %= MAX_FRAME;
		}
	}
}
