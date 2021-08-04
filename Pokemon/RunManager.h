#pragma once

#ifndef __RUNMANAGER_H__
#define __RUNMANAGER_H__

#include "BaseClass.h"

#include "GamePlay.h"
#include "BagMenu.h"
#include "MainMenu.h"
#include "GameFadeInOut.h"

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

	private:

		void reset();
	};

private:

	static Run run;

private:

	RunManager() = delete;
	~RunManager() = delete;

public:

	static void Reset();
	static void SetTarget(BaseClass* _base);

	static void Update();
	static void Draw(HWND hWnd);
};

#endif