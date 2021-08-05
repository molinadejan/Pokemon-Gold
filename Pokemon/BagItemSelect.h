#pragma once

#ifndef __BAGITEMSELECT_H__
#define __BAGITEMSELECT_H__

#include "BaseClass.h"

class BagItemSelect :public BaseClass
{
private:



public:

	BagItemSelect();
	~BagItemSelect() = default;

	void Draw(Graphics& g) override;
	void Update() override;
};

#endif