#include "UIManager.h"
#include "DataLoadManager.h"

UIManager::UI UIManager::ui = UIManager::UI();

UIManager::UI::UI() { }
UIManager::UI::~UI() { }

// UI

void UIManager::UI::_Reset()
{
}

void UIManager::UI::_DrawDialogUI_IDX(Graphics& g, int idxX, int idxY, int col, int row)
{
	SolidBrush brush(Color(248, 248, 248));
	Rect rect(idxX * MUL, idxY * MUL, col * MUL, row * MUL);

	g.FillRectangle(&brush, rect);

	Image* dialog = DataLoadManager::GetUI_Dialog_Base();
	
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

// UIManager

void UIManager::Reset()
{
	ui._Reset();
}

void UIManager::DrawDialogUI_IDX(Graphics & g, int idxX, int idxY, int col, int row)
{
	if (col < 2 || row < 2)
		return;

	ui._DrawDialogUI_IDX(g, idxX, idxY, col, row);
}
