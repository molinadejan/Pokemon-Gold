#pragma once
#ifndef __CONVERTER_HPP_
#define __CONVERTER_HPP_

#include <json/json.h>
#include "Datas.h"
#include <atlstr.h>
#include "framework.h"

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

void JsonToMovePoint(MovePoint &mp, Json::Value &value)
{
	mp.targetID = value["targetID"].asString();

	mp.pos.x = value["posX"].asInt();
	mp.pos.y = value["posY"].asInt();

	mp.targetPos.x = value["targetPosX"].asInt();
	mp.targetPos.y = value["targetPosY"].asInt();
}

void MovePointToJson(MovePoint &mp, Json::Value &value)
{
	value["targetID"] = mp.targetID;

	value["posX"] = mp.pos.x;
	value["posY"] = mp.pos.y;

	value["targetPosX"] = mp.targetPos.x;
	value["targetPosY"] = mp.targetPos.y;
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

	for (int i = 0; i < (int)saveTiles.size(); ++i)
	{
		Tile &tile = map.tiles[i / map.mapSize.x][i % map.mapSize.x];
		JsonToTile(tile, saveTiles[i]);
	}

	map.neighbors = vector<string>();

	Json::Value n = value["neighbors"];

	for (int i = 0; i < (int)n.size(); ++i)
		map.neighbors.push_back(n[i].asString());

	map.movePoints = vector<MovePoint>();

	Json::Value m = value["movePoints"];

	for (int i = 0; i < (int)m.size(); ++i)
	{
		MovePoint newMp;
		JsonToMovePoint(newMp, m[i]);
		map.movePoints.push_back(newMp);
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

	Json::Value n;

	for (int i = 0; i < (int)map.neighbors.size(); ++i)
		n.append(map.neighbors[i]);

	value["neighbors"] = n;

	Json::Value m;

	for (int i = 0; i < (int)map.movePoints.size(); ++i)
	{
		Json::Value mp;
		MovePointToJson(map.movePoints[i], mp);
		m.append(mp);
	}

	value["movePoints"] = m;
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
