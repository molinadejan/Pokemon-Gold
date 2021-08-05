#pragma once

#ifndef __BASECLASS_H__
#define __BASECLASS_H__

#include "framework.h"
#include "GameManager.h"
#include "DataLoadManager.h"

using namespace Gdiplus;

class GameManager;

class BaseClass
{
protected:

	GameManager* gm;

	SolidBrush* black;
	SolidBrush* white;

	Font* fontS;
	Font* fontM;
	Font* fontB;

	TCHAR buffer[256];

	StringFormat* leftAlign;
	StringFormat* centerAlign;
	StringFormat* rightAlign;

public:

	BaseClass();
	~BaseClass();

	virtual void ResourceInit();

	void SetManager(GameManager* _gm);
	virtual void Update();
	virtual void Draw(Graphics& g);
};

#endif