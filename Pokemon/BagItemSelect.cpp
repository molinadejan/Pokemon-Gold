#include "BagItemSelect.h"
#include "BagMenu.h"
#include "UIManager.h"
#include "InputManager.h"
#include "RunManager.h"
#include "MyUtils.h"
#include "DataLoadManager.h"
#include "BagItemToss.h"
#include "TransDatas.h"

BagItemSelect::BagItemSelect()
	: curSelect(0) { }

void BagItemSelect::ResourceInit()
{
	BaseClass::ResourceInit();
	dialog = DataLoadManager::GetUI_Dialog_Base();
}

void BagItemSelect::DrawChoices(Graphics & g)
{
	UIManager::DrawDialogUI_IDX(g, 0, 1, 3, 5);

	for (int i = 0; i < 4; ++i)
	{
		TransString(buffer, "bag_item_choice_" + std::to_string(i));
		g.DrawString(buffer, -1, fontS, GetChoiceRect(i), leftAlign, black);
	}

	g.DrawImage(dialog, GetCursorRect(curSelect), 3 * PIXEL, 0, PIXEL, PIXEL, UnitPixel);
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
	if (InputManager::GetKeyUp(VK_UP) && curSelect > 0)
		--curSelect;
	else if (InputManager::GetKeyUp(VK_DOWN) && curSelect < 3)
		++curSelect;

	curState = (ChoiceState)curSelect;

	if (InputManager::GetKeyUp('X'))
	{
		curSelect = 0;
		RunManager::SetTarget(gm->bagMenu);
	}

	if (InputManager::GetKeyUp('Z'))
	{
		switch (curState)
		{
			case BagItemSelect::USE:
			{
				//curSelect = 0;
				//RunManager::SetTarget(gm->bagMenu);
			}
			break;

			case BagItemSelect::GIVE:
			{
				//curSelect = 0;
				//RunManager::SetTarget(gm->bagMenu);
			}
			break;

			case BagItemSelect::TOSS:
			{
				curSelect = 0;
				RunManager::SetTarget(gm->bagItemToss);
			}
			break;

			case BagItemSelect::QUIT:
			{
				curSelect = 0;
				RunManager::SetTarget(gm->bagMenu);
			}
			break;
		}
	}
}
