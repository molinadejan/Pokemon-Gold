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

	const TCHAR* CHOICE[4] = { _T("사용하다"), _T("지니게하다"), _T("버리다"), _T("그만두다") };
	const float CHOICE_H = (5 * MUL) / 5.0f;

private:

	void DrawChoices(Graphics& g);

private:

	int curSelect;
	Image* dialog;

public:

	BagItemSelect();
	~BagItemSelect() = default;

	void ResourceInit() override;
	void Draw(Graphics& g) override;
	void Update() override;
};

#endif