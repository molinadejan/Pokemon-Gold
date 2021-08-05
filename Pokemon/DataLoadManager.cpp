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

//https://m.blog.naver.com/codbs7/221441864531
void DataLoadManager::DataLoad::LoadFont()
{
	collection = new PrivateFontCollection;
	collection->AddFontFile(L"data/font/Dot.ttf");

	WCHAR familyName[LF_FACESIZE];
	int count, found;

	count = collection->GetFamilyCount();
	fm = new FontFamily[count];
	collection->GetFamilies(count, fm, &found);

	fm[0].GetFamilyName(familyName);

	fontS = new Font(familyName, 4 * SCREEN_MUL, FontStyleBold, UnitPoint, collection);
	fontM = new Font(familyName, 6 * SCREEN_MUL, FontStyleBold, UnitPoint, collection);
	fontB = new Font(familyName, 8 * SCREEN_MUL, FontStyleBold, UnitPoint, collection);
}

void DataLoadManager::DataLoad::LoadItemData()
{
	fstream openFile("data/table/item_desc.json");
	Json::Value root;

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

void DataLoadManager::DataLoad::Reset()
{
	LoadMap();
	LoadFont();
	LoadItemData();

	playerData = new PlayerData;

	// others

	player_game = new Image(_T("data/sprite/player/player_game.png"));
	UI_Bag = new Image(_T("data/sprite/UI/UI_Bag.png"));
	UI_Dialog_Base = new Image(_T("data/sprite/UI/UI_Dialog_Base.png"));

	// test
	for (int i = 1; i <= 60; ++i)
		AddItemToInventory(i, rand() % 999 + 1);
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

	InventoryData newData(code, item->type, count);
	playerData->iData[item->type].push_back(newData);
}

void DataLoadManager::Reset()
{
	dataLoad.Reset();
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
