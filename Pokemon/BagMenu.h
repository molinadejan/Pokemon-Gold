#pragma once

#ifndef __BAGMENU_H__
#define __BAGMENU_H__

#include "BaseClass.h"

class BagMenu : public BaseClass
{

private:

	enum BagState 
	{
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
	~BagMenu() = default;

	void Draw(Graphics& g) override;
	void Update() override;
};

#endif // !__BAGMENU_H__
