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

	const TCHAR* CHOICE[4] = { _T("����ϴ�"), _T("���ϰ��ϴ�"), _T("������"), _T("�׸��δ�") };
	const float CHOICE_H = (5 * MUL) / 5.0f;

private:

	void DrawChoices(Graphics& g);

private:

	int curSelect;
	Image* dialog;

public:

	BagItemSelect();
	~BagItemSelect() = default;

	void ResourceInit() override;
	void Draw(Graphics& g) override;
	void Update() override;
};

#endif