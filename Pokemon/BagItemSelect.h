#pragma once

#ifndef __BAGITEMSELECT_H__
#define __BAGITEMSELECT_H__

#include "BaseClass.h"

// �Ϲ� ��������, ������������
// �������� Ÿ���� ���������� ���� �����ִ� �޴��� �޶�� �Ѵ�.
// ���߿� �߰� �ʿ�

class BagItemSelect :public BaseClass
{
private:

	const float CHOICE_H = (5 * MUL) / 5.0f;

	RectF GetChoiceRect(int i) { return RectF(R(MUL), R(1.5f * MUL + CHOICE_H * i), R(2 * MUL), R(MUL)); }
	Rect  GetCursorRect(int i) { return Rect (0, INT(1.6f * MUL + CHOICE_H * curSelect), MUL, MUL); }

private:

	enum ChoiceState
	{
		USE,
		GIVE,
		TOSS,
		QUIT
	};

private:

	void DrawChoices(Graphics& g);

private:

	int curSelect;
	ChoiceState curState;
	Image* dialog;

public:

	BagItemSelect();
	~BagItemSelect() = default;

	void ResourceInit() override;
	void Draw(Graphics& g) override;
	void Update() override;
};

#endif