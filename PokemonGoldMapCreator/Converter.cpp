#include "Converter.h"

#include <atlstr.h>
#include "framework.h"
#include <json/json.h>

void JsonToTile(Tile &tile, Json::Value &value)
{
	tile.pos.X = value["posX"].asInt();
	tile.pos.Y = value["posY"].asInt();

	tile.tilePos.X = value["tilePosX"].asInt();
	tile.tilePos.Y = value["tilePosY"].asInt();

	tile.moveable = value["moveable"].asInt();
	tile.interactID = value["interact ID"].asInt();
}

void TileToJson(Tile &tile, Json::Value &value)
{
	value["posX"] = tile.pos.X;
	value["posY"] = tile.pos.Y;

	value["tilePosX"] = tile.tilePos.X;
	value["tilePosY"] = tile.tilePos.Y;

	value["moveable"] = tile.moveable;
	value["interact ID"] = tile.interactID;
}

void JsonToMovePoint(MovePoint &mp, Json::Value &value)
{
	mp.targetID = value["targetID"].asString();

	mp.pos.X = value["posX"].asInt();
	mp.pos.Y = value["posY"].asInt();

	mp.targetPos.X = value["targetPosX"].asInt();
	mp.targetPos.Y = value["targetPosY"].asInt();

	mp.moveType = value["moveType"].asInt();
}

void MovePointToJson(MovePoint &mp, Json::Value &value)
{
	value["targetID"] = mp.targetID;

	value["posX"] = mp.pos.X;
	value["posY"] = mp.pos.Y;

	value["targetPosX"] = mp.targetPos.X;
	value["targetPosY"] = mp.targetPos.Y;

	value["moveType"] = mp.moveType;
}

void JsonToMap(Map &map, Json::Value &value)
{
	map.ID = value["ID"].asString();

	map.worldPos.X = value["worldPosX"].asInt();
	map.worldPos.Y = value["worldPosY"].asInt();

	map.mapSize.X = value["mapSizeX"].asInt();
	map.mapSize.Y = value["mapSizeY"].asInt();

	map.tiles = vector<vector<Tile>>(map.mapSize.Y, vector<Tile>(map.mapSize.X, Tile()));

	Json::Value saveTiles = value["tiles"];

	for (int i = 0; i < (int)saveTiles.size(); ++i)
	{
		Tile &tile = map.tiles[i / map.mapSize.X][i % map.mapSize.X];
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

	value["worldPosX"] = map.worldPos.X;
	value["worldPosY"] = map.worldPos.Y;

	value["mapSizeX"] = map.mapSize.X;
	value["mapSizeY"] = map.mapSize.Y;

	Json::Value saveTiles;

	for (int i = 0; i < map.mapSize.Y; ++i)
	{
		for (int j = 0; j < map.mapSize.X; ++j)
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