#include "BagMenu.h"
#include "DataLoadManager.h"
#include "InputManager.h"
#include "UIManager.h"
#include "RunManager.h"
#include "MyUtils.h"
#include "BagItemSelect.h"
#include "TransDatas.h"
#include "GdiplusElement.h"
#include "SoundManager.h"

BagMenu::BagMenu() : poketSelect(0)
{
	curSelect[0] = curSelect[1] = curSelect[2] = curSelect[3] = 0;
	curSelectIdx[0] = curSelectIdx[1] = curSelectIdx[2] = curSelectIdx[3] = 0;
}

void BagMenu::DrawBagUI(Graphics & g)
{
	g.DrawImage(DM::GetUIImage("bagUI"), bagUIRect, bagUI.X, bagUI.Y, bagUI.Width, bagUI.Height, UnitPixel);
}

void BagMenu::DrawBottomDialog(Graphics & g)
{
	UM::DrawDialogUI_IDX(g, 0, ROW - 3, COL, 3);
}

void BagMenu::DrawBagTypeAndText(Graphics & g)
{
	g.DrawImage(DM::GetUIImage("bagUI"), poketImageRect, R(poketSelect * poketImage.X), R(poketImage.Y), R(poketImage.Width), R(poketImage.Height), UnitPixel);

	TransString(buffer, "poket_type_" + std::to_string(poketSelect));
	g.DrawString(buffer, -1, FONT_BIG, poketTextRect, CENTER_ALIGN, WHITE);
}

void BagMenu::DrawItemList(Graphics & g)
{
	int size = int(DM::GetPlayerData()->iData[poketSelect].size());
	int curS = curSelect[poketSelect];
	int curSI = curSelectIdx[poketSelect];

	for (int i = 0; i < 5; ++i)
	{
		int itemIdx = curS + i - curSI;

		if (itemIdx > size - 1)
			break;

		int code = DM::GetPlayerData()->iData[poketSelect][itemIdx]->code;
		int count = DM::GetPlayerData()->iData[poketSelect][itemIdx]->count;

		// 아이템 이름
		string itemName = DM::GetItemDesc(code)->name;
		_tcscpy_s(buffer, CA2T(itemName.c_str()));
		g.DrawString(buffer, -1, FONT_BIG, GetItemTextRectF(i), LEFT_ALIGN, BLACK);

		// X 출력
		g.DrawImage(DM::GetUIImage("bagUI"), GetXRect(i), X.X, X.Y, X.Width, X.Height, UnitPixel);

		// 개수 출력
		_stprintf_s(buffer, _T("%d"), count);
		g.DrawString(buffer, -1, FONT_BIG, GetItemCountRectF(i), RIGHT_ALIGN, BLACK);
	}
}

void BagMenu::DrawItemCursor(Graphics& g)
{
	g.DrawImage(DM::GetUIImage("bagUI"), GetCursorRect(curSelectIdx[poketSelect]), cursor.X, cursor.Y, cursor.Width, cursor.Height, UnitPixel);
}

void BagMenu::DrawItemDesc(Graphics& g)
{
	int code = DM::GetPlayerData()->iData[poketSelect][curSelect[poketSelect]]->code;
	string descStr = DM::GetItemDesc(code)->desc;
	_tcscpy_s(buffer, CA2T(descStr.c_str()));
	g.DrawString(buffer, -1, FONT_BIG, descRect, LEFT_ALIGN, BLACK);
}

void BagMenu::Draw(Graphics& g)
{
	DrawBagUI(g);
	DrawBottomDialog(g);
	DrawBagTypeAndText(g);

	if (DM::GetPlayerData()->iData[poketSelect].size() > 0)
	{
		DrawItemList(g);
		DrawItemCursor(g);
		DrawItemDesc(g);
	}
}

void BagMenu::UpdatePoketSelect()
{
	// 좌우 가방 종류 선택
	if (GET_KEY_LEFT && poketSelect > 0)
	{
		SM::PlayEffect("bagOpen");
		--poketSelect;
	}
	else if (GET_KEY_RIGHT && poketSelect < 3)
	{
		SM::PlayEffect("bagOpen");
		++poketSelect;
	}
}

void BagMenu::UpdateItemSelect()
{
	if (GET_KEY_UP)
	{
		--curSelect[poketSelect];
		--curSelectIdx[poketSelect];
	}
	else if (GET_KEY_DOWN)
	{
		++curSelect[poketSelect];
		++curSelectIdx[poketSelect];
	}

	int size = int(DM::GetPlayerData()->iData[poketSelect].size());

	Clamp(curSelect[poketSelect], 0, size - 1);
	Clamp(curSelectIdx[poketSelect], 0, 4);
	Clamp(curSelectIdx[poketSelect], 0, size - 1);
}

void BagMenu::Update()
{
	UpdatePoketSelect();
	UpdateItemSelect();

	// 아이템 선택
	if (GET_KEY_Z && DM::GetPlayerData()->iData[poketSelect].size() > 0)
	{
		SM::PlayEffect("button");
		RM::SetTargetWithoutFade(GM::game.bagItemSelect);
	}

	// 가방 나가기
	if (GET_KEY_X)
	{
		SM::PlayEffect("button");
		RM::SetTargetWithoutFade(GM::game.mainMenu);
	}
}

void BagMenu::AdjustSelect()
{
	if (curSelect[poketSelect] >= DM::GetPlayerData()->iData[poketSelect].size())
	{
		--curSelect[poketSelect];

		if (curSelectIdx[poketSelect] > 0)
		{
			--curSelectIdx[poketSelect];
		}
		else
		{
			if (DM::GetPlayerData()->iData[poketSelect].size() > 0)
				curSelectIdx[poketSelect] = 4;
		}
	}
}

InventoryItemData* BagMenu::GetCurSelectInventoryItemData()
{
	if (DM::GetPlayerData()->iData[poketSelect].empty())
		return NULL;

	return DM::GetPlayerData()->iData[poketSelect][curSelect[poketSelect]];
}
