#pragma once

#ifndef __BASECLASS_H__
#define __BASECLASS_H__

#include "framework.h"
#include "GameManager.h"
#include "DataLoadManager.h"

#define R(X) (REAL)(X)

using namespace Gdiplus;

class BaseClass
{
protected:

	TCHAR buffer[256];

public:

	BaseClass() = default;
	~BaseClass() = default;

	virtual void ResourceInit() { }
	virtual void Init() { }
	virtual void Reset() { }

	virtual void Update() { }
	virtual void Draw(Graphics& g) { }
};

#endif