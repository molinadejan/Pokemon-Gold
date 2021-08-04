#include "BagMenu.h"
#include "DataLoadManager.h"
#include "InputManager.h"
#include "UIManager.h"
#include "RunManager.h"

BagMenu::BagMenu() : curSelect(0) { }

void BagMenu::Draw(Graphics& g)
{
	Image* bag = DataLoadManager::GetUI_Bag();

	// 가방 UI
	Rect rect1(0, 0, SCREEN_SIZE_X, 6 * MUL);
	g.DrawImage(bag, rect1, 0, 0, 160, 96, UnitPixel);

	// 하단 UI 배경
	UIManager::DrawDialogUI_IDX(g, 0, ROW - 3, COL, 3);

	// 가방 종류

	TCHAR buffer[128];
	Font* font = DataLoadManager::GetFontB();
	SolidBrush brush(Color(255, 255, 255, 255));
	StringFormat format;

	format.SetAlignment(StringAlignmentCenter);
	format.SetLineAlignment(StringAlignmentCenter);

	RectF strRect(2 * SCREEN_MUL, 58 * SCREEN_MUL, 36 * SCREEN_MUL, 20 * SCREEN_MUL);
	Rect bagImageRect(0, 24 * SCREEN_MUL, 40 * SCREEN_MUL, 24 * SCREEN_MUL);
	int imagePosX = 0;

	switch (state)
	{
		case BagMenu::Item:
			_stprintf_s(buffer, _T("아이템"));
			imagePosX = 0;
			break;

		case BagMenu::Ball:
			_stprintf_s(buffer, _T("볼"));
			imagePosX = 1;
			break;

		case BagMenu::KeyItem:
			_stprintf_s(buffer, _T("중요한"));
			imagePosX = 2;
			break;

		case BagMenu::Machine:
			_stprintf_s(buffer, _T("기술머신"));
			imagePosX = 3;
			break;
	}

	g.DrawImage(bag, bagImageRect, imagePosX * 40, 96, 40, 24, UnitPixel);
	g.DrawString(buffer, -1, font, strRect, &format, &brush);
}

void BagMenu::Update()
{
	if (InputManager::GetKeyUp(VK_LEFT))
		--curSelect;
	else if (InputManager::GetKeyUp(VK_RIGHT))
		++curSelect;

	if (curSelect < 0) curSelect = 3;
	if (curSelect > 3) curSelect = 0;

	state = (BagState)curSelect;

	if (InputManager::GetX())
		RunManager::SetTarget(gm->mainMenu);
}
