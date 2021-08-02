#include "Player.h"
#include "MyUtils.h"
#include "DataLoadManager.h"
#include "InputManager.h"
#include <cmath>

Player::Player()
	: pos{ 0, 0 }, posF{ (REAL)pos.X, (REAL)pos.Y }, moveDir{ 0, 0 }, inputDir(0, 0), speed(3.0f), isMoving(false) { }

Player::~Player() { }

void Player::DrawPlayer(Graphics &g)
{
	Image *img = DataLoadManager::GetPlayer_game();
	Rect r((COL / 2) * PIXEL * SCREEN_MUL, (ROW / 2 - 0.25f) * PIXEL * SCREEN_MUL, PIXEL * SCREEN_MUL, PIXEL * SCREEN_MUL);

	int spriteTargetX = 0, curFrameCnt = 0;

	if (moveDir.X != 0 && moveDir.Y == 0)
	{
		spriteTargetX = moveDir.X == 1 ? 0 : 2;
		curFrameCnt = isMoving ? frameCount % DIR_HORIZONTAL_FRAME_CNT : 0;
	}
	else if (moveDir.X == 0 && moveDir.Y != 0)
	{
		spriteTargetX = moveDir.Y == 1 ? 4 : 7;

		if (isMoving)
		{
			curFrameCnt = frameCount % DIR_VERTICAL_FRAME_CNT;
			curFrameCnt = curFrameCnt % 2 == 0 ? 0 : curFrameCnt / 2 + 1;
		}
		else curFrameCnt = 0;
	}

	g.DrawImage(img, r, (spriteTargetX + curFrameCnt) * PIXEL, 0, PIXEL, PIXEL, UnitPixel);
}

void Player::MovePlayer(Map* &m)
{
	if (isMoving)
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
	else
	{
		inputDir = { InputManager::GetHorizontal(), InputManager::GetVertical() };

		if (inputDir == Point(0, 0))
			return;

		//// Check Move to neighbor map ////
		Map* nMap = GetNMap(m, pos);

		if (nMap != NULL)
		{
			SetPos(pos + m->worldPos - nMap->worldPos);
			m = nMap;
		}
		//// Check Move to neighbor map ////

		//// Check Move to Door ////
		bool ignoreInput = false;

		MovePoint* mp = m->GetMovePoint(pos);

		if (mp != NULL && mp->isDoor())
		{
			m = DataLoadManager::GetMapData(mp->targetID);
			SetPos(mp->targetPos);

			MovePoint* newMp = m->GetMovePoint(pos);

			if (newMp != NULL && newMp->isDoor())
			{
				inputDir = newMp->GetDir();
				ignoreInput = true;
			}
		}
		//// Check Move to Door ////

		//// Input ////
		if (!ignoreInput)
		{
			/*inputDir = { InputManager::GetHorizontal(), InputManager::GetVertical() };

			if (inputDir == Point(0, 0))
				return;*/

			//// Check Move on Carpet ////
			mp = m->GetMovePoint(pos);

			if (mp != NULL && mp->isCarpet())
			{
				if (mp->GetDir() == inputDir)
				{
					m = DataLoadManager::GetMapData(mp->targetID);
					SetPos(mp->targetPos);

					MovePoint* newMp = m->GetMovePoint(pos);

					if (newMp != NULL && newMp->isDoor())
						inputDir = newMp->GetDir();
				}
			}
			//// Check Move on Carpet ////
		}
		//// Input ////

		//// Player Move ////
		Point nextPos = pos + inputDir;
		moveDir = inputDir;

		Tile* tile = GetTile(m, nextPos);

		if (tile != NULL && tile->moveable == 0)
		{
			nextTilePos = nextPos;

			isMoving = true;
			distance = 1.0f;
		}
		//// Player Move ////
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
