#include "BagItemSelect.h"
#include "BagMenu.h"
#include "UIManager.h"
#include "InputManager.h"
#include "RunManager.h"

BagItemSelect::BagItemSelect()
{ }

void BagItemSelect::Draw(Graphics & g)
{
	BagMenu* bagMenu = gm->bagMenu;
	
	bagMenu->DrawBagUI(g);
	bagMenu->DrawBottomDialog(g);
	bagMenu->DrawItemDesc(g);
	bagMenu->DrawItemList(g);
	bagMenu->DrawItemCursor(g);

	UIManager::DrawDialogUI_IDX(g, 0, 1, 3, 5);
}

void BagItemSelect::Update()
{
	if (InputManager::GetX())
		RunManager::SetTarget(gm->bagMenu);
}
