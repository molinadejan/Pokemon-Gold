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
#include "GdiplusElement.h"

BagItemTossConfirm::BagItemTossConfirm()
	: curState(Init), confirmSelect(0)
{ 
	dialogShow = new DialogShow;
}

BagItemTossConfirm::~BagItemTossConfirm()
{
	delete dialogShow;
}

void BagItemTossConfirm::ResourceInit()
{
	BaseClass::ResourceInit();
	bag = DM::GetBagUI();
}

void BagItemTossConfirm::Reset()
{
	memset(tmpBuffer, 0, sizeof(tmpBuffer));
	curState = Init;
	confirmSelect = 0;
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
		case Init:
		{
			curItemData = *(gm->bagMenu->GetCurSelectInventoryItemData());

			string name = DM::GetItemDesc(curItemData.code)->name;
			int count = gm->bagItemToss->GetTossCount();

			string dialog = TransString(NULL, "bag_item_toss_confirm", 2, TokenChange("item_name", name), TokenChange("item_count", std::to_string(count)));
			dialogShow->Push(dialog);
			dialogShow->Reset();

			curState = OneMoreConfirm;
		}
		break;

		case OneMoreConfirm:
		{
			dialogShow->Draw(g);
		}
		break;

		case Confirm:
		{
			dialogShow->Draw(g);

			UIManager::DrawDialogUI_IDX(g, 7, 3, 3, 3);

			for (int i = 0; i < 2; ++i)
			{
				RectF choiceRect(8 * MUL, (2.6f + i) * MUL, 3 * MUL, 3 * MUL);
				TransString(tmpBuffer, i == 0 ? "yes" : "no");
				g.DrawString(tmpBuffer, -1, FONT_BIG, choiceRect, LEFT_ALIGN, BLACK);
			}

			Rect cursorRect(7 * MUL, (INT)(2.6f + confirmSelect + 1) * MUL, MUL, MUL);
			g.DrawImage(bag, cursorRect, 10 * PIXEL, 1 * PIXEL, PIXEL, PIXEL, UnitPixel);
		}
		break;

		case TossFinish:
		{
			string name = DM::GetItemDesc(curItemData.code)->name;
			TransString(buffer, "bag_item_toss_finish", 1, TokenChange("item_name", name));
			g.DrawString(buffer, -1, FONT_BIG, descRect, LEFT_ALIGN, BLACK);
		}
		break;

		case Pause:
		{
			dialogShow->Draw(g);
		}
		break;
	}
}

void BagItemTossConfirm::Update()
{
	switch (curState)
	{
		case OneMoreConfirm:
		{
			dialogShow->Update();

			/*if (count == 0)
				curState = Confirm;
			else if(count > 0)
				curState = Pause;*/
		}
		break;

		case Confirm:
		{
			if (GET_KEY_UP && confirmSelect == 1)
				confirmSelect = 0;
			else if (GET_KEY_DOWN && confirmSelect == 0)
				confirmSelect = 1;

			if (GET_KEY_Z && confirmSelect == 0)
			{
				InventoryItemData* data = gm->bagMenu->GetCurSelectInventoryItemData();
				int code = data->code;

				DM::RemoveItemFromInventory(code, gm->bagItemToss->GetTossCount());

				curState = TossFinish;
			}
			else if (GET_KEY_X || GET_KEY_Z && confirmSelect == 1)
			{
				gm->bagItemToss->SetTossCount(1);
				Reset();
				RunManager::SetTarget(gm->bagMenu);
			}
		}
		break;

		case TossFinish:
		{
			if (GET_KEY_Z)
			{
				gm->bagItemToss->SetTossCount(1);
				Reset();
				RunManager::SetTarget(gm->bagMenu);
			}
		}
		break;

		case Pause:
		{
			if (GET_KEY_Z)
				curState = OneMoreConfirm;
		}
		break;
	}
}
