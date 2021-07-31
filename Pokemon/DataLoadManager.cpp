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
	Reset();
}

DataLoadManager::DataLoad::~DataLoad()
{
	for (auto &e : mapImages)
	{
		delete e.second;
	}
}

void DataLoadManager::DataLoad::Reset()
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