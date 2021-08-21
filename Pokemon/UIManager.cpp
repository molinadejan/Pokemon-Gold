#include "UIManager.h"
#include "DataLoadManager.h"

UIManager::UI UIManager::ui = UIManager::UI();

void UIManager::UI::Reset()
{

}

void UIManager::UI::Init()
{

}

void UIManager::UI::_DrawDialogUI_IDX(Graphics& g, int idxX, int idxY, int col, int row)
{
	SolidBrush brush(Color(248, 248, 248));
	Rect rect(idxX * MUL, idxY * MUL, col * MUL, row * MUL);

	g.FillRectangle(&brush, rect);

	Image* dialog = DataLoadManager::DM::GetUIImage("dialogBase");
	
	Rect LT(idxX * MUL, idxY * MUL, MUL, MUL);
	g.DrawImage(dialog, LT, 0, 0, PIXEL, PIXEL, UnitPixel);

	Rect LB(idxX * MUL, (idxY + row - 1) * MUL, MUL, MUL);
	g.DrawImage(dialog, LB, 0, 2 * PIXEL, PIXEL, PIXEL, UnitPixel);

	Rect RT((idxX + col - 1) * MUL, idxY * MUL, MUL, MUL);
	g.DrawImage(dialog, RT, 2 * PIXEL, 0, PIXEL, PIXEL, UnitPixel);

	Rect RB((idxX + col - 1) * MUL, (idxY + row - 1) * MUL, MUL, MUL);
	g.DrawImage(dialog, RB, 2 * PIXEL, 2 * PIXEL, PIXEL, PIXEL, UnitPixel);

	if (col > 2)
	{
		Rect T((idxX + 1) * MUL, idxY * MUL, (col - 2) * MUL, MUL);
		g.DrawImage(dialog, T, PIXEL, 0, PIXEL, PIXEL, UnitPixel);

		Rect B((idxX + 1) * MUL, (idxY + row - 1) * MUL, (col - 2) * MUL, MUL);
		g.DrawImage(dialog, B, PIXEL, 2 * PIXEL, PIXEL, PIXEL, UnitPixel);
	}

	if (row > 2)
	{
		Rect L(idxX * MUL, (idxY + 1) * MUL, MUL, (row - 2) * MUL);
		g.DrawImage(dialog, L, 0, PIXEL, PIXEL, PIXEL, UnitPixel);

		Rect R((idxX + col - 1) * MUL, (idxY + 1) * MUL, MUL, (row - 2) * MUL);
		g.DrawImage(dialog, R, 2 * PIXEL, PIXEL, PIXEL, PIXEL, UnitPixel);
	}
}

void UIManager::UI::_DrawDialogUI_IDX(Graphics & g, float idxX, float idxY, float col, float row)
{
	SolidBrush brush(Color(248, 248, 248));
	Rect rect(INT(idxX * MUL), INT(idxY * MUL), INT(col * MUL), INT(row * MUL));

	g.FillRectangle(&brush, rect);

	Image* dialog = DataLoadManager::DM::GetUIImage("dialogBase");

	Rect LT(INT(idxX * MUL), INT(idxY * MUL), MUL, MUL);
	g.DrawImage(dialog, LT, 0, 0, PIXEL, PIXEL, UnitPixel);

	Rect LB(INT(idxX * MUL), (idxY + row - 1) * MUL, MUL, MUL);
	g.DrawImage(dialog, LB, 0, 2 * PIXEL, PIXEL, PIXEL, UnitPixel);

	Rect RT(INT((idxX + col - 1) * MUL), INT(idxY * MUL), MUL, MUL);
	g.DrawImage(dialog, RT, 2 * PIXEL, 0, PIXEL, PIXEL, UnitPixel);

	Rect RB(INT((idxX + col - 1) * MUL), INT((idxY + row - 1) * MUL), MUL, MUL);
	g.DrawImage(dialog, RB, 2 * PIXEL, 2 * PIXEL, PIXEL, PIXEL, UnitPixel);

	if (col > 2)
	{
		Rect T(INT((idxX + 1) * MUL), INT(idxY * MUL), INT((col - 2) * MUL), MUL);
		g.DrawImage(dialog, T, PIXEL, 0, PIXEL, PIXEL, UnitPixel);

		Rect B(INT((idxX + 1) * MUL), INT((idxY + row - 1) * MUL), INT((col - 2) * MUL), MUL);
		g.DrawImage(dialog, B, PIXEL, 2 * PIXEL, PIXEL, PIXEL, UnitPixel);
	}

	if (row > 2)
	{
		Rect L(INT(idxX * MUL), INT((idxY + 1) * MUL), MUL, INT((row - 2) * MUL));
		g.DrawImage(dialog, L, 0, PIXEL, PIXEL, PIXEL, UnitPixel);

		Rect R(INT((idxX + col - 1) * MUL), INT((idxY + 1) * MUL), MUL, INT((row - 2) * MUL));
		g.DrawImage(dialog, R, 2 * PIXEL, PIXEL, PIXEL, PIXEL, UnitPixel);
	}
}

void UIManager::Reset()
{
	ui.Reset();
}

void UIManager::Init()
{
	ui.Init();
}

void UIManager::DrawDialogUI_IDX(Graphics & g, int idxX, int idxY, int col, int row)
{
	if (col < 2 || row < 2)
		return;

	ui._DrawDialogUI_IDX(g, idxX, idxY, col, row);
}

void UIManager::DrawDialogUI_IDX(Graphics & g, float idxX, float idxY, float col, float row)
{
	if (col < 2 || row < 2)
		return;

	ui._DrawDialogUI_IDX(g, idxX, idxY, col, row);
}