#include "Intro.h"
#include "Timer.h"
#include "DataLoadManager.h"
#include "InputManager.h"
#include "RunManager.h"
#include "SoundManager.h"

void Intro::Init()
{
	introImg = DM::GetUIImage("intro");

	backgroundTimer = 0.0f;
	turquiseTimer = 0.0f;

	cloudPosX = 0;

	turquoiseVec = DM::GetAnimRect("intro_turquoise");
	turquiseFrameCnt = 0;

	for (int i = 0; i < 5; ++i)
		pos[i] = particles[i];

	SM::ChangeBgmWithoutFade("intro", true);
}

void Intro::Update()
{
	backgroundTimer += Timer::DeltaTime();
	turquiseTimer += Timer::DeltaTime();

	if (backgroundTimer >= 0.35f)
	{
		backgroundTimer = 0.0f;
		
		++cloudPosX;

		if (cloudPosX == 32)
			cloudPosX = 0;
	}

	if (turquiseTimer >= 0.2f)
	{
		turquiseTimer = 0.0f;

		++turquiseFrameCnt;

		if (turquiseFrameCnt == (int)turquoiseVec->size())
			turquiseFrameCnt = 0;
	}

	for (int i = 0; i < 5; ++i)
	{
		pos[i].X += dirs[i].X * Timer::DeltaTime() * 600.0f;
		pos[i].Y += dirs[i].Y * Timer::DeltaTime() * 600.0f;

		if (pos[i].X >= 10 * MUL || pos[i].Y >= 9 * MUL)
			pos[i] = particles[i];
	}
	
	if (GET_KEY_Z)
		RM::SetTarget(GM::game.gameStart, 2.0f);
}

void Intro::Draw(Graphics & g)
{
	g.DrawImage(introImg, TitleRect, 0, 0, 10 * PIXEL, 6 * PIXEL, UnitPixel);
	g.DrawImage(introImg, CloudRect, cloudPosX, 6 * PIXEL, 10 * PIXEL, 2 * PIXEL, UnitPixel);
	g.DrawImage(introImg, CompanyRect, 0, 8 * PIXEL, 10 * PIXEL, PIXEL, UnitPixel);
	g.DrawImage(introImg, turquiseRect, (*turquoiseVec)[turquiseFrameCnt].X, (*turquoiseVec)[turquiseFrameCnt].Y, (*turquoiseVec)[turquiseFrameCnt].Width, (*turquoiseVec)[turquiseFrameCnt].Height, UnitPixel);

	for (int i = 0; i < 5; ++i)
	{
		g.DrawImage(introImg, Rect(INT(pos[i].X), INT(pos[i].Y), 18 * SCREEN_MUL, 16 * SCREEN_MUL), 11 * PIXEL, 4 * PIXEL, 18, 16, UnitPixel);
	}
}
