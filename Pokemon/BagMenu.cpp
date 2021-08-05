#include "BagMenu.h"
#include "DataLoadManager.h"
#include "InputManager.h"
#include "UIManager.h"
#include "RunManager.h"
#include "MyUtils.h"
#include "BagItemSelect.h"

// ���߿� �������� �������� ���� Ŀ�� �������� �������ִ� 
// ��� �߰� �ʿ�� �ҵ��ϴ�

BagMenu::BagMenu() : curBagSelect(0)
{
	curSelect[0] = curSelect[1] = curSelect[2] = curSelect[3] = 0;
	curSelectIdx[0] = curSelectIdx[1] = curSelectIdx[2] = curSelectIdx[3] = 0;
}

void BagMenu::ResourceInit()
{
	BaseClass::ResourceInit();
	bag = DataLoadManager::GetUI_Bag();
	pData = DataLoadManager::GetPlayerData();
}

void BagMenu::DrawBagUI(Graphics & g)
{
	g.DrawImage(bag, bagUIRect, bagUI.X, bagUI.Y, bagUI.Width, bagUI.Height, UnitPixel);
}

void BagMenu::DrawBottomDialog(Graphics & g)
{
	UIManager::DrawDialogUI_IDX(g, 0, ROW - 3, COL, 3);
}

void BagMenu::DrawBagTypeAndText(Graphics & g)
{
	g.DrawImage(bag, bagTypeImageRect, curBagSelect * bagTypeImage.X, bagTypeImage.Y, bagTypeImage.Width, bagTypeImage.Height, UnitPixel);

	_stprintf_s(buffer, ITEM_TYPE[curBagSelect]);
	g.DrawString(buffer, -1, fontB, bagTypeTextRect, centerAlign, white);
}

void BagMenu::DrawItemList(Graphics & g)
{
	int size = pData->iData[curBagSelect].size();
	int curS = curSelect[curBagSelect];
	int curSI = curSelectIdx[curBagSelect];

	for (int i = 0; i < 5; ++i)
	{
		int itemIdx = curS + i - curSI;

		if (itemIdx > size - 1)
			break;

		int code = pData->iData[curBagSelect][itemIdx].code;
		int count = pData->iData[curBagSelect][itemIdx].count;

		// ������ �̸�
		string itemName = DataLoadManager::GetItemDesc(code)->name;
		_tcscpy_s(buffer, CA2T(itemName.c_str()));
		g.DrawString(buffer, -1, fontB, GetItemTextRectF(i), leftAlign, black);

		// X ���
		g.DrawImage(bag, GetXRect(i), X.X, X.Y, X.Width, X.Height, UnitPixel);

		// ���� ���
		_stprintf_s(buffer, _T("%d"), count);
		g.DrawString(buffer, -1, fontB, GetItemCountRectF(i), rightAlign, black);
	}
}

void BagMenu::DrawItemCursor(Graphics & g)
{
	g.DrawImage(bag, GetCursorRect(curSelectIdx[curBagSelect]), cursor.X, cursor.Y, cursor.Width, cursor.Height, UnitPixel);
}

void BagMenu::DrawItemDesc(Graphics & g)
{
	int code = pData->iData[curBagSelect][curSelect[curBagSelect]].code;
	string descStr = DataLoadManager::GetItemDesc(code)->desc;
	_tcscpy_s(buffer, CA2T(descStr.c_str()));
	g.DrawString(buffer, -1, fontB, descRect, leftAlign, black);
}

void BagMenu::Draw(Graphics& g)
{
	DrawBagUI(g);
	DrawBottomDialog(g);
	DrawBagTypeAndText(g);

	if (pData->iData[curBagSelect].size() > 0)
	{
		DrawItemList(g);
		DrawItemCursor(g);
		DrawItemDesc(g);
	}
}

void BagMenu::UpdateBagSelect()
{
	// �¿� ���� ���� ����
	if (InputManager::GetKeyUp(VK_LEFT) && curBagSelect > 0)
		--curBagSelect;
	else if (InputManager::GetKeyUp(VK_RIGHT) && curBagSelect < 3)
		++curBagSelect;

	//state = (BagState)curBagSelect;
}

void BagMenu::UpdateItemSelect()
{
	if (InputManager::GetKeyUp(VK_UP))
	{
		--curSelect[curBagSelect];
		--curSelectIdx[curBagSelect];
	}
	else if (InputManager::GetKeyUp(VK_DOWN))
	{
		++curSelect[curBagSelect];
		++curSelectIdx[curBagSelect];
	}

	int size = pData->iData[curBagSelect].size();

	Clamp(curSelect[curBagSelect], 0, size - 1);
	Clamp(curSelectIdx[curBagSelect], 0, 4);
	Clamp(curSelectIdx[curBagSelect], 0, size - 1);
}

void BagMenu::Update()
{
	UpdateBagSelect();
	UpdateItemSelect();

	// ������ ����
	if (InputManager::GetKeyUp('Z') && pData->iData[curBagSelect].size() > 0)
		RunManager::SetTarget(gm->bagItemSelect);

	// ���� ������
	if (InputManager::GetX())
		RunManager::SetTarget(gm->mainMenu);
}
