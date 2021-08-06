#pragma once

#ifndef __BAGITEMSELECT_H__
#define __BAGITEMSELECT_H__

#include "BaseClass.h"

// 일반 상태인지, 전투상태인지
// 아이템의 타입이 무엇인지에 따라서 보여주는 메뉴가 달라야 한다.
// 나중에 추가 필요

class BagItemSelect :public BaseClass
{
private:

	const float CHOICE_H = (5 * MUL) / 5.0f;

	RectF GetChoiceRect(int i) { return RectF(R(MUL), R(1.5f * MUL + CHOICE_H * i), R(2 * MUL), R(MUL)); }
	Rect  GetCursorRect(int i) { return Rect (0, INT(1.6f * MUL + CHOICE_H * curSelect), MUL, MUL); }

private:

	enum ChoiceState
	{
		USE,
		GIVE,
		TOSS,
		QUIT
	};

private:

	void DrawChoices(Graphics& g);

private:

	int curSelect;
	ChoiceState curState;
	Image* dialog;

public:

	BagItemSelect();
	~BagItemSelect() = default;

	void ResourceInit() override;
	void Draw(Graphics& g) override;
	void Update() override;
};

#endif