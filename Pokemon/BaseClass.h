#pragma once

#ifndef __BASECLASS_H__
#define __BASECLASS_H__

#include "framework.h"
#include "GameManager.h"

using namespace Gdiplus;

class GameManager;

class BaseClass
{
protected:

	GameManager* gm;

public:

	BaseClass();
	~BaseClass();

	void SetManager(GameManager* _gm);
	virtual void Update();
	virtual void Draw(Graphics& g);
};

#endif