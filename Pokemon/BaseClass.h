#pragma once

#ifndef __BASECLASS_H__
#define __BASECLASS_H__

#include "framework.h"
#include "GameManager.h"
#include "DataLoadManager.h"

#define R(X) (REAL)(X)

using namespace Gdiplus;

class GameManager;

class BaseClass
{
protected:

	GameManager* gm;

	TCHAR buffer[256];

public:

	BaseClass();
	~BaseClass();

	virtual void ResourceInit();
	virtual void Init() { };
	virtual void Reset() { };

	void SetManager(GameManager* _gm);
	virtual void Update();
	virtual void Draw(Graphics& g);
};

#endif