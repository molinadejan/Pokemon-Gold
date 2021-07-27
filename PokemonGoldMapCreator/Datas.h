#pragma once

#ifndef __DATAS_H__
#define __DATAS_H__

#include <string>
#include "framework.h"

using std::string;
using namespace Gdiplus;

struct Tile
{
	string tileset;
	POINT tilePos;

	// 0 : �̵� �Ұ���
	// 1 : �̵� ����
	// 2 ~ : �ش� ���ϸ� ����� ���� ��� �̵� ����
	int moveable;

	Tile() : tileset(""), tilePos{ -1, -1 }, moveable(false) { }
};

#endif // !__DATAS_H__

