#include "GameFadeInOut.h"
#include "RunManager.h"
#include "Timer.h"

GameFadeInOut::GameFadeInOut()
	: fadeTimer(0.0f)
{ }

void GameFadeInOut::Draw(Graphics & g)
{
	gm->gamePlay->Draw(g);

	int tp = 255 * ((FADETIME - fadeTimer) / (FADETIME));
	SolidBrush brush(Color(tp, 0, 0, 0));
	g.FillRectangle(&brush, 0, 0, SCREEN_SIZE_X, SCREEN_SIZE_Y);
}

void GameFadeInOut::Update()
{
	fadeTimer += Timer::DeltaTime();

	if (fadeTimer > FADETIME)
	{
		fadeTimer = 0.0f;
		RunManager::SetTarget(gm->gamePlay);
	}
}
