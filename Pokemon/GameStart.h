#pragma once

#ifndef __GAMESTART_H__
#define __GAMESTART_H__

#include "BaseClass.h"
#include "CSound.h"

class GameStart : public BaseClass
{
private:

	RectF menuRects[2] = { RectF(R(MUL), R(0.6f * MUL), R(6 * MUL), R(MUL)), RectF(R(MUL), R(1.6f * MUL), R(6 * MUL), R(MUL)) };
	Rect cursorRects[2] = { Rect(0, INT(0.6f * MUL), MUL, MUL), Rect(0, INT(1.6f * MUL), MUL, MUL) };

private:

	Image* dialogImg;

	int curSelectMenu;
	bool isSaveFile;
	int menuCount;

public:

	GameStart() = default;

	void Init() override;
	void Update() override;
	void Draw(Graphics &g) override;
};

#endif // !__GAMESTART_H__
