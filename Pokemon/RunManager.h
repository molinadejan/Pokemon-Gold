#pragma once

#ifndef __RUNMANAGER_H__
#define __RUNMANAGER_H__

#include "BaseClass.h"

#include "GamePlay.h"
#include "BagMenu.h"
#include "MainMenu.h"
#include "GameFadeInOut.h"
#include "BattleScreen.h"
#include "GameStart.h"
#include "Intro.h"

#define SCENE_CHANGE_TIME 0.3f
#define SCENE_CHANGE_TIME_HALF 0.15f

class RunManager
{
private:

	typedef void(BaseClass::*drawPtr)(Graphics& g);
	typedef void(BaseClass::*updatePtr)(void);

private:

	class Run
	{
		friend RunManager;

	private:

		Run();
		~Run();

	private:

		drawPtr draw;
		updatePtr update;
		bool isPop;

		BaseClass* target;
		BaseClass* newTarget;

	private:

		void reset();
	};

private:

	static Run run;
	static bool isSceneChange;
	static float sceneChangeTimer;
	static float tp;
	static float fadeSpeed;

private:

	RunManager() = delete;
	~RunManager() = delete;

	static void SetFunc();

public:

	static void Reset();
	static void SetTarget(BaseClass* _base, float _fadeSpeed = 3000.0f);
	static void SetTargetWithoutFade(BaseClass* _base);

	static void Update();
	static void Draw(HWND hWnd);
};

#endif