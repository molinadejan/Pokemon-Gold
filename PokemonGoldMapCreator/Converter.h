#pragma once
#ifndef __CONVERTER_HPP_
#define __CONVERTER_HPP_

#include "Datas.h"
#include <json/json.h>

void JsonToTile(Tile &tile, Json::Value &value);

void TileToJson(Tile &tile, Json::Value &value);

void JsonToMovePoint(MovePoint &mp, Json::Value &value);

void MovePointToJson(MovePoint &mp, Json::Value &value);

void JsonToMap(Map &map, Json::Value &value);

void MapToJson(Map &map, Json::Value &value);

//https://docs.microsoft.com/ko-kr/windows/win32/gdiplus/-gdiplus-retrieving-the-class-identifier-for-an-encoder-use?redirectedfrom=MSDN
int GetEncoderClsid(const WCHAR * format, CLSID * pClsid);

#endif // !__CONVERTER_HPP_
