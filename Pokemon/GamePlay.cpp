#include "GamePlay.h"
#include "InputManager.h"
#include "MyUtils.h"
#include "DataLoadManager.h"
#include "RunManager.h"
#include "GdiplusElement.h"
#include "BattleScreen.h"
#include "SoundManager.h"
#include "PokemonCalculator.h"

#include <cmath>
#include <thread>
#include <chrono>

using std::thread;
using namespace std::chrono;

GamePlay::GamePlay() 
	: curData(NULL), isMapChange(false), isFirstLoad(false), checkCnt(0), tp(0)
{ }

void GamePlay::DrawMap(Graphics& g)
{
	Image* img = DM::GetMapImage(curData->ID);

	PointF pos = player->GetPosF();

	Point rectOrigin  = Point( INT((4 - pos.X) * PIXEL), INT((4 - pos.Y) * PIXEL) );
	Point imageOrigin = Point( INT((pos.X - 5) * PIXEL), INT((pos.Y - 5) * PIXEL) );

	for (string& nID : curData->neighbors)
	{
		Image *nImg = DM::GetMapImage(nID);
		Map* n = DM::GetMapData(nID);
		
		Point diff = curData->worldPos - n->worldPos;

		Point nRectOrigin  = rectOrigin  - diff * PIXEL;
		Point nImageOrigin = imageOrigin + diff * PIXEL;

		Clamp(nRectOrigin.X, -PIXEL, 11 * PIXEL);
		Clamp(nRectOrigin.Y, -PIXEL, 10 * PIXEL);

		Clamp(nImageOrigin.X, 0, n->mapSize.X * PIXEL);
		Clamp(nImageOrigin.Y, 0, n->mapSize.Y * PIXEL);

		Rect nRect = { nRectOrigin.X * SCREEN_MUL, nRectOrigin.Y * SCREEN_MUL,  (11 * PIXEL - nRectOrigin.X) * SCREEN_MUL, (10 * PIXEL - nRectOrigin.Y) * SCREEN_MUL };

		if (nImageOrigin.X >= (int)nImg->GetWidth() || nImageOrigin.Y >= (int)nImg->GetHeight() || nImageOrigin.X + 11 * PIXEL - nRectOrigin.X <= 0 || nImageOrigin.Y + 10 * PIXEL - nRectOrigin.Y <= 0)
			continue;

		g.DrawImage(nImg, nRect, nImageOrigin.X, nImageOrigin.Y, 11 * PIXEL - nRectOrigin.X, 10 * PIXEL - nRectOrigin.Y, UnitPixel);
	}

	Clamp(rectOrigin.X, -PIXEL, 11 * PIXEL);
	Clamp(rectOrigin.Y, -PIXEL, 10 * PIXEL);

	Clamp(imageOrigin.X, 0, curData->mapSize.X * PIXEL);
	Clamp(imageOrigin.Y, 0, curData->mapSize.Y * PIXEL);

	Rect rect = { rectOrigin.X * SCREEN_MUL, rectOrigin.Y * SCREEN_MUL,  (11 * PIXEL - rectOrigin.X) * SCREEN_MUL, (10 * PIXEL - rectOrigin.Y) * SCREEN_MUL };
	g.DrawImage(img, rect, imageOrigin.X, imageOrigin.Y, 11 * PIXEL - rectOrigin.X, 10 * PIXEL - rectOrigin.Y, UnitPixel);
}

void GamePlay::DrawDebug(Graphics& g)
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

void GamePlay::DrawEncounterAnimation(Graphics & g)
{
	Rect imageRect = (*encounterRect)[frameCnt];
	g.DrawImage(encounterImg, Rect(0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y), imageRect.X, imageRect.Y, imageRect.Width, imageRect.Height, UnitPixel);
}

void GamePlay::_Encounter()
{
	SM::ChangeBgmWithoutFade("battle_encounter", false);

	int twinkleCnt = 0;
	int _add = 25;

	auto prevClock = high_resolution_clock::now();

	while (twinkleCnt < 4)
	{
		auto nextClock = high_resolution_clock::now();
		double deltaTime = (nextClock - prevClock).count() / 1e9;

		auto frameClock = high_resolution_clock::now();
		double sleepSecs = 1.0 / 80 - (frameClock - nextClock).count() / 1e9;

		tp += _add;

		if (tp >= 255)
		{
			tp = 255;
			_add *= -1;
		}
		else if (tp <= 0)
		{
			++twinkleCnt;

			tp = 0;
			_add *= -1;
		}

		if (sleepSecs > 0)
			std::this_thread::sleep_for(nanoseconds((int64_t)(sleepSecs * 1e9)));

		prevClock = nextClock;
	}

	double timer = 0.0f;

	prevClock = high_resolution_clock::now();

	while (frameCnt < (int)encounterRect->size() - 1)
	{
		auto nextClock = high_resolution_clock::now();
		double deltaTime = (nextClock - prevClock).count() / 1e9;

		auto frameClock = high_resolution_clock::now();
		double sleepSecs = 1.0 / 60 - (frameClock - nextClock).count() / 1e9;

		++frameCnt;

		if (sleepSecs > 0)
			std::this_thread::sleep_for(nanoseconds((int64_t)(sleepSecs * 1e9)));

		prevClock = nextClock;
	}

	SM::ChangeBgmWithoutFade("battle_battle", true);
	isEncounter = false;

	frameCnt = 0;
	GM::game.battleScreen->InitWildBattle(1, 5);
	RM::SetTargetWithoutFade(GM::game.battleScreen);
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

			SM::ChangeBgmWithFade(curData->music);

			return;
		}

		if (isMapChange)
			SM::ChangeBgmWithFade(curData->music);

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

				SM::PlayEffect("door");
				RM::SetTarget(GM::game.gamePlay, 0.3f);
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

				SM::PlayEffect("carpet");
				RM::SetTarget(GM::game.gamePlay, 0.3f);
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
		player = new Player();
		player->SetPos(DM::GetPlayerData()->pos);
		curData = DM::GetMapData(DM::GetPlayerData()->locationID);
		isFirstLoad = true;
		encounterImg = DM::GetUIImage("encounter");
		encounterRect = DM::GetAnimRect("encounter");
	}

	SM::ChangeBgmWithFade(curData->music);
}

void GamePlay::Update()
{
	if (isEncounter)
		return;

	UpdatePlayer();

	if (GET_KEY_ENTER && !player->GetIsMoving())
	{
		SM::PlayEffect("bagOpen");
		RM::SetTargetWithoutFade(GM::game.mainMenu);
	}

	if (player->GetIsMoving())
	{
		checkCnt = 0;
	}
	else
	{
		if (checkCnt == 0)
		{
			Tile* tile = GetTile(curData, player->GetPos());

			if (tile != NULL && tile->isPokemon == 1 && GetRandom(3.0f))
			{
				isEncounter = true;

				std::thread t(&GamePlay::_Encounter, this);
				t.detach();
			}
		}

		checkCnt = 1;
	}
}

void GamePlay::Draw(Graphics& g)
{
	DrawMap(g);
	player->DrawPlayer(g);

	if (isEncounter)
	{
		DrawEncounterAnimation(g);

		SolidBrush brush(Color(tp, 0, 0, 0));
		g.FillRectangle(&brush, 0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
	}

	//DrawDebug(g);
}
