#include "DataLoadManager.h"

#include "framework.h"
#include "Converter.h"

#include <fstream>

using std::fstream;
using namespace Gdiplus;

DataLoadManager::DataLoad DataLoadManager::dataLoad = DataLoadManager::DataLoad();

TCHAR dataFile[128];
TCHAR imageFile[128], *token;

DataLoadManager::DataLoad::DataLoad()
{
	//Reset();
}

DataLoadManager::DataLoad::~DataLoad()
{
	/*delete collection;
	delete fm;
	delete fontS;
	delete fontM;
	delete fontB;*/

	/*for (auto &e : mapImages)
	{
		delete e.second;
	}*/

	for (auto &e : itemDescs)
		delete e.second;

	for (auto &e : pokemonDatas)
		delete e.second;

	for (auto &e : pokemonDescs)
		delete e.second;

	delete playerData;
}

void DataLoadManager::DataLoad::LoadMap()
{
	WIN32_FIND_DATA findData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	TCHAR fullPath[] = _T("data/map/mapData/*.*");

	hFind = FindFirstFile(fullPath, &findData);

	if (hFind == INVALID_HANDLE_VALUE)
		throw std::runtime_error("Invalid handle value! Please check your path...");

	while (FindNextFile(hFind, &findData))
	{
		if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			_stprintf_s(dataFile, _T("data/map/mapData/%s"), findData.cFileName);

			TCHAR *imageName = wcstok_s(findData.cFileName, _T("."), &token);
			_stprintf_s(imageFile, _T("data/map/mapPng/%s.png"), imageName);

			Json::Value root;
			std::ifstream readFile(dataFile);

			if (readFile.is_open())
			{
				Map newMap;

				readFile >> root;
				readFile.close();

				JsonToMap(newMap, root);

				mapDatas[newMap.ID] = newMap;

				Image* newImage = new Image(imageFile);
				mapImages[newMap.ID] = newImage;
			}
		}
	}
}

void DataLoadManager::DataLoad::LoadItemDesc()
{
	fstream openFile("data/table/item_desc.json");
	Json::Value root;

	if (openFile.is_open())
	{
		openFile >> root;
		openFile.close();

		for (int i = 0; i < root.size(); ++i)
		{
			Json::Value data = root[i];
			ItemDesc* newDesc = new ItemDesc;

			JsonToItemDesc(newDesc, data);

			itemDescs[newDesc->code] = newDesc;
		}
	}
}

void DataLoadManager::DataLoad::LoadTransData()
{
	fstream openFile("data/table/UI_text.json");
	Json::Value root;

	if (openFile.is_open())
	{
		openFile >> root;
		openFile.close();

		for (int i = 0; i < root.size(); ++i)
			transDatas[root[i]["key"].asString()] = root[i]["value"].asString();
	}
}

void DataLoadManager::DataLoad::LoadPokemonData()
{
	fstream openFile("data/table/pokemon_data.json");
	Json::Value root;

	if (openFile.is_open())
	{
		openFile >> root;
		openFile.close();

		for (int i = 0; i < root.size(); ++i)
		{
			Json::Value jsonData = root[i];
			PokemonData* newData = new PokemonData;

			JsonToPokemonData(newData, jsonData);
			pokemonDatas[newData->id] = newData;
		}
	}
}

void DataLoadManager::DataLoad::LoadPokemonDesc()
{
	fstream openFile("data/table/pokemon_desc.json");
	Json::Value root;

	if (openFile.is_open())
	{
		openFile >> root;
		openFile.close();

		for (int i = 0; i < root.size(); ++i)
		{
			Json::Value jsonData = root[i];
			PokemonDesc* newDesc = new PokemonDesc;

			JsonToPokemonDesc(newDesc, jsonData);
			pokemonDescs[newDesc->id] = newDesc;
		}
	}
}

void DataLoadManager::DataLoad::Init()
{
	LoadMap();
	LoadItemDesc();
	LoadTransData();

	LoadPokemonData();
	LoadPokemonDesc();

	playerData = new PlayerData;

	// others

	player_game = new Image(_T("data/sprite/player/player_game.png"));
	UI_Bag = new Image(_T("data/sprite/UI/UI_Bag.png"));
	UI_Dialog_Base = new Image(_T("data/sprite/UI/UI_Dialog_Base.png"));

	// test
	for (int i = 1; i <= 60; ++i)
		AddItemToInventory(i, rand() % 99 + 1);
}

void DataLoadManager::DataLoad::AddItemToInventory(int code, int count)
{
	ItemDesc* item = itemDescs[code];

	for (auto &e : playerData->iData[item->type])
	{
		if (e.code == code)
		{
			e.count += count;
			break;
		}
	}

	InventoryItemData newData(code, item->type, count);
	playerData->iData[item->type].push_back(newData);
}

void DataLoadManager::DataLoad::RemoveItemFromInventory(int code, int count)
{
	ItemDesc* item = itemDescs[code];
	vector<InventoryItemData> &v = playerData->iData[item->type];

	for (int i = 0; i < (int)v.size(); ++i)
	{
		if (v[i].code == code)
		{
			v[i].count -= count;

			if (v[i].count == 0)
				v.erase(v.begin() + i);

			break;
		}
	}
}

void DataLoadManager::Reset()
{
	dataLoad.Init();
}

Map* DataLoadManager::GetMapData(string ID)
{
	return &(dataLoad.mapDatas[ID]);
}

Image* DataLoadManager::GetMapImage(string ID)
{
	return dataLoad.mapImages[ID];
}

Image* DataLoadManager::GetPlayer_game()
{
	return dataLoad.player_game;
}
