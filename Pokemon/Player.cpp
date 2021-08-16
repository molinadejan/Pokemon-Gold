#include "Player.h"
#include "MyUtils.h"
#include "DataLoadManager.h"
#include "InputManager.h"
#include "Timer.h"
#include <cmath>

Player::Player()
	: pos{ 0, 0 }, posF{ (REAL)pos.X, (REAL)pos.Y }, moveDir{ 0, 0 }, inputDir(0, 0), speed(3.5f), isMoving(false), frameChangeTime(0.0f) 
{ 
	playerImg = DM::GetPlayerInGame();

	walkAnim[0] = DM::GetAnimRect("player_walk_left");
	walkAnim[1] = DM::GetAnimRect("player_walk_right");
	walkAnim[2] = DM::GetAnimRect("player_walk_up");
	walkAnim[3] = DM::GetAnimRect("player_walk_down");
}

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
	Rect r((COL / 2 - 1) * PIXEL * SCREEN_MUL, (ROW / 2 - 0.25f) * PIXEL * SCREEN_MUL, PIXEL * SCREEN_MUL, PIXEL * SCREEN_MUL);

	Rect imagePos = walkAnim[curDir][frameCount % walkAnim[curDir].size()];

	g.DrawImage(playerImg, r, imagePos.X, imagePos.Y, imagePos.Width, imagePos.Height, UnitPixel);
}

void Player::MovePlayer(Map*& m, Point dir)
{
	inputDir = dir;

	if (dir.X == 1)
		curDir = RIGHT;
	else if (dir.X == -1)
		curDir = LEFT;
	else if (dir.Y == 1)
		curDir = DOWN;
	else if (dir.Y == -1)
		curDir = UP;

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
	if (isMoving || frameCount % 2 == 1)
	{
		frameChangeTime += Timer::DeltaTime();

		if (frameChangeTime >= FRAME_TIME)
		{
			frameChangeTime = 0.0f;

			++frameCount;
			frameCount %= (int)walkAnim[3].size();
		}
	}
}
