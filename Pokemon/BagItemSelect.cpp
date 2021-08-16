#include "BagItemSelect.h"
#include "BagMenu.h"
#include "UIManager.h"
#include "InputManager.h"
#include "RunManager.h"
#include "MyUtils.h"
#include "DataLoadManager.h"
#include "BagItemToss.h"
#include "TransDatas.h"
#include "GdiplusElement.h"
#include "SoundManager.h"

BagItemSelect::BagItemSelect()
	: curSelect(0) { }

void BagItemSelect::DrawChoices(Graphics & g)
{
	UIManager::DrawDialogUI_IDX(g, 0, 1, 3, 5);

	for (int i = 0; i < 4; ++i)
	{
		TransString(buffer, "bag_item_choice_" + std::to_string(i));
		g.DrawString(buffer, -1, FONT_SMALL, GetChoiceRect(i), LEFT_ALIGN, BLACK);
	}

	g.DrawImage(DM::GetDialogBase(), GetCursorRect(curSelect), 3 * PIXEL, 0, PIXEL, PIXEL, UnitPixel);
}

void BagItemSelect::Draw(Graphics & g)
{
	BagMenu* bagMenu = gm->bagMenu;
	
	bagMenu->DrawBagUI(g);
	bagMenu->DrawBottomDialog(g);
	bagMenu->DrawItemDesc(g);
	bagMenu->DrawItemList(g);
	bagMenu->DrawItemCursor(g);

	DrawChoices(g);
}

void BagItemSelect::Update()
{
	if (GET_KEY_UP && curSelect > 0)
		--curSelect;
	else if (GET_KEY_DOWN && curSelect < 3)
		++curSelect;

	if (GET_KEY_X)
	{
		SM::PlayEffect("button");

		curSelect = 0;
		RunManager::SetTargetWithoutFade(gm->bagMenu);
	}

	if (GET_KEY_Z)
	{
		SM::PlayEffect("button");
		switch (curSelect)
		{
			case USE:
			{

			}
			break;

			case GIVE:
			{

			}
			break;

			case TOSS:
			{
				curSelect = 0;
				RunManager::SetTargetWithoutFade(gm->bagItemToss);
			}
			break;

			case QUIT:
			{
				curSelect = 0;
				RunManager::SetTargetWithoutFade(gm->bagMenu);
			}
			break;
		}
	}
}
