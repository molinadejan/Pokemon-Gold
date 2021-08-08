#include "BagItemToss.h"
#include "BagMenu.h"
#include "BagItemSelect.h"
#include "InputManager.h"
#include "UIManager.h"
#include "RunManager.h"
#include "DataLoadManager.h"
#include "BagItemTossConfirm.h"
#include "TransDatas.h"
#include "GdiplusElement.h"

BagItemToss::BagItemToss()
 : tossCount(1) { }

void BagItemToss::ResourceInit()
{
	BaseClass::ResourceInit();
	bag = DataLoadManager::GetUI_Bag();
}

void BagItemToss::DrawTossText(Graphics & g)
{
	TransString(buffer, "bag_item_toss");
	g.DrawString(buffer, -1, FONT_BIG, descRect, LEFT_ALIGN, BLACK);
}

void BagItemToss::DrawTossCount(Graphics & g)
{
	UIManager::DrawDialogUI_IDX(g, 7, 4, 3, 2);

	RectF tossCountRect(7 * MUL, 4 * MUL, 2.5f * MUL, 2 * MUL);
	_stprintf_s(buffer, _T("%02d"), tossCount);
	g.DrawString(buffer, -1, FONT_BIG, tossCountRect, RIGHT_ALIGN, BLACK);

	Rect tossXRect(7 * MUL, 4.5f * MUL, 1 * MUL, 1 * MUL);
	g.DrawImage(bag, tossXRect, 10 * PIXEL, 2 * PIXEL, 1 * PIXEL, 1 * PIXEL, UnitPixel);
}

void BagItemToss::Draw(Graphics & g)
{
	BagMenu* bagMenu = gm->bagMenu;

	bagMenu->DrawBagUI(g);
	bagMenu->DrawBottomDialog(g);

	DrawTossText(g);

	bagMenu->DrawBagTypeAndText(g);
	bagMenu->DrawItemList(g);
	bagMenu->DrawItemCursor(g);

	DrawTossCount(g);
}

void BagItemToss::Update()
{
	int maxCount = gm->bagMenu->GetCurSelectInventoryItemData()->count;

	if (GET_KEY_UP && tossCount < maxCount)
		++tossCount;
	else if (GET_KEY_DOWN && tossCount > 1)
		--tossCount;

	if (GET_KEY_Z)
	{
		RunManager::SetTarget(gm->bagItemTossConfirm);
	}

	if (GET_KEY_X)
	{
		tossCount = 1;
		RunManager::SetTarget(gm->bagMenu);
	}
}
