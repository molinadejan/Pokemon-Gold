#pragma once

#ifndef __BAGMENU_H__
#define __BAGMENU_H__

#include "BaseClass.h"

class BagMenu : public BaseClass
{
private:

	const Rect  bagUIRect        = { 0                , 0                 , SCREEN_SIZE_X     , 6 * MUL            };
	const RectF poketTextRect    = { R(2 * SCREEN_MUL), R(58 * SCREEN_MUL), R(36 * SCREEN_MUL), R(20 * SCREEN_MUL) };
	const RectF poketImageRect   = { R(0)             , R(24 * SCREEN_MUL), R(40 * SCREEN_MUL), R(24 * SCREEN_MUL) };
	const RectF descRect         = { MUL              , 6 * MUL           , (COL - 2) * MUL   , 3 * MUL            };

	const Rect poketImage   = { 40        , 96       , 40        , 24        };
	const Rect bagUI        = { 0         , 0        , 10 * PIXEL, 6 * PIXEL };
	const Rect X            = { 10 * PIXEL, 2 * PIXEL, PIXEL     , PIXEL     };
	const Rect cursor       = { 10 * PIXEL, 0        , PIXEL     , PIXEL     };

	RectF GetItemTextRectF  (int i) { return RectF(R(4 * MUL), R((i + 1) * MUL), R(4 * MUL), R(MUL)); }
	Rect  GetXRect          (int i) { return Rect (7 * MUL   , (i + 1) * MUL   , MUL       , MUL   ); }
	RectF GetItemCountRectF (int i) { return RectF(R(8 * MUL), R((i + 1) * MUL), R(2 * MUL), R(MUL)); }
	Rect  GetCursorRect     (int i) { return Rect (3 * MUL   , (i + 1) * MUL   , MUL       , MUL   ); }

	Image* bag;
	PlayerData* pData;

public:

	enum BagState
	{
		Tool = 0,
		Ball = 1,
		Important = 2,
		Machine = 3,
	};

private:

	//BagState state;
	int poketSelect;

	int curSelectIdx[4];
	int curSelect[4];

public:

	void DrawBagUI(Graphics &g);
	void DrawBottomDialog(Graphics &g);
	void DrawBagTypeAndText(Graphics &g);

	void DrawItemList(Graphics &g);
	void DrawItemCursor(Graphics &g);
	void DrawItemDesc(Graphics &g);

private:

	void UpdatePoketSelect();
	void UpdateItemSelect();

public:

	BagMenu();
	~BagMenu() = default;

	InventoryItemData* GetCurSelectInventoryItemData();

	void ResourceInit() override;
	void Draw(Graphics& g) override;
	void Update() override;
};

#endif // !__BAGMENU_H__
