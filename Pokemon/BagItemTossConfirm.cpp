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
#include "SoundManager.h"

void BagItemTossConfirm::Init()
{
	dialogShow = new DialogShow();

	curItemData = GM::game.bagMenu->GetCurSelectInventoryItemData();

	string itemName = DM::GetItemDesc(curItemData->code)->name;
	int count = GM::game.bagItemToss->GetTossCount();

	dialogShow->Reset();
	dialogShow->Push(TransString(NULL, "bag_item_toss_confirm", 2, TokenChange("item_name", itemName), TokenChange("item_count", std::to_string(count))));
	dialogShow->Start();
}

void BagItemTossConfirm::Reset()
{
	curItemData = NULL;

	memset(tmpBuffer, 0, sizeof(tmpBuffer));
	curState = OneMoreConfirm;
	confirmSelect = 0;

	delete dialogShow;
}

void BagItemTossConfirm::DrawConfirmUI(Graphics& g)
{
	UM::DrawDialogUI_IDX(g, 7, 3, 3, 3);

	for (int i = 0; i < 2; ++i)
	{
		RectF choiceRect(8 * MUL, (2.6f + i) * MUL, 3 * MUL, 3 * MUL);
		TransString(tmpBuffer, i == 0 ? "yes" : "no");
		g.DrawString(tmpBuffer, -1, FONT_BIG, choiceRect, LEFT_ALIGN, BLACK);
	}

	Rect cursorRect(7 * MUL, (INT)((3.5f + confirmSelect) * MUL), MUL, MUL);
	g.DrawImage(DM::GetUIImage("bagUI"), cursorRect, 10 * PIXEL, 1 * PIXEL, PIXEL, PIXEL, UnitPixel);
}

void BagItemTossConfirm::Draw(Graphics& g)
{
	BagMenu* bagMenu = GM::game.bagMenu;

	bagMenu->DrawBagUI(g);
	bagMenu->DrawBagTypeAndText(g);
	bagMenu->DrawItemList(g);
	bagMenu->DrawItemCursor(g);
	bagMenu->DrawBottomDialog(g);

	switch (curState)
	{
		case OneMoreConfirm:
		{
			dialogShow->Draw(g);

			if (!dialogShow->IsPlaying())
				DrawConfirmUI(g);
		}
		break;

		case TossFinish:
		{
			g.DrawString(buffer, -1, FONT_BIG, descRect, LEFT_ALIGN, BLACK);
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
			if(dialogShow->IsPlaying())
				dialogShow->Update();
			else
			{
				if (GET_KEY_UP && confirmSelect == 1)
					confirmSelect = 0;
				else if (GET_KEY_DOWN && confirmSelect == 0)
					confirmSelect = 1;

				if (GET_KEY_Z && confirmSelect == 0)
				{
					SM::PlayEffect("button");

					string name = DM::GetItemDesc(curItemData->code)->name;

					if (DM::RemoveItemFromInventory(curItemData->code, GM::game.bagItemToss->GetTossCount()))
						GM::game.bagMenu->AdjustSelect();
					
					TransString(buffer, "bag_item_toss_finish", 1, TokenChange("item_name", name));
					curState = TossFinish;
				}
				else if (GET_KEY_X || (GET_KEY_Z && confirmSelect == 1))
				{
					SM::PlayEffect("button");
					RM::SetTargetWithoutFade(GM::game.bagMenu);
				}
			}
		}
		break;

		case TossFinish:
		{
			if (GET_KEY_Z)
			{
				SM::PlayEffect("button");
				RM::SetTargetWithoutFade(GM::game.bagMenu);
			}
		}
		break;
	}
}
