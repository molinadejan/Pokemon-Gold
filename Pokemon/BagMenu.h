#pragma once

#ifndef __BAGMENU_H__
#define __BAGMENU_H__

#define R(X) (REAL)(X)

#include "BaseClass.h"

class BagMenu : public BaseClass
{

private:

	const TCHAR *ITEM_TYPE[4] = { _T("도구"), _T("볼"), _T("중요한"), _T("기술머신") };

	const Rect bagUIRect = { 0, 0, SCREEN_SIZE_X, 6 * MUL };
	const RectF bagTypeTextRect = { R(2 * SCREEN_MUL), R(58 * SCREEN_MUL), R(36 * SCREEN_MUL), R(20 * SCREEN_MUL) };
	const RectF bagTypeImageRect = { R(0), R(24 * SCREEN_MUL), R(40 * SCREEN_MUL), R(24 * SCREEN_MUL) };
	const RectF descRect = { MUL, 6 * MUL, (COL - 2) * MUL, 3 * MUL };

	const Rect bagTypeImage = { 40, 96, 40, 24 };
	const Rect bagUI = { 0, 0, 10 * PIXEL, 6 * PIXEL };
	const Rect X = { 10 * PIXEL, 2 * PIXEL, PIXEL, PIXEL };
	const Rect cursor = { 10 * PIXEL, 0, PIXEL, PIXEL };

	RectF GetItemTextRectF(int i);
	Rect GetXRect(int i);
	RectF GetItemCountRectF(int i);
	Rect GetCursorRect(int i);

	Image* bag;

private:

	enum BagState 
	{
		Tool = 0,
		Ball = 1,
		Important = 2,
		Machine = 3,
	};

private:

	BagState state;
	int curBagSelect;

	int curSelectIdx[4];
	int curSelect[4];

public:

	BagMenu();
	~BagMenu() = default;

	void ResourceInit() override;
	void Draw(Graphics& g) override;
	void Update() override;
};

#endif // !__BAGMENU_H__
