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
	: curState(TossConfirmState::Init), confirmSelect(0)
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
	bag = DM::GetUI_Bag();
}

void BagItemTossConfirm::Reset()
{
	memset(tmpBuffer, 0, sizeof(tmpBuffer));
	curState = TossConfirmState::Init;
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
		case BagItemTossConfirm::Init:
		{
			curItemData = *(gm->bagMenu->GetCurSelectInventoryItemData());

			string name = DM::GetItemDesc(curItemData.code)->name;
			int count = gm->bagItemToss->GetTossCount();

			string dialog = TransString(NULL, "bag_item_toss_confirm", 2, TokenChange("item_name", name), TokenChange("item_count", std::to_string(count)));
			
			vector<string> dialogs;
			dialogs.push_back(dialog);

			dialogShow->Init(dialogs, descRect);

			curState = BagItemTossConfirm::OneMoreConfirm;
		}
		break;

		case BagItemTossConfirm::OneMoreConfirm:
		{
			dialogShow->Draw(g);
		}
		break;

		case BagItemTossConfirm::Confirm:
		{
			dialogShow->Draw(g);

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
			string name = DM::GetItemDesc(curItemData.code)->name;
			TransString(buffer, "bag_item_toss_finish", 1, TokenChange("item_name", name));
			g.DrawString(buffer, -1, DM::GetFontB(), descRect, leftAlign, black);
		}
		break;

		case BagItemTossConfirm::Pause:
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
			int count = dialogShow->UpdateDlg();

			if (count == 0)
				curState = Confirm;
			else if(count > 0)
				curState = Pause;
		}
		break;

		case Confirm:
		{
			if (GET_UP && confirmSelect == 1)
				confirmSelect = 0;
			else if (GET_DOWN && confirmSelect == 0)
				confirmSelect = 1;

			if (GET_Z && confirmSelect == 0)
			{
				InventoryItemData* data = gm->bagMenu->GetCurSelectInventoryItemData();
				int code = data->code;

				DM::RemoveItemFromInventory(code, gm->bagItemToss->GetTossCount());

				curState = TossFinish;
			}
			else if (GET_X || GET_Z && confirmSelect == 1)
			{
				gm->bagItemToss->SetTossCount(1);
				Reset();
				RunManager::SetTarget(gm->bagMenu);
			}
		}
		break;

		case TossFinish:
		{
			if (GET_Z)
			{
				gm->bagItemToss->SetTossCount(1);
				Reset();
				RunManager::SetTarget(gm->bagMenu);
			}
		}
		break;

		case Pause:
		{
			if (GET_Z)
				curState = OneMoreConfirm;
		}
		break;
	}
}
