#pragma once

#ifndef __UIMANAGER_H__
#define __UIMANAGER_H__

#include "framework.h"

using namespace Gdiplus;

class UIManager
{
private:

	class UI
	{
		friend UIManager;

	private:

		UI();
		~UI();

	private:

		void _Reset();

		void _DrawDialogUI_IDX(Graphics& g, int idxX, int idxY, int col, int row);

	};

private:

	static UI ui;

public:

	static void Reset();
	static void DrawDialogUI_IDX(Graphics& g, int idxX, int idxY, int col, int row);

};

#endif // !__UIMANAGER_H__
