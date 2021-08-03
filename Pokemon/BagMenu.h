#pragma once

#ifndef __BAGMENU_H__
#define __BAGMENU_H__

#include "framework.h"

using namespace Gdiplus;

class BagMenu
{
public:
	enum BagState {
		Item = 0,
		Ball = 1,
		KeyItem = 2,
		Machine = 3,
	};


private:

	BagState state;
	int curSelect;

public:

	BagMenu();

	void DrawBag(Graphics& g);
	void UpdateBag();
};

#endif // !__BAGMENU_H__
