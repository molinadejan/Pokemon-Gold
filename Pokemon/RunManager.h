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

		Run() = default;
		~Run() = default;

	private:

		drawPtr draw;
		updatePtr update;

		BaseClass* target;
		BaseClass* oldTarget;

		bool isChange;
		bool isFading;

	private:

		void SetFunc();

		void _SetTarget(BaseClass* _base, float _fadeTime = 1.0f);
		void SetTarget(BaseClass* _base, float _fadeTime = 1.0f);

		void SetTargetWithoutFade(BaseClass* _base);

		void Init();
	};

private:

	static Run run;
	static float tp;

private:

	RunManager() = delete;
	~RunManager() = delete;

public:

	static void SetTarget(BaseClass* _base, float _fadeTime = 1.0f) { run.SetTarget(_base, _fadeTime); }
	static void SetTargetWithoutFade(BaseClass* _base) { run.SetTargetWithoutFade(_base); }

	static void Init() { run.Init(); }
	static void Update();
	static void Draw(HWND hWnd);
};

#define RM RunManager

#endif