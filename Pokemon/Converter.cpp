#include "Converter.h"

#include <atlstr.h>
#include "framework.h"
#include <json/json.h>
#include <utility>

void JsonToTile(Tile &tile, Json::Value &value)
{
	tile.pos.X = value["posX"].asInt();
	tile.pos.Y = value["posY"].asInt();

	tile.tilePos.X = value["tilePosX"].asInt();
	tile.tilePos.Y = value["tilePosY"].asInt();

	tile.moveable = value["moveable"].asInt();
	tile.interactID = value["interact ID"].asInt();

	tile.isPokemon = value["isPokemon"].asInt();
}

void TileToJson(Tile &tile, Json::Value &value)
{
	value["posX"] = tile.pos.X;
	value["posY"] = tile.pos.Y;

	value["tilePosX"] = tile.tilePos.X;
	value["tilePosY"] = tile.tilePos.Y;

	value["moveable"] = tile.moveable;
	value["interact ID"] = tile.interactID;

	value["isPokemon"] = tile.isPokemon;
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
	map.music = value["music"].asString();

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

	value["music"] = map.music;

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

void JsonToItemDesc(ItemDesc *itemDesc, Json::Value &value)
{
	itemDesc->code = value["code"].asInt();
	itemDesc->desc = value["desc"].asString();
	itemDesc->name = value["name"].asString();
	itemDesc->type = value["type"].asInt();
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

void JsonToPokemonData(PokemonData *pData, Json::Value &value)
{
	pData->id = value["id"].asInt();
	pData->type1 = value["type1"].asInt();
	pData->type2 = value["type2"].asInt();

	pData->evo_id = value["evo_id"].asInt();
	pData->height = value["height"].asInt();
	pData->weight = value["weight"].asFloat();

	pData->catch_rate = value["catch_rate"].asInt();
	pData->base_exp = value["base_exp"].asInt();
	pData->exp_growth_group = value["exp_growth_group"].asInt();

	pData->HP = value["HP"].asInt();
	pData->ATK = value["ATK"].asInt();
	pData->DEF = value["DEF"].asInt();
	pData->SPA = value["SPA"].asInt();
	pData->SPD = value["SPD"].asInt();
	pData->SPE = value["SPE"].asInt();

	Json::Value learnSkill = value["learn_skill"];

	for (int i = 0; i < int(learnSkill.size()); ++i)
	{
		std::pair<int, int> newData;
		newData.first = learnSkill[i]["level"].asInt();
		newData.second = learnSkill[i]["id"].asInt();

		pData->learn_skill.push_back(newData);
	}
}

void JsonToPokemonDesc(PokemonDesc *pDesc, Json::Value &value)
{
	pDesc->id = value["id"].asInt();
	pDesc->name = value["name"].asString();
	pDesc->cc = value["cc"].asString();
}

void JsonToSkillData(SkillData * sData, Json::Value & value)
{
	sData->id = value["id"].asInt();
	sData->type = value["type"].asInt();
	sData->cc = value["cc"].asInt();
	sData->power = value["power"].asInt();
	sData->ar = value["ar"].asFloat();
	sData->pp = value["pp"].asInt();
}

void JsonToSkillDesc(SkillDesc * sDesc, Json::Value & value)
{
	sDesc->id = value["id"].asInt();
	sDesc->name = value["name"].asString();
}

void JsonToAnimRect(vector<Rect>& rectVec, Json::Value& value)
{
	Json::Value e = value["rect"];

	for (int i = 0; i < (int)e.size(); ++i)
	{
		Rect newRect(e[i]["x"].asInt(), e[i]["y"].asInt(), e[i]["w"].asInt(), e[i]["h"].asInt());
		rectVec.push_back(newRect);
	}
}
