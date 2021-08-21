#include "DataLoadManager.h"

#include "framework.h"
#include "Converter.h"

#include <fstream>

using std::fstream;
using namespace Gdiplus;

DataLoadManager::DataLoad DataLoadManager::dataLoad = DataLoadManager::DataLoad();

TCHAR dataFile[128];
TCHAR imageFile[128], *token;

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
				Map* newMap = new Map();;

				readFile >> root;
				readFile.close();

				JsonToMap(newMap, root);

				mapDatas[newMap->ID] = newMap;

				Image* newImage = new Image(imageFile);
				mapImages[newMap->ID] = newImage;
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

		for (int i = 0; i < (int)root.size(); ++i)
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

		for (int i = 0; i < (int)root.size(); ++i)
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

		for (int i = 0; i < (int)root.size(); ++i)
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

		for (int i = 0; i < (int)root.size(); ++i)
		{
			Json::Value jsonData = root[i];
			PokemonDesc* newDesc = new PokemonDesc;

			JsonToPokemonDesc(newDesc, jsonData);
			pokemonDescs[newDesc->id] = newDesc;
		}
	}
}

void DataLoadManager::DataLoad::LoadSkillData()
{
	fstream openFile("data/table/skill_data.json");
	Json::Value root;

	if (openFile.is_open())
	{
		openFile >> root;
		openFile.close();

		for (int i = 0; i < (int)root.size(); ++i)
		{
			Json::Value jsonData = root[i];
			SkillData* newData = new SkillData;

			JsonToSkillData(newData, jsonData);
			skillDatas[newData->id] = newData;
		}
	}
}

void DataLoadManager::DataLoad::LoadSkillDesc()
{
	fstream openFile("data/table/skill_desc.json");
	Json::Value root;

	if (openFile.is_open())
	{
		openFile >> root;
		openFile.close();

		for (int i = 0; i < (int)root.size(); ++i)
		{
			Json::Value jsonData = root[i];
			SkillDesc* newData = new SkillDesc;

			JsonToSkillDesc(newData, jsonData);
			skillDescs[newData->id] = newData;
		}
	}
}

void DataLoadManager::DataLoad::LoadAnimRect()
{
	fstream openFile("data/table/anim_rect.json");
	Json::Value root;

	if (openFile.is_open())
	{
		openFile >> root;
		openFile.close();

		for (int i = 0; i < (int)root.size(); ++i)
		{
			Json::Value jsonData = root[i];
			vector<Rect>* rectVec = new vector<Rect>;

			JsonToAnimRect(rectVec, jsonData);
			animRects[jsonData["name"].asString()] = rectVec;
		}
	}
}

void DataLoadManager::DataLoad::LoadUIImage()
{
	WIN32_FIND_DATA findData;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	TCHAR fullPath[] = _T("data/sprite/UI/*.*");
	TCHAR imageFilePath[256], *token;
	char imageFileName[256];

	hFind = FindFirstFile(fullPath, &findData);

	if (hFind == INVALID_HANDLE_VALUE)
		throw std::runtime_error("Invalid handle value! Please check your path...");

	while (FindNextFile(hFind, &findData))
	{
		if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
		{
			TCHAR *imageName = wcstok_s(findData.cFileName, _T("."), &token);
			_stprintf_s(imageFilePath, _T("data/sprite/UI/%s.png"), imageName);

			WideCharToMultiByte(CP_ACP, 0, findData.cFileName, 256, imageFileName, 256, NULL, NULL);

			std::string nameStr(imageFileName);

			Image* image = new Image(imageFilePath);
			uiImages[nameStr] = image;
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

	LoadSkillData();
	LoadSkillDesc();

	LoadAnimRect();
	LoadUIImage();

	playerInGame = new Image(_T("data/sprite/player/playerInGame.png"));
}

void DataLoadManager::DataLoad::Reset()
{
	for (auto &e : mapImages)
		delete e.second;

	for (auto &e : itemDescs)
		delete e.second;

	for (auto &e : pokemonDatas)
		delete e.second;

	for (auto &e : pokemonDescs)
		delete e.second;

	for (auto &e : skillDatas)
		delete e.second;

	for (auto &e : skillDescs)
		delete e.second;

	for (auto &e : mapDatas)
		delete e.second;

	for (auto &e : animRects)
		delete e.second;

	for (auto &e : uiImages)
		delete e.second;

	delete playerInGame;
	delete playerData;
}

void DataLoadManager::DataLoad::AddItemToInventory(int code, int count)
{
	ItemDesc* item = itemDescs[code];

	for (auto &e : playerData->iData[item->type])
	{
		if (e->code == code)
		{
			e->count += count;
			break;
		}
	}

	InventoryItemData* newData = new InventoryItemData(code, item->type, count);

	playerData->iData[item->type].push_back(newData);
}

bool DataLoadManager::DataLoad::RemoveItemFromInventory(int code, int count)
{
	ItemDesc* item = itemDescs[code];
	vector<InventoryItemData*> &v = playerData->iData[item->type];

	for (int i = 0; i < (int)v.size(); ++i)
	{
		if (v[i]->code == code)
		{
			v[i]->count -= count;

			if (v[i]->count == 0)
			{
				delete v[i];
				v.erase(v.begin() + i);
				return true;
			}

			break;
		}
	}

	return false;
}

float DataLoadManager::DataLoad::GetTypeRevision(int skillType, int pokeType)
{
	return typeTable[skillType][pokeType];
}

Rect DataLoadManager::GetFrontPokemonImageRect(int id)
{
	int x = (id - 1) % 10;
	int y = ((id - 1) / 10) * 2;

	return Rect(x * POKE_PIXEL, y * POKE_PIXEL, POKE_PIXEL, POKE_PIXEL);
}

Rect DataLoadManager::GetBehindPokemonImageRect(int id)
{
	int x = (id - 1) % 10;
	int y = ((id - 1) / 10) * 2 + 1;

	return Rect(x * POKE_PIXEL, y * POKE_PIXEL, POKE_PIXEL, POKE_PIXEL);
}
