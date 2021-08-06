#pragma once

#ifndef __BAGITEMTOSS_H__
#define __BAGITEMTOSS_H__

#include "BaseClass.h"

class BagItemToss : public BaseClass
{
private:

	const RectF descRect = { MUL, 6 * MUL, (COL - 2) * MUL, 3 * MUL };

private:

	int tossCount;
	Image* bag;

private:

	void DrawTossText(Graphics& g);
	void DrawTossCount(Graphics& g);

public:

	BagItemToss();
	~BagItemToss() = default;

	int GetTossCount() const { return tossCount; }
	void SetTossCount(int i) { tossCount = i; }

	void ResourceInit() override;
	void Draw(Graphics& g) override;
	void Update() override;
};

#endif
