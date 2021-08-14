#include "GamePlay.h"
#include "InputManager.h"
#include "MyUtils.h"
#include "DataLoadManager.h"
#include "RunManager.h"
#include "GdiplusElement.h"
#include "BattleScreen.h"

#include <cmath>

GamePlay::GamePlay() 
	: curData(NULL), isMapChange(false), isFirstLoad(false) 
{ }

GamePlay::~GamePlay() { }

void GamePlay::DrawMap(Graphics & g, PointF origin)
{
	Image* img = DM::GetMapImage(curData->ID);

	Rect expansion((INT)round(-origin.X * MUL), (INT)round(-origin.Y * MUL), img->GetWidth() * SCREEN_MUL, img->GetHeight() * SCREEN_MUL);

	g.DrawImage(img, expansion);

	for (string& nID : curData->neighbors)
	{
		Image *nImg = DM::GetMapImage(nID);
		Map* n = DM::GetMapData(nID);

		Point diff = curData->worldPos - n->worldPos;

		Rect expansion2((INT)round(-(origin.X + diff.X) * MUL), (INT)round(-(origin.Y + diff.Y) * MUL), nImg->GetWidth() * SCREEN_MUL, nImg->GetHeight() * SCREEN_MUL);
		g.DrawImage(nImg, expansion2);
	}
}

void GamePlay::DrawDebug(Graphics & g)
{
	_tcscpy_s(buffer, CA2T(curData->ID.c_str()));
	
	RectF rectF1(0, 0, 64 * SCREEN_MUL, 8 * SCREEN_MUL);
	g.DrawString(buffer, -1, FONT_SMALL, rectF1, NULL, WHITE);

	_stprintf_s(buffer, _T("Áö¿ª ÁÂÇ¥ : %d %d"), player->GetPos().X, player->GetPos().Y);

	RectF rectF2(0, 8 * SCREEN_MUL, 64 * SCREEN_MUL, 8 * SCREEN_MUL);
	g.DrawString(buffer, -1, FONT_SMALL, rectF2, NULL, WHITE);

	_stprintf_s(buffer, _T("¿ùµå ÁÂÇ¥ : %d %d"), player->GetPos().X + curData->worldPos.X, player->GetPos().Y + curData->worldPos.Y);

	RectF rectF3(0, 16 * SCREEN_MUL, 64 * SCREEN_MUL, 8 * SCREEN_MUL);
	g.DrawString(buffer, -1, FONT_SMALL, rectF3, NULL, WHITE);
}

void GamePlay::UpdatePlayer()
{
	player->FrameUpdate();

	if (player->GetIsMoving())
		player->MovingPlayer();
	else
	{
		//// Move To Neighbor Map ////
		Map* nMap = NULL;

		if (player->IsOnNMap(curData, nMap))
		{
			player->SetPos(player->GetPos() + curData->worldPos - nMap->worldPos);
			curData = nMap;
			return;
		}

		//// Move To Door
		MovePoint* mpDoor = NULL;

		if (player->isOnDoor(curData, mpDoor))
		{
			if (isMapChange)
			{
				player->MovePlayer(curData, mpDoor->GetDir());
				isMapChange = false;
			}
			else
			{
				curData = DM::GetMapData(mpDoor->targetID);
				player->SetPos(mpDoor->targetPos);
				isMapChange = true;

				RunManager::SetTarget(gm->gamePlay);
			}

			return;
		}

		isMapChange = false;

		//// Input
		Point inputDir(GET_KEY_HORIZONTAL, GET_KEY_VERTICAL);

		if (inputDir == Point(0, 0))
			return;

		//// Move On Carpet
		MovePoint* mpCarpet = NULL;

		if (player->isOnCarpet(curData, mpCarpet))
		{
			if (mpCarpet->GetDir() == inputDir)
			{
				curData = DM::GetMapData(mpCarpet->targetID);
				player->SetPos(mpCarpet->targetPos);
				isMapChange = true;

				RunManager::SetTarget(gm->gamePlay);
				return;
			}
		}

		//// Move Player
		player->MovePlayer(curData, inputDir);
	}
}

void GamePlay::Init()
{
	if (!isFirstLoad)
	{
		PlayerData* data = DM::GetPlayerData();
		player = new Player();
		player->SetPos(data->pos);
		curData = DM::GetMapData(data->locationID);
		isFirstLoad = true;
	}
}

void GamePlay::Update()
{
	UpdatePlayer();

	if (GET_KEY_ENTER && !player->GetIsMoving())
	{
		gm->bagSound->play();
		RunManager::SetTargetWithoutFade(gm->mainMenu);
	}

	// test
	/*if (IM::GetKeyUp('P'))
	{
		gm->battleScreen->InitWildBattle(1, 5);
		RunManager::SetTarget(gm->battleScreen);
	}*/
}

void GamePlay::Draw(Graphics& g)
{
	PointF playerPos = player->GetPosF();
	PointF mapOrigin(playerPos.X - REAL(COL / 2 - 1), playerPos.Y - REAL(ROW / 2));

	DrawMap(g, mapOrigin);
	player->DrawPlayer(g);

	DrawDebug(g);
}
