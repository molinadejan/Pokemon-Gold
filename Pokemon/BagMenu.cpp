#include "BagMenu.h"
#include "DataLoadManager.h"
#include "InputManager.h"
#include "UIManager.h"
#include "RunManager.h"
#include "MyUtils.h"

// 나중에 아이템이 없어지고 나서 커서 변수들을 조정해주는 
// 기능 추가 필요로 할듯하다

void BagMenu::ResourceInit()
{
	BaseClass::ResourceInit();
	bag = DataLoadManager::GetUI_Bag();
}

RectF BagMenu::GetItemTextRectF(int i)
{
	return RectF(R(4 * MUL), R((i + 1) * MUL), R(4 * MUL), R(MUL));
}

Rect BagMenu::GetXRect(int i)
{
	return Rect(7 * MUL, (i + 1) * MUL, MUL, MUL);
}

RectF BagMenu::GetItemCountRectF(int i)
{
	return RectF(R(8 * MUL), R((i + 1) * MUL), R(2 * MUL), R(MUL));
}

Rect BagMenu::GetCursorRect(int i)
{
	return Rect(3 * MUL, (i + 1) * MUL, MUL, MUL);
}

BagMenu::BagMenu() : curBagSelect(0)
{ 
	curSelect[0] = curSelect[1] = curSelect[2] = curSelect[3] = 0;
	curSelectIdx[0] = curSelectIdx[1] = curSelectIdx[2] = curSelectIdx[3] = 0;
}

void BagMenu::Draw(Graphics& g)
{
	// 가방 UI
	g.DrawImage(bag, bagUIRect, bagUI.X, bagUI.Y, bagUI.Width, bagUI.Height, UnitPixel);

	// 하단 UI 배경
	UIManager::DrawDialogUI_IDX(g, 0, ROW - 3, COL, 3);

	// 가방 종류 이미지
	g.DrawImage(bag, bagTypeImageRect, curBagSelect * bagTypeImage.X, bagTypeImage.Y, bagTypeImage.Width, bagTypeImage.Height, UnitPixel);

	// 가방 종류 텍스트
	_stprintf_s(buffer, ITEM_TYPE[curBagSelect]);
	g.DrawString(buffer, -1, fontB, bagTypeTextRect, centerAlign, white);

	// 아이템 리스트 
	PlayerData* pData = DataLoadManager::GetPlayerData();
	int size = pData->iData[curBagSelect].size();

	if (size == 0) 
		return;

	int curS = curSelect[curBagSelect];
	int curSI = curSelectIdx[curBagSelect];

	for (int i = 0; i < 5; ++i)
	{
		// 아이템 이름 출력
		int itemIdx = curS + i - curSI;

		if (itemIdx > size - 1)
			break;

		int code = pData->iData[curBagSelect][itemIdx].code;
		int count = pData->iData[curBagSelect][itemIdx].count;

		// 아이템 이름
		string itemName = DataLoadManager::GetItemDesc(code)->name;
		_tcscpy_s(buffer, CA2T(itemName.c_str()));
		g.DrawString(buffer, -1, fontB, GetItemTextRectF(i), leftAlign, black);

		// X 출력
		g.DrawImage(bag, GetXRect(i), X.X, X.Y, X.Width, X.Height, UnitPixel);

		// 개수 출력
		_stprintf_s(buffer, _T("%d"), count);
		g.DrawString(buffer, -1, fontB, GetItemCountRectF(i), rightAlign, black);
	}

	// 아이템 커서
	g.DrawImage(bag, GetCursorRect(curSI), cursor.X, cursor.Y, cursor.Width, cursor.Height, UnitPixel);

	int code = pData->iData[curBagSelect][curS].code;

	// 아이템 설명
	string descStr = DataLoadManager::GetItemDesc(code)->desc;
	_tcscpy_s(buffer, CA2T(descStr.c_str()));
	g.DrawString(buffer, -1, fontB, descRect, leftAlign, black);
}

void BagMenu::Update()
{
	// 좌우 가방 종류 선택
	if (InputManager::GetKeyUp(VK_LEFT) && curBagSelect > 0)
		--curBagSelect;
	else if (InputManager::GetKeyUp(VK_RIGHT) && curBagSelect < 3)
		++curBagSelect;

	state = (BagState)curBagSelect;

	// 상하 아이템 선택
	PlayerData* data = DataLoadManager::GetPlayerData();

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

	int size = data->iData[curBagSelect].size();

	Clamp(curSelect[curBagSelect], 0, size - 1);
	Clamp(curSelectIdx[curBagSelect], 0, 4);
	Clamp(curSelectIdx[curBagSelect], 0, size -1);

	// 가방 나가기
	if (InputManager::GetX())
		RunManager::SetTarget(gm->mainMenu);
}
