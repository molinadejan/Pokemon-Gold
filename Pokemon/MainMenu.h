#pragma once

#ifndef __MAINMENU_H__
#define __MAINMENU_H__

#include "BaseClass.h"

class MainMenu : public BaseClass
{
public:
	enum MainMenuState
	{
		Main = 0,
		PokeDex = 1,
		Pokemon = 2,
		Bag = 3,
		Pokegear = 4,
		Player = 5,
		Report = 6,
		Option = 7,
		Exit = 8
	};


private:

	const int MENU_COUNT = 8;

	const TCHAR* MENU[8] = { _T("����"), _T("���ϸ�"), _T("����"), _T("���ϱ��"), _T("�÷��̾�"), _T("����Ʈ"), _T("����"), _T("�ݱ�") };
	const TCHAR* MENU_DESCREIPTION[8] = { _T("���ϸ��� �����\n��ϵǾ��� �ִ�"), _T("���� �ִ�\n���ϸ��� ����"), _T("������ ����ִ�\n���� ���ù賶"), _T("Ʈ���̳��� ���࿡\n������ �Ǵ� ��"), 
		_T("����\n����� ����"), _T("��� ���� ����\n���¸� ���"), _T("������ �� ����\n�������� ����"), _T("�� �޴��� �ݴ´�") };

	const int MENU_H = ((ROW - 2) * MUL) / MENU_COUNT;

private:

	int curSelect;
	MainMenuState state;

private:

	void DrawMain(Graphics &g);

public:

	MainMenu();
	~MainMenu() = default;

	void Draw(Graphics &g) override;
	void Update() override;
};

#endif // !__GAMEPLAYMAINMENU_H__

