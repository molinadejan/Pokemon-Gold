#include "Player.h"
#include "MyUtils.h"
#include "DataLoadManager.h"
#include "InputManager.h"
#include <cmath>

Player::Player()
	: pos{ 0, 0 }, posF{ (REAL)pos.X, (REAL)pos.Y }, moveDir{ 0, 0 }, inputDir(0, 0), speed(3.0f), isMoving(false) { }

Player::~Player() { }

bool Player::isOnDoor(Map* &m, MovePoint* &mp)
{
	mp = NULL;
	mp = m->GetMovePoint(pos);

	if (mp != NULL && mp->isDoor())
		return true;

	return false;
}

bool Player::isOnCarpet(Map *& m, MovePoint *& mp)
{
	mp = NULL;
	mp = m->GetMovePoint(pos);

	if (mp != NULL && mp->isCarpet())
		return true;

	return false;
}

bool Player::IsOnNMap(Map *& m, Map *&nMap)
{
	nMap = NULL;
	nMap = GetNMap(m, pos);
	return nMap != NULL;
}

void Player::MovingPlayer()
{
	posF = posF + moveDir * (speed * Timer::DeltaTime());

	float newDistance = fabs(posF.X - nextTilePos.X) + fabs(posF.Y - nextTilePos.Y);

	if (newDistance < 0.05f || newDistance > distance)
	{
		posF = { (REAL)nextTilePos.X , (REAL)nextTilePos.Y };
		pos = nextTilePos;

		isMoving = false;
	}

	distance = newDistance;
}

void Player::DrawPlayer(Graphics &g)
{
	Image *img = DataLoadManager::GetPlayer_game();
	Rect r((COL / 2 - 1) * PIXEL * SCREEN_MUL, (ROW / 2 - 0.25f) * PIXEL * SCREEN_MUL, PIXEL * SCREEN_MUL, PIXEL * SCREEN_MUL);

	int spriteTargetX = 0, curFrameCnt = 0;

	if (inputDir.X != 0 && inputDir.Y == 0)
	{
		spriteTargetX = inputDir.X == 1 ? 0 : 2;
		curFrameCnt = isMoving ? frameCount % DIR_HORIZONTAL_FRAME_CNT : 0;
	}
	else if (inputDir.X == 0 && inputDir.Y != 0)
	{
		spriteTargetX = inputDir.Y == 1 ? 4 : 7;

		if (isMoving)
		{
			curFrameCnt = frameCount % DIR_VERTICAL_FRAME_CNT;
			curFrameCnt = curFrameCnt % 2 == 0 ? 0 : curFrameCnt / 2 + 1;
		}
		else curFrameCnt = 0;
	}

	g.DrawImage(img, r, (spriteTargetX + curFrameCnt) * PIXEL, 0, PIXEL, PIXEL, UnitPixel);
}

void Player::MovePlayer(Map*& m, Point dir)
{
	inputDir = dir;

	if (inputDir == Point(0, 0))
		return;

	Point nextPos = pos + inputDir;
	moveDir = inputDir;

	Tile* tile = GetTile(m, nextPos);

	if (tile != NULL && tile->moveable == 0)
	{
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
