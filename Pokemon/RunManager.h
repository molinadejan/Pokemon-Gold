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
		BaseClass* oldTarget;

		bool isChange;
		bool isFading;

	private:

		void setFunc();

		void _setTarget(BaseClass* _base, float _fadeTime = 1.0f);
		void setTarget(BaseClass* _base, float _fadeTime = 1.0f);

		void reset();
	};

private:

	static Run run;
	static float tp;

private:

	RunManager() = delete;
	~RunManager() = delete;

public:

	static void Reset();
	static void SetTarget(BaseClass* _base, float _fadeTime = 1.0f);
	static void SetTargetWithoutFade(BaseClass* _base);

	static void Update();
	static void Draw(HWND hWnd);
};

#define RM RunManager

#endif