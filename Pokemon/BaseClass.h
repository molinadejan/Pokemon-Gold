#pragma once

#include "framework.h"

using namespace Gdiplus;

class BaseClass
{
public:

	BaseClass() {}

	virtual void Update() {}
	virtual void Draw(Graphics& g) {}
};
