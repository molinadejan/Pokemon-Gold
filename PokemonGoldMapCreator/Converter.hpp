#pragma once
#ifndef __CONVERTER_HPP_
#define __CONVERTER_HPP_

#include <json/json.h>
#include "Datas.h"

void JsonToTile(Tile &tile, Json::Value &value)
{
	tile.pos.x = value["posX"].asInt();
	tile.pos.y = value["posY"].asInt();

	tile.tilePos.x = value["tilePosX"].asInt();
	tile.tilePos.y = value["tilePosY"].asInt();

	tile.moveable = value["moveable"].asInt();
	tile.interactID = value["interact ID"].asInt();
}

void TileToJson(Tile &tile, Json::Value &value)
{
	value["posX"] = tile.pos.x;
	value["posY"] = tile.pos.y;

	value["tilePosX"] = tile.tilePos.x;
	value["tilePosY"] = tile.tilePos.y;

	value["moveable"] = tile.moveable;
	value["interact ID"] = tile.interactID;
}

void JsonToMap(Map &map, Json::Value &value)
{
	map.ID = value["ID"].asString();

	map.worldPos.x = value["worldPosX"].asInt();
	map.worldPos.y = value["worldPosY"].asInt();

	map.mapSize.x = value["mapSizeX"].asInt();
	map.mapSize.y = value["mapSizeY"].asInt();

	map.tiles = vector<vector<Tile>>(map.mapSize.y, vector<Tile>(map.mapSize.x, Tile()));

	Json::Value saveTiles = value["tiles"];

	for (int i = 0; i < saveTiles.size(); ++i)
	{
		Tile &tile = map.tiles[i / map.mapSize.x][i % map.mapSize.x];
		JsonToTile(tile, saveTiles[i]);
	}
}

void MapToJson(Map &map, Json::Value &value)
{
	value["ID"] = map.ID;

	value["worldPosX"] = map.worldPos.x;
	value["worldPosY"] = map.worldPos.y;

	value["mapSizeX"] = map.mapSize.x;
	value["mapSizeY"] = map.mapSize.y;

	Json::Value saveTiles;

	for (int i = 0; i < map.mapSize.y; ++i)
	{
		for (int j = 0; j < map.mapSize.x; ++j)
		{
			Json::Value tileJson;
			TileToJson(map.tiles[i][j], tileJson);
			saveTiles.append(tileJson);
		}
	}

	value["tiles"] = saveTiles;
}

//https://docs.microsoft.com/ko-kr/windows/win32/gdiplus/-gdiplus-retrieving-the-class-identifier-for-an-encoder-use?redirectedfrom=MSDN
int GetEncoderClsid(const WCHAR * format, CLSID * pClsid)
{
	UINT num = 0;
	UINT size = 0;

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if (size == 0)
		return -1;

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if (pImageCodecInfo == NULL)
		return -1;

	GetImageEncoders(num, size, pImageCodecInfo);

	for (UINT j = 0; j < num; ++j)
	{
		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;
		}
	}

	free(pImageCodecInfo);
	return -1;
}


#endif // !__CONVERTER_HPP_
