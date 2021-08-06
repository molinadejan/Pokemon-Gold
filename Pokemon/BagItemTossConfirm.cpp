#include "BagItemTossConfirm.h"
#include "BagMenu.h"
#include "BagItemToss.h"
#include "BagItemSelect.h"
#include "InputManager.h"
#include "RunManager.h"
#include "Timer.h"
#include "UIManager.h"
#include "DataLoadManager.h"
#include "TransDatas.h"

BagItemTossConfirm::BagItemTossConfirm()
	: curState(TossConfirmState::Init), frameTimer(FRAME_LIMIT), dlgLen(1), confirmSelect(0)
{ }

void BagItemTossConfirm::ResourceInit()
{
	BaseClass::ResourceInit();
	bag = DataLoadManager::GetUI_Bag();
}

void BagItemTossConfirm::UpdateConfirm()
{
	frameTimer -= Timer::DeltaTime();

	if (frameTimer <= 0.0f)
	{
		++dlgLen;
		frameTimer = FRAME_LIMIT;

		int len = _tcsclen(tmpBuffer);
		_tcsncpy_s(buffer, tmpBuffer, dlgLen);

		if (dlgLen == len)
		{
			dlgLen = 1;
			curState = TossConfirmState::Confirm;
		}
	}
}

void BagItemTossConfirm::Reset()
{
	dlgLen = 1;
	memset(tmpBuffer, 0, sizeof(tmpBuffer));
	curState = TossConfirmState::Init;
	confirmSelect = 0;
	curItemData = NULL;
}

void BagItemTossConfirm::Draw(Graphics & g)
{
	BagMenu* bagMenu = gm->bagMenu;

	bagMenu->DrawBagUI(g);
	bagMenu->DrawBagTypeAndText(g);
	bagMenu->DrawItemList(g);
	bagMenu->DrawItemCursor(g);
	bagMenu->DrawBottomDialog(g);

	switch (curState)
	{
		case BagItemTossConfirm::Init:
		{
			memset(buffer, 0, sizeof(buffer));

			curItemData = gm->bagMenu->GetCurSelectInventoryItemData();

			string name = DataLoadManager::GetItemDesc(curItemData->code)->name;
			int count = gm->bagItemToss->GetTossCount();

			TransString(tmpBuffer, "bag_item_toss_confirm", 2, TokenChange("item_name", name), TokenChange("item_count", std::to_string(count)));
			curState = BagItemTossConfirm::OneMoreConfirm;
		}
		break;

		case BagItemTossConfirm::OneMoreConfirm:
		{
			g.DrawString(buffer, -1, DM::GetFontB(), descRect, leftAlign ,black);
		}
		break;

		case BagItemTossConfirm::Confirm:
		{
			g.DrawString(buffer, -1, DM::GetFontB(), descRect, leftAlign, black);
			UIManager::DrawDialogUI_IDX(g, 7, 3, 3, 3);

			for (int i = 0; i < 2; ++i)
			{
				RectF choiceRect(8 * MUL, (2.6f + i) * MUL, 3 * MUL, 3 * MUL);
				TransString(tmpBuffer, i == 0 ? "yes" : "no");
				g.DrawString(tmpBuffer, -1, DM::GetFontB(), choiceRect, leftAlign, black);
			}

			Rect cursorRect(7 * MUL, (2.6f + confirmSelect + 1) * MUL, MUL, MUL);
			g.DrawImage(bag, cursorRect, 10 * PIXEL, 1 * PIXEL, PIXEL, PIXEL, UnitPixel);
		}
		break;

		case BagItemTossConfirm::TossFinish:
		{
			string name = DataLoadManager::GetItemDesc(curItemData->code)->name;
			TransString(buffer, "bag_item_toss_finish", 1, TokenChange("item_name", name));
			g.DrawString(buffer, -1, DM::GetFontB(), descRect, leftAlign, black);
		}
		break;

		case BagItemTossConfirm::Pause:
		{
			g.DrawString(buffer, -1, DM::GetFontB(), descRect, leftAlign, black);
		}
		break;
	}
}

void BagItemTossConfirm::Update()
{
	switch (curState)
	{
		case BagItemTossConfirm::OneMoreConfirm:
		{
			UpdateConfirm();
		}
		break;

		case BagItemTossConfirm::Confirm:
		{
			if (InputManager::GetKeyUp(VK_UP) && confirmSelect == 1)
				confirmSelect = 0;
			else if (InputManager::GetKeyUp(VK_DOWN) && confirmSelect == 0)
				confirmSelect = 1;

			if (InputManager::GetKeyUp('Z') && confirmSelect == 0)
			{
				InventoryItemData* data = gm->bagMenu->GetCurSelectInventoryItemData();
				int code = data->code;

				DataLoadManager::RemoveItemFromInventory(code, gm->bagItemToss->GetTossCount());

				curState = TossFinish;
			}
			else if (InputManager::GetKeyUp('X') || InputManager::GetKeyUp('Z') && confirmSelect == 1)
			{
				gm->bagItemToss->SetTossCount(1);
				Reset();
				RunManager::SetTarget(gm->bagMenu);
			}
		}
		break;

		case BagItemTossConfirm::TossFinish:
		{
			if (InputManager::GetKeyUp('Z'))
			{
				gm->bagItemToss->SetTossCount(1);
				Reset();
				RunManager::SetTarget(gm->bagMenu);
			}
		}
		break;

		case BagItemTossConfirm::Pause:
		{
			if (InputManager::GetKeyUp('Z'))
				curState = BagItemTossConfirm::OneMoreConfirm;
		}
		break;
	}
}
