#include "BagItemSelect.h"
#include "BagMenu.h"
#include "UIManager.h"
#include "InputManager.h"
#include "RunManager.h"
#include "MyUtils.h"
#include "DataLoadManager.h"

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
		RectF choiceRect(MUL, 1.5f * MUL + CHOICE_H * i, 2 * MUL, MUL);
		g.DrawString(CHOICE[i], -1, fontS, choiceRect, leftAlign, black);
	}

	Rect cursorRect(0, (1.6f * MUL + CHOICE_H * curSelect), MUL, MUL);
	g.DrawImage(dialog, cursorRect, 3 * PIXEL, 0, PIXEL, PIXEL, UnitPixel);
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

	if (InputManager::GetX())
	{
		curSelect = 0;
		RunManager::SetTarget(gm->bagMenu);
	}
}
