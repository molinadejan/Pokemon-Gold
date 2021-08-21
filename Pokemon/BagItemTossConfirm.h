#pragma once

#ifndef __BAGITEMTOSSCONFIRM_H__
#define __BAGITEMTOSSCONFIRM_H__

#include "BaseClass.h"
#include "DialogShow.h"
#include <vector>

using std::vector;

class BagItemTossConfirm : public BaseClass
{
private:

	enum TossConfirmState
	{
		OneMoreConfirm,
		TossFinish,
	};

private:

	const RectF descRect = { MUL, 6 * MUL, (COL - 2) * MUL, 3 * MUL };

private:

	DialogShow* dialogShow;

	int confirmSelect;

	TCHAR tmpBuffer[256];
	TossConfirmState curState;
	InventoryItemData* curItemData;

private:

	void DrawConfirmUI(Graphics& g);

public:

	BagItemTossConfirm() = default;
	~BagItemTossConfirm() = default;

	void Init() override;
	void Reset() override;
	void Draw(Graphics& g) override;
	void Update() override;
};

#endif // !__BAGITEMTOSSCONFIRM_H__
