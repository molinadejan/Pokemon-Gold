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

	// 0 : 이동 불가능
	// 1 : 이동 가능
	// 2 ~ : 해당 포켓몬 기술이 있을 경우 이동 가능
	int moveable;

	Tile() : tileset(""), tilePos{ -1, -1 }, moveable(false) { }
};

#endif // !__DATAS_H__

